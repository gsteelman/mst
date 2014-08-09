///////////////////////////////////////////////////////////////////////////////
/// @file requestTime.cpp
/// @auth Gary Steelman
/// @edit 25 Apr 2009
/// @brief Function implementation for the requestTime class
///////////////////////////////////////////////////////////////////////////////

#include "requestTime.h" //Includes the header for this implementation

#include "../database/database.h" //Gives us the database functionality we'll need

#include "../library/exception.h" //Gives us the exception functionality
                                  //THIS CLASS USES EXCEPTIONS 50-...

#include "../library/strmanip.h" //Gives us string manipulation functions

#include "../common.h" //Gives us our path constants and databse constants

#include <ctime> //Gives us the ctime library

///////////////////////////////////////////////////////////////////////////////
/// @fn requestTime()
/// @brief the default constructor for the requestTime class
///////////////////////////////////////////////////////////////////////////////
requestTime::requestTime() {
  
  //Set today's date
  setToday();

  // Ensure our database is open.
  DATABASE.open(DATABASE_PATH);

}

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
requestTime::requestTime( string uID, string startDate, string endDate, string leaveType ) {

  //Set today's date
  setToday();

  addRequest( uID, startDate, endDate, leaveType );

}

///////////////////////////////////////////////////////////////////////////////
/// @fn ~requestTime(void)
/// @brief This is the default destructor for the requestTime class
///////////////////////////////////////////////////////////////////////////////
requestTime::~requestTime() {
  
  DATABASE.save_file();

}

///////////////////////////////////////////////////////////////////////////////
/// @fn addRequest( string uID, string startDate, string endDate )
/// @brief This is a function that stores requests to a file 
/// @param string uID is the user ID of the user requesting leave
/// @param string startDate is the first date the user wants off
/// @param string endDate is the last date the user wants off
/// @param string leaveType is the type of leave to request
///   "sick" = sick leave
///   "vacation" = vacation leave
/// @ret true if the adding went alright, false if the user made a request
///   when they did not have enough balance to do so
/// @note the parameter today must be in "MM/DD" where MM is the month number
///   and DD is the day number
/// @note all dates between and including startDate and endDate will be
///   recorded as a request for vacation dates
///////////////////////////////////////////////////////////////////////////////
bool requestTime::addRequest( string uID, string startDate, string endDate, string leaveType ) {
  
  string today = get_today();

  leaveType = str_tolower(leaveType);

  if (leaveType != SICK_LEAVE && leaveType != VACATION_LEAVE) {

    throw Exception(244, "\"" + leaveType + "\" is an invalid leave type. (class requestTime, addRequest())");

  }

  string vacationRequest = today + "|" + startDate + "|" + endDate + "|" + leaveType;

  //Adds a request to the database in the form of
  // RR/RR|SS/SS|EE/EE
  DATABASE.add_entry( uID, PENDING_APPROVAL, vacationRequest );
  
  //Now add the same line about the request to the history
  //DATABASE.add_entry( uID, REQUEST_HISTORY, vacationRequest );
  // JEREMY EDIT: I think the duplication is unnecessary. 
   
  //Saves our changes and close the database
  DATABASE.save_file();

  return true;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn setToday()
/// @brief Fetches the current time of the system and parses the day and month 
///   into our MM/DD format and stores it in m_today
///////////////////////////////////////////////////////////////////////////////
void requestTime::setToday() {
  
  //Creates a time object
  time_t rawtime;
  
  //Creates a struct to hold our time information
  struct tm * timeinfo;

  //Gets the current time as a time_t object
  time( &rawtime );

  //returns a pointer to a tm structure with the information of the pointer 
  //passed in filled in
  timeinfo = localtime( &rawtime );

  // Sets "today" in the MM/DD format.
  // +1 to the month because it's stored as 0-11 instead of 1-12.
  string today = int_to_str(timeinfo->tm_mon + 1, 2) + "/" + int_to_str(timeinfo->tm_mday, 2);
  
  m_today = today;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn get_today()
/// @brief gets today's date as stored by the validate class on instantiation
/// @return string containing today's date in MM/DD format
///////////////////////////////////////////////////////////////////////////////
string requestTime::get_today() {
  
  // If the day changes between requests, we want to make sure it shows up.
  setToday();

  return m_today;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn time_t str_to_time(string date)
/// @brief returns a time_t object made from the passed in string
/// @param date is a string in the format MM/DD/YYYY to turn into a time_t
/// @ret time_t ojbect made from the passed in date
///////////////////////////////////////////////////////////////////////////////
time_t requestTime::str_to_time(string date) {

  // Storage for what we return.
  time_t return_time;

  // Store the current time, too.
  time_t now;
  time(&now);

  // Current tm, too.
  tm now_tm;
  // Yeah, I'm dereferencing a function.
  now_tm = *localtime(&now);

  // tm structure for easier storage.
  // Initialize to "now" for day/month/year, if any are missing.
  tm date_tm(now_tm);

  // We don't need these three values.
  date_tm.tm_hour = 0;
  date_tm.tm_min = 0;
  date_tm.tm_sec = 0;

  // Clear out any ambiguity.
  date = str_strip(date, " ", true, true, true);
  date = str_replace_all(date, "-", "/");
  date = str_replace_all(date, ".", "/");
  date = str_replace_all(date, "\\", "/");
  date = str_replace_all(date, "|", "/");
  date = str_replace_all(date, "_", "/");

  vector<string> values = str_find_lines(date, "/", false);

  if (values.size() >= 1) {

    // tm stores months as 0-11
    date_tm.tm_mon = str_to_int(values[0]) - 1;

  }

  if (values.size() >= 2) {

    date_tm.tm_mday = str_to_int(values[1]);

  }

  if (values.size() >= 3) {

    // tm stores years as the distance from 1900
    date_tm.tm_year = str_to_int(values[2]) - 1900;

  }

  return_time = mktime(&date_tm);

  return return_time;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn int num_days(string start, string end)
/// @brief gets the number of days between the start string and the end string
/// @param string start is the start date
/// @param string end is the end date
/// @ret int that is the number of days between the 2 dates
///////////////////////////////////////////////////////////////////////////////
int requestTime::num_days(string start, string end) {

  // Just convert to time_t, because it's easier that way.
  return num_days( str_to_time( start ), str_to_time( end ) );

}

///////////////////////////////////////////////////////////////////////////////
/// @fn int num_days(time_t start, time_t end)
/// @brief gets the number of days between the start time and end time
/// @param time_t start is the start time_t object
/// @param time_t end is the end time_t object
/// @return int that is the number of days betwee the 2 dates
///////////////////////////////////////////////////////////////////////////////
int requestTime::num_days(time_t start, time_t end) {

  time_t diff = difftime(end, start);

  // Store whether the original value was positive or negative.
  int sign = 1;

  // A time_t value needs to be positive to convert properly
  // to the tm struct we're using.
  if (diff < 0) {

    // We're negative.
    sign = -1;

    // Make the difference positive.
    diff = -diff;

  }

  // Get the local time equivalent of the difference
  // between the two times.
  tm diff_tm = *localtime(&diff);

  // Pull the days from everything.
  // +2 to INCLUDE both the start and end dates.
  int days = (diff_tm.tm_yday + 2) * sign;

  // Return the number of days elapsed since January 1 in
  // the fictional year designated by the difference between
  // the two dates. Should give us the number of days elapsed.
  return days;

}