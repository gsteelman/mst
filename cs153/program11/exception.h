///////////////////////////////////////////////////////////////////////////////
/// @file exception.h
/// @author Gary Steelman, CS153-B
/// @edited 7 Apr 08
/// @brief Exception class header file
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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

using namespace std;

class Exception
{
  public:
    Exception( int _error_code, string _error_message );
    int error_code();
    string error_message();
  private:
    int m_error_code;
    string error_message_data;
};

#endif
