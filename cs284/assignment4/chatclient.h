///////////////////////////////////////////////////////////////////////////////
/// @file chatclient.h
/// @author -- Jeremy Davidson
/// @author -- Gary Steelman
/// @brief -- A client class for an internet chat system.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class ChatClient
/// @brief The client for an internet chat system. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ChatClient()
/// @brief Default constructor for a ChatServer object. 
/// @pre None.
/// @post Creates a ChatClient object. 
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
/// @fn ~ChatClient()
/// @brief Destructor for a ChatClient. 
/// @pre A ChatClient exists.
/// @post Destroys the ChatClient object.
/// @return N/A.
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
/// @fn void run()
/// @brief Once setup() has been run, activates the client.
/// @pre A ChatServer object exists.
/// @pre setup() has been run and completed successfully. 
/// @post Activates the ChatClient. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void get_input()
/// @brief Gets the input from what the client types and stores it.
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @post Gets the input from what the client types and stores it. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_input( void * client )
/// @brief A wrapper for the client input thread.
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param void * client -- A void pointer to a ChatServer. 
/// @post Wraps the input thread for the client.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
/// @fn void read_buffer()
/// @brief Reads data input by the client. 
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @post Reads data input by the client. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn static void * thread_read( void * client )
/// @brief A wrapper for the client read thread.
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param void * data -- A void pointer to the client to read from. 
/// @post Wraps the read thread for the client.
/// @return NULL. 
///////////////////////////////////////////////////////////////////////////////
/// @fn void write_buffer( const string & to_write )
/// @brief Writes to the buffer and sends it to the server. 
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param const string& to_write -- The string to write to the buffer. 
/// @post Writes to_write to the buffer. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn static void signal_intercept(int sig)
/// @brief ctrl+c handling for trying to quit out illegally. 
/// @pre A ChatClient object exists, has been setup, and is running. 
/// @param int sig -- The signal number thrown.
/// @post Handles ctrl+c for trying to quit illegally.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <string>
#include <cstring>
using std::string;

#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

class ChatClient {

  public:
  
    ChatClient();
    ~ChatClient();
    
    void setup(const unsigned int port, const string & hostname);
    void run();
  
  protected:
  
    void          get_input();
    static void * thread_input(void * client);
    
    void          read_buffer();
    static void * thread_read(void * client);
    
    void          write_buffer(const string & to_write);
    
    static void   signal_intercept(int sig);
  
  private:
  
    int         m_socket;
    
    sockaddr_in m_address;
    sockaddr_in m_server_address;
    
    pthread_t   m_input_thread;
    pthread_t   m_read_thread;
    
    bool        m_done;

};

#endif
