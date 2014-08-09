///BEGINNING OF FILE-----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file requestTime.h
/// @auth Gary Steelman
/// @edit 25 Apr 2009
/// @brief Function declarations for the requestTime class
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn requestTime()
/// @brief the default constructor for the requestTime class
/// @note initializes the database when called
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn requestTime( string today, string uID, string startDate, string endDate )
/// @brief This is the constructor for the request time class
/// @param string uID is the user ID of the user requesting leave
/// @param string startDate is the first date the user wants off
/// @param string endDate is the last date the user wants off
/// @note the parameter today must be in "MM/DD" where MM is the month number
///   and DD is the day number
/// @note all dates between and including startDate and endDate will be
///   recorded as a request for vacation dates
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn addRequest( string uID, string startDate, string endDate )
/// @brief This is a function that stores requests to a file 
/// @param string uID is the user ID of the user requesting leave
/// @param string startDate is the first date the user wants off
/// @param string endDate is the last date the user wants off
/// @param string leaveType is the type of leave to request
///   0 = sick leave
///   1 = vacation leave
/// @ret true if the adding went alright, false if the user made a request
///   when they did not have enough balance to do so
/// @note the parameter today must be in "MM/DD" where MM is the month number
///   and DD is the day number
/// @note all dates between and including startDate and endDate will be
///   recorded as a request for vacation dates
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~requestTime(void)
/// @brief This is the default destructor for the requestTime class
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn setToday()
/// @brief Fetches the current time of the system and parses the day and month 
///   into our MM/DD format and stores it in m_today
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn get_today()
/// @brief gets today's date as stored by the validate class on instantiation
/// @return string containing today's date in MM/DD format
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void initializeDatabase()
/// @brief sets up the databse with the required fields to function
///////////////////////////////////////////////////////////////////////////////

#ifndef REQUEST_TIME_H
#define REQUEST_TIME_H

#include <string> //Gives us the string library to work with 
using std::string;

class requestTime {

  public:

    requestTime();
    
    requestTime( string uID, string startDate, string endDate, string leaveType );

	  ~requestTime( void );

    string get_today();
  
    bool addRequest( string uID, string startDate, string endDate, string leaveType );

  private:
    
    void setToday();

    //Holds the current date in our MM/DD format
    string m_today;

    time_t str_to_time( string date );

    int num_days( string start, string end );

    int num_days( time_t start, time_t end );
};

#endif

///END OF FILE-----------------------------------------------------------------