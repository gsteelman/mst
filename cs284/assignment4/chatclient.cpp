///////////////////////////////////////////////////////////////////////////////
/// @file chatclient.cpp
/// @author -- Jeremy Davidson
/// @author -- Gary Steelman
/// @brief -- A client class for an internet chat system.
///////////////////////////////////////////////////////////////////////////////

#include <cerrno>
#include <signal.h>

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "chatclient.h"

#include "exception.h"
#include "library.h"
#include "strmanip.h"

//////////////////////////////
/// CONSTS
//////////////////////////////
const unsigned int BUFFER_SIZE = 1024;

// For command handling 
const string QUIT = "/quit";
const string EXIT = "/exit";
const string PART = "/part";
const string NOTIFY = "<SERVER>";

///////////////////////////////////////////////////////////////////////////////
/// @fn ChatClient()
/// @brief Default constructor for a ChatServer object. 
/// @pre None.
/// @post Creates a ChatClient object. 
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
ChatClient::ChatClient() {

  // Initialize our data.
  m_address.sin_family = AF_INET;
  m_server_address.sin_family = AF_INET;
  
  // And set us to intercept a terminate signal.
  signal(SIGINT, ChatClient::signal_intercept);
  
  // Keeps track of whether we're done executing or not.
  m_done = false;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn ~ChatClient()
/// @brief Destructor for a ChatClient. 
/// @pre A ChatClient exists.
/// @post Destroys the ChatClient object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
ChatClient::~ChatClient() {

  // Nothing.

}

///////////////////////////////////////////////////////////////////////////////
/// @fn static void signal_intercept(int sig)
/// @brief ctrl+c handling for trying to quit out illegally. 
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param int sig -- The signal number thrown.
/// @post Handles ctrl+c for trying to quit illegally.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatClient::signal_intercept(int sig) {

  if (sig == SIGINT) {
  
    cout << NOTIFY
         << " Please exit using one of the defined exit commands: " << endl;
    cout << NOTIFY << " " << QUIT << endl;
    cout << NOTIFY << " " << EXIT << endl;
    cout << NOTIFY << " " << PART << endl;
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void setup( const unsigned int port, const string & hostname )
/// @brief Sets up the client to communicate over the designated port with
///   the server specified by hostname. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param const unsigned int port -- The port number for the client to 
///   communicate over. 
/// @param const string& hostname -- The name of the host where the server is
///   running. 
/// @post Sets up the client to communicate over the designated port.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatClient::setup(const unsigned int port, const string & hostname) {
  
  // Keep track of any errors we get.
  int error = 0;
  
  // Set up the rest of our address struct.
  // htons = host-to-network-short. This makes sure
  // our data here is converted properly to the network data format.
  m_address.sin_port = htons(port);
  m_server_address.sin_port = htons(port);
  
  m_address.sin_addr.s_addr = INADDR_ANY;
  
  hostent * host_info = gethostbyname(hostname.c_str());
  
  if (host_info == NULL) {
  
    throw Exception(0, "Host does not exist."
                       "(class ChatClient, setup())");
  
  }
  
  bcopy(host_info->h_addr,
        (char *)&m_server_address.sin_addr.s_addr,
        host_info->h_length);
  
  // Create the socket as non-blocking.
  m_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  if (m_socket == -1) {
  
    throw Exception(10, "Failed to create client socket. "
                        "(class ChatClient, setup())");
  
  }
  
  // Bind the socket to the port in the address struct
  // and fill up the rest of the address data.
  error = bind(m_socket, (sockaddr *)&m_address, sizeof(m_address));
  
  if (error == -1) {
  
    string message = "";
    
    switch (errno) {
    
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
    
    throw Exception(errno, "Client socket failed to bind to port " +
                        num_to_str(port) + " with the message: " + message +
                        " (class ChatClient, setup())");
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void run()
/// @brief Once setup() has been run, activates the client.
/// @pre A ChatServer object exists.
/// @pre setup() has been run and completed successfully. 
/// @post Activates the ChatClient. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatClient::run() {

  // Keep track of any errors we get.
  int error = 0;
  
  error = connect(m_socket, (sockaddr *)&m_server_address,
                  sizeof(m_server_address));
  
  string message = "";
  
  switch (errno) {
    
    case EACCES:
			message = "The user tried to connect to a broadcast address "
                "without having the socket broadcast flag enabled "
                "or the connection request failed because of a local "
                "firewall rule.";
			break;
		
    case EPERM:
			message = "The user tried to connect to a broadcast address "
                "without having the socket broadcast flag enabled "
                "or the connection request failed because of a local "
                "firewall rule.";
			break;
		
    case EADDRINUSE:
			message = "Local address is already in use.";
			break;
		
    case EAFNOSUPPORT:
			message = "The passed address didn't have the correct "
                "address family in its sa_family field.";
			break;
		
    case EAGAIN:
			message = "No more free local ports or insufficient "
                "entries in the routing cache.";
			break;
		
    case EALREADY:
			message = "The socket is non-blocking and a previous "
                "connection attempt has not yet been completed.";
			break;
		
    case EBADF:
			message = "The file descriptor is not a valid index "
                "in the descriptor table.";
			break;
		
    case ECONNREFUSED:
			message = "No one listening on the remote address.";
			break;
		
    case EFAULT:
			message = "The socket structure address is outside "
                "the user's address space.";
			break;
		
    case EINPROGRESS:
			message = "The socket is non-blocking and the "
                "connection cannot be completed immediately.";
			break;
		
    case EINTR:
			message = "The system call was interrupted by a signal that was caught.";
			break;
		
    case EISCONN:
			message = "The socket is already connected.";
			break;
		
    case ENETUNREACH:
			message = "Network is unreachable.";
			break;
		
    case ENOTSOCK:
			message = "The file descriptor is not associated with a socket.";
			break;
		
    case ETIMEDOUT:
			message = "Timeout while attempting connection. "
                "The server may be too busy to accept new connections.";
			break;
		
  }
  
  if (error == -1) {
  
    throw Exception(errno, "Client failed to connect to server "
                           "with the message: " + message +
                           " (class ChatClient, run())");
  
  }
  
  cout << NOTIFY << " Welcome to the chat server." << endl;
  cout << NOTIFY << " Type '/nick name' to change your nickname." << endl;
  cout << NOTIFY << " Type '/quit', '/part', or '/exit' to leave the server."
       << endl;
  
  // Create our read/input threads.
  error = pthread_create(&m_read_thread, NULL,
                         ChatClient::thread_read, this);
  
  if (error != 0) {
  
    throw Exception(13, "Failed to create listen thread. "
                        "(class ChatClient, run())");
  
  }
  
  error = pthread_create(&m_input_thread, NULL,
                         ChatClient::thread_input, this);
  
  if (error != 0) {
  
    throw Exception(14, "Failed to create input thread. "
                        "(class ChatClient, run())");
  
  }
  
  // Wait for our threads to complete.
  error = pthread_join(m_read_thread, NULL);
  
  if (error != 0) {
  
    throw Exception(15, "Failed to join listen thread. "
                        "(class ChatClient, run())");
  
  }
  
  error = pthread_join(m_input_thread, NULL);
  
  if (error != 0) {
  
    throw Exception(16, "Failed to join input thread. "
                        "(class ChatClient, run())");
  
  }
  
  // And close our socket.
  close(m_socket);

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void get_input()
/// @brief Gets the input from what the client types and stores it.
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @post Gets the input from what the client types and stores it. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatClient::get_input() {
  
  // Loop for the duration of the program.
  while (!m_done) {
  
    string input;
    
    getline(cin, input);
    
    // Handle exiting here.
    if (str_left(input, EXIT.length()) == EXIT ||
        str_left(input, QUIT.length()) == QUIT ||
        str_left(input, PART.length()) == PART) {
    
      m_done = true;
      
      cout << NOTIFY << " Good bye." << endl;
      cout << NOTIFY << " Please wait at least 1 minute before attempting "
           << "to rejoin the server." << endl;
    
    }
    
    // And output the buffer to the server, if necessary.
    if (input != "") {
      
      write_buffer(input);
    
    }
  
  }
  
  // Get rid of the read thread, so we don't loop forever.
  pthread_cancel(m_read_thread);

}

///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_input( void * client )
/// @brief A wrapper for the client input thread.
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param void * client -- A void pointer to a ChatServer. 
/// @post Wraps the input thread for the client.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
void * ChatClient::thread_input(void * client) {

  // Wrapper for the thread entry function.
  ChatClient * client_ptr = (ChatClient *)client;
  client_ptr->get_input();
  
  return NULL;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void read_buffer()
/// @brief Reads data input by the client. 
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @post Reads data input by the client. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatClient::read_buffer() {
  
  char buffer[BUFFER_SIZE];
  
  int bytes_read = read(m_socket, buffer, sizeof(buffer));
  
  if (bytes_read == -1 || bytes_read > SSIZE_MAX) {
  
    throw Exception(19, "Error reading from buffer. "
                        "(class ChatClient, read_buffer())");
  
  }
  
  // Convert our buffer into a string.
  string output(buffer);
  
  // If we received a quit message from the server, then we're forced
  // to exit.
  if (output == QUIT || output == EXIT || output == PART) {
  
    // Break out of the external loop.
    m_done = true;
    
    // And output a nice closing message.
    output = NOTIFY + " Good bye.\n" + 
             "Please press 'Enter' to shut down the program.";
  
  }
  
  // Write the message out to the screen, if necessary.
  if (output != "") {
  
    cout << output << endl;
  
  }

}

///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_read( void * client )
/// @brief A wrapper for the client read thread.
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param void * data -- A void pointer to the client to read from. 
/// @post Wraps the read thread for the client.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
void * ChatClient::thread_read(void * client) {

  // Wrapper for the thread entry function.
  ChatClient * client_ptr = (ChatClient *)client;
  
  while (!client_ptr->m_done) {
  
    client_ptr->read_buffer();
  
  }
  
  return NULL;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void write_buffer( const string & to_write )
/// @brief Writes to the buffer and sends it to the server. 
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param const string& to_write -- The string to write to the buffer. 
/// @post Writes to_write to the buffer. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void ChatClient::write_buffer(const string & to_write) {
  
  char buffer[BUFFER_SIZE];
  
  // Put the string into the buffer, making sure it will fit.
  strcpy(buffer, str_left(to_write, BUFFER_SIZE - 1).c_str());
  
  int written = write(m_socket, buffer, sizeof(buffer));
  
  if (written == -1) {
  
    throw Exception(20, "Error writing to socket from buffer. "
                        "(class ChatClient, write_buffer())");
  
  }
  
}
