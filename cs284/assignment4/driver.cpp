///////////////////////////////////////////////////////////////////////////////
/// @file -- driver.cpp
/// @author -- Jeremy Davidson
/// @author -- Gary Steelman
/// @date -- 11.16.09
/// @course -- CS 284
/// @section -- A
/// @assignment -- 4
/// @brief -- A driver for the threaded chat program.
///////////////////////////////////////////////////////////////////////////////

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include "chatserver.h"
#include "chatclient.h"

#include "exception.h"
#include "file.h"
#include "strmanip.h"

//////////////////////////////
/// CONSTS
//////////////////////////////
const unsigned int DEFAULT_PORT = 12853;
const string       DEFAULT_HOST = "localhost";

//////////////////////////////
/// PRE-DECLARATIONS
//////////////////////////////
void driver(int argc, char * argv[]);
void error_logger(const Exception & e);

//////////////////////////////
/// MAIN
//////////////////////////////
int main(int argc, char * argv[]) {

  // Catch-all exception handler.
  // If something's not handled on the inside,
  // this will catch the exception and write it out to a file.
  try {
    
    // Don't clutter the main routine.
    driver(argc, argv);
    
  } catch (Exception e) {
    
    // Run the error logger.
    error_logger(e);
    
    // Return a bad code, just for redundancy.
    return e.error_code();
  
  }
  
  // Success!
  return 0;

}

//////////////////////////////
/// DRIVER
//////////////////////////////
void driver(int argc, char * argv[]) {
  
  // Argument #2 is the first command line argument, so
  // we want to make sure we have some here.
  if (argc > 1) {
  
    string type(argv[1]);
    
    // Make the string lowercase so it's not case-sensitive.
    type = str_tolower(type);
    
    unsigned int port = DEFAULT_PORT;
    
    // If they supplied a port to use.
    if (argc > 2) {
    
      string port_str(argv[2]);
      port_str = str_tolower(port_str);
      
      if (port_str != "-d") {
      
        port = str_to_int(argv[2]);
      
      }
    
    }
    
    // Create an object of the requested type and start running.
    if (type == "s" || type == "server") {
    
      ChatServer server;
      server.setup(port);
      server.run();
    
    } else if (type == "c" || type == "client") {
    
      string hostname = DEFAULT_HOST;
      
      if (argc > 3) {
      
        hostname = argv[3];
      
      }
      
      ChatClient client;
      client.setup(port, hostname);
      client.run();
    
    } else {
    
      cout << "Invalid arguments provided." << endl;
      cout << "Please supply arguments to the program in this format:" << endl;
      cout << argv[0] << " type [port [hostname]]" << endl;
      cout << "type:     Either 'S' for server or 'C' for client." << endl;
      cout << "port:     The port number to use ('-d' for default)." << endl;
      cout << "          Note: this program defaults to port " << DEFAULT_PORT
           << "." << endl;
      cout << "hostname: The hostname or IP address of the server to" << endl;
      cout << "          connect to (only used as client)." << endl;
      cout << "These are case-insensitive." << endl;
    
    }
  
  } else {
  
    cout << "No arguments provided." << endl;
    cout << "Please supply arguments to the program in this format:" << endl;
    cout << argv[0] << " type [port [hostname]]" << endl;
    cout << "type:     Either 'S' for server or 'C' for client." << endl;
    cout << "port:     The port number to use ('-d' for default)." << endl;
    cout << "          Note: this program defaults to port " << DEFAULT_PORT
         << endl;
    cout << "hostname: The hostname or IP address of the server to" << endl;
    cout << "          connect to (only used as client)." << endl;
    cout << "These are case-insensitive." << endl;
  
  }
  
}

//////////////////////////////
/// ERROR LOGGER
//////////////////////////////
void error_logger(const Exception & e) {

  // Open the log file.
  File error_log("errorlog.txt");
  
  // Message for dual-output.
  string message = "Exception " + int_to_str(e.error_code()) + ": " +
                   e.error_message();
  
  // Insert a new line at the end with the error code and message.
  error_log.insert_line(error_log.num_lines(), message);
  
  // Close and save the file.
  error_log.close(true);
  
  // Output to standard out, too.
  cout << message << endl;

}
