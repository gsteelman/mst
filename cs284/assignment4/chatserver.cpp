///////////////////////////////////////////////////////////////////////////////
/// @file chatserver.cpp
/// @author -- Jeremy Davidson
/// @author -- Gary Steelman
/// @brief -- A server class for an internet chat system.
///////////////////////////////////////////////////////////////////////////////

#include <cerrno>
#include <signal.h>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "chatserver.h"

#include "exception.h"
#include "library.h"
#include "strmanip.h"

//////////////////////////////
/// CONSTS
//////////////////////////////
const unsigned int MAX_CLIENTS = 10;
const unsigned int BUFFER_SIZE = 1024;
const unsigned int SHUTDOWN_TIME = 10;

const string QUIT = "/quit";
const string EXIT = "/exit";
const string PART = "/part";
const string NICK = "/nick";
const string NOTIFY = "<SERVER>";

//////////////////////////////
/// STRUCTS
//////////////////////////////
struct ThreadRead {

  ChatServer * server;
  int socket;

};

///////////////////////////////////////////////////////////////////////////////
/// @fn ChatServer()
/// @brief Default constructor for a ChatServer object. 
/// @pre None.
/// @post Creates a ChatServer object. 
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
ChatServer::ChatServer() {

  // Initialize our data.
  m_address.sin_family = AF_INET;
  
  // And set us to intercept a terminate signal.
  signal(SIGINT, ChatServer::signal_intercept);
  
  m_username = "Server";
  
  // Keeps track of whether we're done executing or not.
  m_done = false;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn ~ChatServer()
/// @brief Destructor for a ChatServer. 
/// @pre A ChatServer exists.
/// @post Destroys the ChatServer object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
ChatServer::~ChatServer() {

  // Nothing.

}

///////////////////////////////////////////////////////////////////////////////
/// @fn static void signal_intercept(int sig)
/// @brief ctrl+c handling for trying to quit out illegally. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param int sig -- The signal number thrown.
/// @post Handles ctrl+c for trying to quit illegally.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatServer::signal_intercept(int sig) {

  if (sig == SIGINT) {
  
    cout << NOTIFY
         << " Please exit using one of the defined exit commands: " << endl;
    cout << NOTIFY << " " << QUIT << endl;
    cout << NOTIFY << " " << EXIT << endl;
    cout << NOTIFY << " " << PART << endl;
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void setup( const unsigned int port )
/// @brief Sets up the server to communicate over the designated port.
/// @pre A ChatServer exists.
/// @param const unsigned int port -- The port number for the server to 
///   communicate over. 
/// @post Sets up the server to communicate over the designated port.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatServer::setup(const unsigned int port) {
  
  // Keep track of any errors we get.
  int error = 0;
  
  // Set up the rest of our address struct.
  // htons = host-to-network-short. This makes sure
  // our data here is converted properly to the network data format.
  m_address.sin_port = htons(port);
  m_address.sin_addr.s_addr = INADDR_ANY;
  
  // Create the socket as non-blocking.
  m_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  if (m_socket == -1) {
  
    throw Exception(10, "Failed to create server socket. "
                        "(class ChatServer, setup())");
  
  }
  
  // Bind the socket to the port in the address struct
  // and fill up the rest of the address data.
  error = bind(m_socket, (sockaddr *)&m_address, sizeof(m_address));
  
  if (error == -1) {
  
    string message = "";
    
    switch errno {
    
      case EACCES:
        message = "The address is protected, "
                  "and the user is not the superuser.";
        break;
        
      case EADDRINUSE:
        message = "The given address is already in use.";
        break;
        
      case EBADF:
        message = num_to_str(m_socket) + " is not a valid descriptor.";
        break;
        
      case EINVAL:
        message = "The socket is already bound to an address.";
        break;
        
      case ENOTSOCK:
        message = num_to_str(m_socket) + "is a descriptor for a file, "
                  "not a socket.";
        break;
        
    	case EADDRNOTAVAIL:
				message = "A nonexistent interface was requested "
                  "or the address was not local.";
				break;
        
    	case EFAULT:
				message = "Address points outside the user's "
                  "accessible address space.";
				break;
        
    	case ELOOP:
				message = "Too many symbolic links were encountered "
                  "in resolving the address.";
				break;
        
    	case ENAMETOOLONG:
				message = "Address is too long.";
				break;
        
    	case ENOENT:
				message = "The file does not exist.";
				break;
        
    	case ENOMEM:
				message = "Insufficient kernel memory was available.";
				break;
        
    	case ENOTDIR:
				message = "The component of the path prefix is not a directory.";
				break;
        
    	case EROFS:
				message = "The socket inode would reside on a read-only file system.";
        break;
    
    }
    
    throw Exception(errno, "Server socket failed to bind to port " +
                        num_to_str(port) + " with the message: " + message +
                        " (class ChatServer, setup())");
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void run()
/// @brief Once setup() has been run, activates the server.
/// @pre A ChatServer object exists.
/// @pre setup() has been run and completed successfully. 
/// @post Activates the ChatServer. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatServer::run() {

  // Keep track of any errors we get.
  int error = 0;
  
  error = listen(m_socket, MAX_CLIENTS);
  
  if (error == -1) {
  
    throw Exception(12, "Server failed to listen for clients. "
                        "(class ChatServer, run())");
  
  }
  
  cout << NOTIFY << " Welcome to the chat server." << endl;
  cout << NOTIFY << " Type '/nick name' to change your nickname." << endl;
  cout << NOTIFY << " Type '/quit', '/part', or '/exit' to leave the server."
       << endl;
  
  // Create our listen/input threads.
  error = pthread_create(&m_listen_thread, NULL,
                         ChatServer::thread_listen, this);
  
  if (error != 0) {
  
    throw Exception(13, "Failed to create listen thread. "
                        "(class ChatServer, run())");
  
  }
  
  error = pthread_create(&m_input_thread, NULL,
                         ChatServer::thread_input, this);
  
  if (error != 0) {
  
    throw Exception(14, "Failed to create input thread. "
                        "(class ChatServer, run())");
  
  }
  
  // Wait for our threads to complete.
  error = pthread_join(m_input_thread, NULL);
  
  if (error != 0) {
  
    throw Exception(16, "Failed to join input thread. "
                        "(class ChatServer, run())");
  
  }
  
  error = pthread_join(m_listen_thread, NULL);
  
  if (error != 0) {
  
    throw Exception(15, "Failed to join listen thread. "
                        "(class ChatServer, run())");
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void get_input()
/// @brief Gets the input from what the server types and stores it.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @post Gets the input from what the server types and stores it. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatServer::get_input() {
  
  // Loop for the duration of the program.
  while (!m_done) {
  
    string input;
    
    getline(cin, input);
    
    // Handle exiting here.
    if (str_left(input, EXIT.length()) == EXIT ||
        str_left(input, QUIT.length()) == QUIT ||
        str_left(input, PART.length()) == PART) {
    
      m_done = true;
    
    } else {
    
      // Parse the input for any commands.
      input = parse_buffer(m_socket, input);
      
      // And output the buffer to the other clients, if necessary.
      if (input != "") {
      
        write_buffer(m_socket, input);
      
      }
    
    }
  
  }
  
  exit();

}

///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_input( void * server )
/// @brief A wrapper for the server input thread.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param void * server -- A void pointer to a ChatServer. 
/// @post Wraps the input thread for the server.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
void * ChatServer::thread_input(void * server) {

  // Wrapper for the thread entry function.
  ChatServer * server_ptr = (ChatServer *)server;
  server_ptr->get_input();
  
  return NULL;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn listen_clients()
/// @brief Listens for clients, makes a new thread for each client. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient object exists, and has been setup.
/// @post Creates a thread for new clients.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatServer::listen_clients() {

  // Loop for the duration of the program.
  while (!m_done) {
  
    // Only listen for more clients if we have space for more.
    if (m_client_sockets.size() < MAX_CLIENTS) {
    
      sockaddr_in client_address;
      client_address.sin_family = AF_INET;
      
      int client_length = sizeof(client_address);
      
      int client_socket = accept(m_socket, (sockaddr *)&client_address,
                                 (socklen_t *)&client_length);
      
      // If we failed.
      if (client_socket == -1) {
      
        throw Exception(17, "Failed to accept new client. "
                            "(class ChatServer, listen())");
      
      }
      
      m_client_addresses.push_back(client_address);
      
      // Add the new socket to the list of client sockets.
      m_client_sockets.push_back(client_socket);
      
      // Give the new client a default username.
      set_username(client_socket, "Guest" + num_to_str(client_socket, 4));
      
      pthread_t client_thread;
      
      // Keep track of any errors we get.
      int error = 0;
      
      ThreadRead read_data;
      read_data.server = this;
      read_data.socket = m_client_sockets[m_client_sockets.size() - 1];
      
      // Create a new thread for reading from the client's socket.
      error = pthread_create(&client_thread,
                             NULL,
                             ChatServer::thread_read,
                             &read_data);
      
      if (error != 0) {
      
        throw Exception(18, "Failed to create new client thread. "
                            "(class ChatServer, listen())");
      
      }
      
      m_client_threads.push_back(client_thread);
      
      write_buffer(client_socket, NOTIFY + " " + get_username(client_socket) +
                                  " has joined the server.");
    
    }
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_listen( void * server )
/// @brief A wrapper for the server listen thread.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param void * server -- A void pointer to a ChatServer. 
/// @post Wraps the listen thread for the server.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
void * ChatServer::thread_listen(void * server) {
  
  // Wrapper for the thread entry function.
  ChatServer * server_ptr = (ChatServer *)server;
  server_ptr->listen_clients();
  
  return NULL;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void read_buffer( const unsigned int socket )
/// @brief Reads data input to the specified socket. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param const unsigned int socket -- The socket number to read from.
/// @post Reads data input to the specified socket. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatServer::read_buffer(const unsigned int socket) {
  
  char buffer[BUFFER_SIZE];
  
  int bytes_read = read(socket, buffer, sizeof(buffer));
  
  if (bytes_read == -1 || bytes_read > SSIZE_MAX) {
  
    throw Exception(19, "Error reading from buffer. "
                        "(class ChatServer, read_buffer())");
  
  }
  
  // Convert our buffer into a string.
  string output(buffer);
  
  // Parse the data we just received for any special commands.
  output = parse_buffer(socket, output);
  
  // And write it out to the clients, if necessary.
  if (output != "") {
  
    write_buffer(socket, output);
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_read( void * data )
/// @brief A wrapper for the server read thread.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param void * data -- A void pointer to the data to read. 
/// @post Wraps the read thread for the server.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
void * ChatServer::thread_read(void * data) {

  // Wrapper for the thread entry function.
  ThreadRead read_data;
  
  read_data = *(ThreadRead *)data;
  
  // Only loop as long as the socket still exists.
  while (search(read_data.server->m_client_sockets,
                read_data.socket) != UINT_MAX) {
  
    read_data.server->read_buffer(read_data.socket);
  
  }
  
  return NULL;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void write_buffer( const int socket, const string & to_write )
/// @brief Writes to all clients except the one specified by socket. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param const int socket -- The socket to skip writing to.
/// @param const string& to_write -- The string to write to all sockets except 
///   socket.
/// @post Writes to_write to socket.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatServer::write_buffer(const int socket, const string & to_write) {

  char buffer[BUFFER_SIZE];
  
  // Put the string into the buffer, making sure it will fit.
  strcpy(buffer, str_left(to_write, BUFFER_SIZE - 1).c_str());
  
  // Write to all clients (except the sender).
  for (unsigned int x = 0; x < m_client_sockets.size(); x++) {
  
    // Skip this one if it was the sender.
    if (m_client_sockets[x] != socket) {
    
      int written = write(m_client_sockets[x], buffer,
                          sizeof(buffer));
      
      if (written == -1) {
      
        throw Exception(20, "Error writing to socket from buffer. "
                            "(class ChatServer, write_buffer())");
      
      }
    
    }
  
  }
  
  // Output the original string here, if it's not the server who said it.
  if (socket != m_socket) {
  
    cout << to_write << endl;
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn string parse_buffer( const int socket, const string & buffer )
/// @brief Parses the buffer of the specified socket into useable input.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param const int socket -- The socket number to look in.
/// @param const string& buffer -- The contents of the buffer specified by 
///   socket's client. 
/// @post Returns the parsed string.
/// @return string -- The parsed version of the input.
///////////////////////////////////////////////////////////////////////////////
string ChatServer::parse_buffer(const int socket, const string & buffer) {

  string parsed = buffer;
  
  // If we start with a "/", then we're dealing with a command.
  if (str_left(parsed, 1) == "/") {
  
    // Remove any double spaces so we can parse properly even if they
    // add too many spaces.
    parsed = str_replace_all(parsed, "  ", " ");
    
    // Then break it into individual space-delimited commands.
    // We are guaranteed at least one element in this vector because
    // we've previously checked that the first character is a "/".
    vector<string> commands = str_find_lines(parsed, " ");
    
    // Check to see if we have an exit request.
    if (str_left(commands[0], EXIT.length()) == EXIT ||
        str_left(commands[0], QUIT.length()) == QUIT ||
        str_left(commands[0], PART.length()) == PART) {
      
      // Handle server quitting elsewhere.
      if (socket != m_socket) {
      
        // If we do, set the output to say that the user has quit.
        parsed = NOTIFY + " " + get_username(socket) + " has left the server.";
        
        // And disconnect them.
        disconnect_client(socket);
      
      }
      
    } else if (str_left(commands[0], NICK.length()) == NICK &&
               commands.size() > 1) {
      
      // Or, if we have a nick change request...
      // First set the output to reflect the change.
      parsed = NOTIFY + " " + get_username(socket) + " is now known as " +
               commands[1] + ".";
      
      // And then change the name.
      set_username(socket, commands[1]);
    
    } else {
    
      // If it's an invalid command, then don't output anything.
      parsed = "";
    
    }
  
  } else {
  
    // If it's not a command, then it's plain text to be sent to
    // the other users.
    parsed = "[" + get_username(socket) + "]: " + parsed;
  
  }
  
  return parsed;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void disconnect_client( const int socket )
/// @brief Disconnects a client specified by socket. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient is connected.
/// @param const int socket -- The socket number to disconnect.
/// @post Disconnectes a client specified by socket.
/// @return None. 
///////////////////////////////////////////////////////////////////////////////
void ChatServer::disconnect_client(const int socket) {

  // Check to see if we're disconnecting the server first.
  // Handle server disconnect elsewhere.
  if (socket == m_socket) {
  
    return;
  
  }

  // Find the index of the socket in the socket vector.
  unsigned int index = search(m_client_sockets, socket);
  
  // Not found.
  if (index == UINT_MAX) {
  
    throw Exception(21, "Socket does not exist. "
                        "(class ChatServer, disconnect_client())");
  
  }
  
  // Delete thread storage.
  // It will expire naturally at the end of this function.
  m_client_threads.erase(m_client_threads.begin() + index);
  
  // Get rid of the socket.
  close(m_client_sockets[index]);
  m_client_sockets.erase(m_client_sockets.begin() + index);
  
  // Delete the address.
  m_client_addresses.erase(m_client_addresses.begin() + index);
  
  // Get rid of the username, too.
  m_client_usernames.erase(m_client_usernames.begin() + index);

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void exit()
/// @brief Disconnectes all clients and shuts down the server.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @post Disconnects all clients and shuts down the server.
/// @return None. 
///////////////////////////////////////////////////////////////////////////////
void ChatServer::exit() {

  // Send out a warning and then kill in 10 seconds.
  write_buffer(-1, NOTIFY + " WARNING: The server will be shut down in " +
                   num_to_str(SHUTDOWN_TIME) + " seconds.");
  
  // Sleep for ten seconds.
  sleep(SHUTDOWN_TIME);
  
  // Send to -1 so everyone sees it, even the server.
  write_buffer(-1, NOTIFY + " WARNING: The server is now shutting down.");
  
  // Signal all the clients to disconnect.
  write_buffer(m_socket, EXIT);
  
  //for (unsigned int x = 0; x < m_client_sockets.size(); x++) {
  while (m_client_sockets.size() > 0) {
  
    // Kill everyone.
    disconnect_client(m_client_sockets[0]);
  
  }
  
  close(m_socket);
  
  // And get rid of our other threads so we go back to the main run()
  pthread_cancel(m_listen_thread);

}

///////////////////////////////////////////////////////////////////////////////
/// @fn string get_username( const int socket )
/// @brief Gets the username of the ChatClient connected at socket.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient is connected.
/// @param const int socket -- The socket number to get the username of.
/// @post Gets the username of the ChatClient connected at socket.
/// @return string -- The username of the ChatClient.
///////////////////////////////////////////////////////////////////////////////
string ChatServer::get_username(const int socket) {

  // Check to see if we're retrieving the server's name first.
  if (socket == m_socket) {
  
    return m_username;
  
  }

  // Find the index of the socket in the socket vector.
  unsigned int index = search(m_client_sockets, socket);
  
  // Not found.
  if (index == UINT_MAX || index >= m_client_usernames.size()) {
  
    throw Exception(22, "Socket does not exist or does not have a "
                        "name assigned. (class ChatServer, get_username())");
  
  }
  
  return m_client_usernames[index];

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void set_username( const int socket, const string & username )
/// @brief Sets the specified socket's client's username to username.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient is connected.
/// @param const int socket -- The socket number of the ChatClient to change
/// @param const string & username -- The username to change to.
/// @post Sets the specified socket's client's username to username. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatServer::set_username(const int socket, const string & username) {

  // Check to see if we're setting the server first.
  if (socket == m_socket) {
  
    m_username = username;
    return;
  
  }
  
  // Find the index of the socket in the socket vector.
  unsigned int index = search(m_client_sockets, socket);
  
  // Not found.
  if (index == UINT_MAX) {
  
    throw Exception(23, "Socket does not exist or does not have a "
                        "name assigned. (class ChatServer, set_username())");
  
  }
  
  if (index >= m_client_usernames.size()) {
  
    // If we don't have enough names for this socket, then make
    // the vector bigger.
    m_client_usernames.resize(index + 1);
  
  }
  
  m_client_usernames[index] = username;

}
