///////////////////////////////////////////////////////////////////////////////
/// @file exception.cpp
/// @author Gary Steelman, CS153-B
/// @edited 7 Apr 08
/// @brief Exception class function implementation file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Exception
/// @brief Instantiates the exception with the passed parameters
/// @pre None.
/// @post Sets the member data to the passed error values
/// @param _error_code is the error number
/// @param _error_message is the error message to be displayed
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn error_code
/// @brief Returns the value of the error code for the error
/// @pre An Exception exists
/// @post Returns the value of the error code for the error
/// @return Returns the value of the error code for the error
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn error_message
/// @brief returns the string that is the error message
/// @pre An exception exists
/// @post Returns the string that is the error message
/// @return Returns the error message 
///////////////////////////////////////////////////////////////////////////////

/*
Code-Description
1-Trying to search for an item that does not exist in the tree.
*/

#ifndef EXCEPTION_CPP
#define EXCEPTION_CPP

#include "exception.h"
#include <iostream>

using namespace std;

Exception::Exception( int _error_code, string _error_message )
{
  m_error_code = _error_code;
  error_message_data = _error_message;
}
 
int Exception::error_code() 
{
  return m_error_code;
}
    
string Exception::error_message()
{
  return error_message_data;
}

#endif
