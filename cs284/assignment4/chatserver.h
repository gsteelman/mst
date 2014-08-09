///////////////////////////////////////////////////////////////////////////////
/// @file chatserver.h
/// @author -- Jeremy Davidson
/// @author -- Gary Steelman
/// @brief -- A server class for an internet chat system.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class ChatServer
/// @brief The server for an internet chat system. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ChatServer()
/// @brief Default constructor for a ChatServer object. 
/// @pre None.
/// @post Creates a ChatServer object. 
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
/// @fn ~ChatServer()
/// @brief Destructor for a ChatServer. 
/// @pre A ChatServer exists.
/// @post Destroys the ChatServer object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
/// @fn void setup( const unsigned int port )
/// @brief Sets up the server to communicate over the designated port.
/// @pre A ChatServer exists.
/// @param const unsigned int port -- The port number for the server to 
///   communicate over. 
/// @post Sets up the server to communicate over the designated port.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void run()
/// @brief Once setup() has been run, activates the server.
/// @pre A ChatServer object exists.
/// @pre setup() has been run and completed successfully. 
/// @post Activates the ChatServer. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void get_input()
/// @brief Gets the input from what the server types and stores it.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @post Gets the input from what the server types and stores it. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_input( void * server )
/// @brief A wrapper for the server input thread.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param void * server -- A void pointer to a ChatServer. 
/// @post Wraps the input thread for the server.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
/// @fn listen_clients()
/// @brief Listens for clients, makes a new thread for each client. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient object exists, and has been setup.
/// @post Creates a thread for new clients.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_listen( void * server )
/// @brief A wrapper for the server listen thread.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param void * server -- A void pointer to a ChatServer. 
/// @post Wraps the listen thread for the server.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
/// @fn void read_buffer( const unsigned int socket )
/// @brief Reads data input to the specified socket. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param const unsigned int socket -- The socket number to read from.
/// @post Reads data input to the specified socket. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_read( void * data )
/// @brief A wrapper for the server read thread.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param void * data -- A void pointer to the data to read. 
/// @post Wraps the read thread for the server.
/// @return NULL. 
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
/// @fn string parse_buffer( const int socket, const string & buffer )
/// @brief Parses the buffer of the specified socket into useable input.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param const int socket -- The socket number to look in.
/// @param const string& buffer -- The contents of the buffer specified by 
///   socket's client. 
/// @post Returns the parsed string.
/// @return string -- The parsed version of the input.
///////////////////////////////////////////////////////////////////////////////
/// @fn void disconnect_client( const int socket )
/// @brief Disconnects a client specified by socket. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient is connected.
/// @param const int socket -- The socket number to disconnect.
/// @post Disconnectes a client specified by socket.
/// @return None. 
///////////////////////////////////////////////////////////////////////////////
/// @fn void exit()
/// @brief Disconnectes all clients and shuts down the server.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @post Disconnects all clients and shuts down the server.
/// @return None. 
///////////////////////////////////////////////////////////////////////////////
/// @fn string get_username( const int socket )
/// @brief Gets the username of the ChatClient connected at socket.
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @pre A ChatClient is connected.
/// @param const int socket -- The socket number to get the username of.
/// @post Gets the username of the ChatClient connected at socket.
/// @return string -- The username of the ChatClient.
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
/// @fn static void signal_intercept(int sig)
/// @brief ctrl+c handling for trying to quit out illegally. 
/// @pre A ChatServer object exists, has been setup, and is running. 
/// @param int sig -- The signal number thrown.
/// @post Handles ctrl+c for trying to quit illegally.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <string>
#include <cstring>
using std::string;

#include <vector>
using std::vector;

#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

class ChatServer {

  public:
  
    ChatServer();
    ~ChatServer();
    
    void setup(const unsigned int port);
    void run();
  
  protected:
  
    void          get_input();
    static void * thread_input(void * server);
    
    void          listen_clients();
    static void * thread_listen(void * server);
    
    void          read_buffer(const unsigned int socket);
    static void * thread_read(void * data);
    
    void          write_buffer(const int socket, const string & to_write);
    string        parse_buffer(const int socket, const string & buffer);
    
    void          disconnect_client(const int socket);
    void          exit();
    
    string        get_username(const int socket);
    void          set_username(const int socket, const string & username);
    
    static void   signal_intercept(int sig);
  
  private:
  
    int                 m_socket;
    vector<int>         m_client_sockets;
    
    string              m_username;
    vector<string>      m_client_usernames;
    
    sockaddr_in         m_address;
    vector<sockaddr_in> m_client_addresses;
    
    pthread_t           m_input_thread;
    pthread_t           m_listen_thread;
    vector<pthread_t>   m_client_threads;
    
    bool                m_done;

};

#endif
