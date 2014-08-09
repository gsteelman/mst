///BEGINNING OF FILE-----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file validate.cpp
/// @auth Gary Steelman, Jacob Alyea
/// @edit 25 Apr 2009
/// @brief This is the implementation for all of the validation functions to be used
///   in the functions elsewhere
///////////////////////////////////////////////////////////////////////////////

#include "validate.h"

#include "../common.h"

#include "../requestTime/requestTime.h"

#include "../library/exception.h" //Gives us the exception functionality
                                  //THIS CLASS USES EXCEPTIONS 70-...

#include "../library/strmanip.h" //Gives us string manipulation functions

#include "../common.h" //Gives us our path constants and databse constants

#include <ctime> //Gives us the ctime library

//#include <iostream> //Gives us the cout ability! Huzzah!
//using std::cout;
//using std::cin;
//using std::endl;

///////////////////////////////////////////////////////////////////////////////
/// @fn validate( void )
/// @brief the default constructor for the validate class
///////////////////////////////////////////////////////////////////////////////
validate::validate() {
  
  //Sets today's date
  setToday();

  //Creates us a new rules system
  m_rules = new rulesSystem( RULESET_PATH );

  // Ensure the global database is open.
  DATABASE.open(DATABASE_PATH);

}

///////////////////////////////////////////////////////////////////////////////
/// @fn ~validate( void )
/// @brief the default destructor for the validate class
///////////////////////////////////////////////////////////////////////////////
validate::~validate() {

  //Deletes m_rules as to not have a memory leak
  delete m_rules;

  // Save our work when we're done.
  DATABASE.save_file();

}

///////////////////////////////////////////////////////////////////////////////
/// @fn bool validateLeave( string startDate, string endDate, rulesSystem &rules )
/// @brief checks a leave range of dates against the rules in the passed rules
///   and then returns whether or not the range follows the rules
/// @param string startDate is the start date for the requested vacation 
/// @param string endDate is the end date for the requested vacation
/// @param rulesSystem &rules is rules system to check the dates against for
///   verification of leave time
/// @return false if the request is denied for any reason
/// @return true if the request is accepted
/// @note the parameters startDate and endDate must be in "MM/DD" where MM is 
///   the month number and DD is the day number
///////////////////////////////////////////////////////////////////////////////
bool validate::validateLeave( string uID, string request ) {

  vector<string> request_vec = parse_request(request);

  string startDate    = request_vec[1];
  string endDate      = request_vec[2];
  string requestType  = request_vec[3];

  //First make sure both the start and end dates are valid dates
  if ( validateDate( startDate ) == false ) {
    
    return false;
  
  }

  if ( validateDate( endDate ) == false ) {
    
    return false;
  
  }

  // Number of days requesting off.
  int request_days = num_days( startDate, endDate );
  int days_to_start = num_days( get_today(), startDate ) - 1;

  // TEST 0
  // If they don't have enough time available in the leave type
  // of their request, they fail.
  if (requestType == SICK_LEAVE) {

    int time_available = str_to_int( DATABASE.get_entry(uID, SICK_LEAVE_BALANCE) );

    // Not enough time.
    if (time_available < request_days) {

      return false;

    }

  } else if (requestType == VACATION_LEAVE) {

    int time_available = str_to_int( DATABASE.get_entry(uID, VACATION_LEAVE_BALANCE) );

    // Not enough time.
    if (time_available < request_days) {

      return false;

    }

  } else {

    // Not a valid leave type.
    return false;

  }

  //TEST 1
  //If the number of days notice is fewer than the rules allow, fail
  //leave time validation
  if ( ( days_to_start ) < m_rules->getDaysNotice() ) {
    
    return false;
  
  }

  //TEST 2
  //Now we're going to make sure we're not requesting too much time off in a row
  //This will just check the size of the leaveRequestDates against the rule for
  //amount of time off in a row
  if ( request_days > m_rules->getDaysConsecutive() ) {
    
    return false;
  
  }

  //TEST 3
  //And now we need to make sure that we're not going to leave the company
  //Trying to run itself with no employees left
  //This I'm not sure how we're going to implement yet, but I'll figure it out
  //I think I've got this part figured out. There's a field in the scope uID
  //in the database that is called ON_VACATION that will store a 1 or a 0
  //to represent if that user is on vacation. This item will be edited somewhere
  //that isn't here.
  //We'll just get all the entries in all scopes in that field and count the
  //number of 1s >_>

  //THIS NEEDS TO BE CHANGED TO JUST CHECK THE CURRENT DATE VS THE DATES OF
  //PEOPLE WHO ARE ON VACATION, lolk
  
  double usersOnVacation = 0;

  vector<string> users = DATABASE.get_scopes();
  vector<string> leaveRequest;

  //We'll run through each user
  for ( int x = 0; x < users.size(); x++ ) {
   
    //Gets all of the approved requests for the user
    leaveRequest = DATABASE.get_entries( users.at( x ), APPROVED_REQUESTS );

    // Hax the vector from the request list into the last
    // approved request in the list.
    leaveRequest = parse_request(leaveRequest.back());

    if (leaveRequest[0] != DEFAULT_ENTRY) {

      // Pull out the start/end of the most recent approved request.
      string request_start = leaveRequest[1];
      string request_end = leaveRequest[2];

      // Calculate the length of the request.
      int request_length = num_days(request_start, request_end);

      // And the number of days from the start of the request to today.
      int start_to_today = num_days(request_start, get_today());

      // If today is between the start and end of the request...
      if (start_to_today > 0 && start_to_today <= request_length) {

        // They're on vacation.
        usersOnVacation++;

      }

    } /* if (leave_request[0] != DEFAULT_ENTRY) */
   
  }
  
  if ( usersOnVacation >= m_rules->getMaxPeopleOff() ) {
  
    return false;
  
  }

  // Vector to store the blackout days.
  vector<string> blackout = m_rules->getBlackoutList();
  
  //TEST 4
  //And finally now we're going to make sure that we're not trying to leave on 
  //A blackout date. This should run through all of the blackoutlist for each
  //date in the request list, not efficient, but the easiest way
  for ( int j = 0; j < blackout.size(); j++ ) {

    int days_to_blackout = num_days(startDate, blackout[j]);

    //And if the date in the request list matches any in the blackout list
    //We return false because employees can't take a vacation on a 
    //blackout date
    if ( days_to_blackout > 0 &&  // A day in the past doesn't matter to us.
         days_to_blackout <= request_days ) {

      return false;

    }
    
  } //end for loop

  return true;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn validateDate( string date )
/// @brief Checks the passed date for validity in format and numbering
/// @param string date is the date to be checked
/// @return true if the date is valid (in "MM/DD" format with possible real days)
/// @return false if the date is invalid
///////////////////////////////////////////////////////////////////////////////
bool validate::validateDate( string date ) {
  
  int month = 0;           //Number of the month we were sent to check
  int day = 0;             //Number of the day we were sent to check
  int monthsInAYear = 12;  //Number of months in a year

  //This is an array of the number of days in each month, that is:
  //31 days in January, 28 (or 29) in February, 31 in March, etc.
  int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  //Makes sure the date is only 5 characters long, that is, "MM/DD"
  if ( date.length() != 5 ) { return false; }

  //Grabs the 2 left characters of the date and converts to an integer
  month = str_to_int( str_left( date, 2 ) );

  //Grabs the 2 right characters of the date and converts to an integer
  day = str_to_int( str_right( date, 2 ) );
  
  //Checks to make sure the month number is a valid number
  if ( month > monthsInAYear || month <= 0 ) {

    return false;
  
  //checks to make sure the day number is valid
  } else if ( day > daysInMonth[month - 1] || day <= 0 ) {

    return false;
  		
  }

  return true;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn vector<string> getDates( string startDate, string endDate )
/// @brief Returns a vector of strings that contain all the dates between 
///   startDate and endDate, inclusively
/// @param string startDate is the start date for the requested vacation 
/// @param string endDate is the end date for the requested vacation
/// @pre the dates being passed in have already been validated
///   using the validateDate function
/// @ret vector of strings that contain all dates between startDate and endDate
///   inclusive
/// @note the parameters startDate and endDate must be in "MM/DD" where MM is 
///   the month number and DD is the day number
/// @note all of the strings (dates) in the vector returned will be in the 
///   format of "MM/DD"
///////////////////////////////////////////////////////////////////////////////
vector<string> validate::getDates( string startDate, string endDate ) {

  //if ( validateDate( startDate ) == false || validateDate( endDate ) == false ) {

    //OUTPUT.insert_line(OUTPUT.num_lines(), "The dates sent into getDates fail. This is why we're infinite looping probably k.\n";

  //}

  //Grabs the 2 left characters of the dates and converts to integers
  int startMonth = str_to_int( str_left( startDate, 2 ) );
  int   endMonth = str_to_int( str_left( endDate, 2 ) );

  //Grabs the 2 right characters of the dates and converts to integers
  int startDay = str_to_int( str_right( startDate, 2 ) );
  int   endDay = str_to_int( str_right( endDate, 2 ) );

  //This will be our day to begin each iteration's pushing of dates into the
  //dates vector
  int startIterationDay = 0;

  //An array of 12 items (0 to 11) telling us how many days are in each month
  int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  //This will be used so we can deal with request rollovers from month to month
  //And from december into january
  int currentIterationMonth = startMonth; 
  
  //This will be our flag for telling us we're done loading all of the dates 
  //between start and end into the vector. 1=done, 0=not done yet
  bool Done = false;
  
  //This will be our flag for telling us when we're rolling over from one month
  //to another, default to false so we can start from the middle of a random
  //month 
  bool fromAnotherMonth = false;

  //This will be used for pushing onto the dates vector
  string currentIterationDate = "";

  //This will store all of the dates between startDate and endDate, inclusively
  vector<string> dates;

  //While we're not done
  while ( !Done ) {

    //This should start us on the correct day, be it at the beginning of the
    //month due to rollover or in the middle of some random month because that
    //is the day that was requested
    if ( fromAnotherMonth ) {
      
      startIterationDay = 1;
    
    } else {
      
      startIterationDay = startDay;
    
    }
      
    //This should run from either the start day or the beginning of a 
    //the month to the number of days in the month or the endDate
    //Whichever happens to come first
    for ( int x = startIterationDay; x <= daysInMonth[currentIterationMonth - 1]; x++ ) {
      
      //We want to generate dates like: "0M/0D" or "0M/DD"
      if ( currentIterationMonth < 10 ) {

        //We want to generate dates like: "0M/0D"
        if ( x < 10 ) {

          currentIterationDate = "0" + int_to_str( currentIterationMonth ) + "/0" + int_to_str( x );
        
        //We want to generate dates like "0M/DD"
        } else {

          currentIterationDate =  "0" + int_to_str( currentIterationMonth ) + "/" + int_to_str( x );

        }
      
      //We want to generate dates like: "MM/0D" or "MM/DD"
      } else {

        //We want to generate dates like: "MM/0D"
        if ( x < 10 ) {

          currentIterationDate = int_to_str( currentIterationMonth ) + "/0" + int_to_str( x );

        }

        //We want to generate dates like "MM/DD"
        else {

          currentIterationDate = int_to_str( currentIterationMonth ) + "/" + int_to_str( x );

        }

      } //End date generation //end else
            
      //Push proper date in form of MM/DD into the dates vector! Yaaay!
      dates.push_back( currentIterationDate );

      //If we've arrived at the endDate, we need to stop pushing more 
      //dates into the vector, we we change our Done flag to 1 to
      //stop us once we go back to the top of the while loop

      /*
      //The stuff in this comment block is the original stuff, the rest below the loop
      OUTPUT.insert_line(OUTPUT.num_lines(), "currentiterationdate: " << currentIterationDate << "endDate: " << endDate << "\n";
      if ( currentIterationDate == endDate ) { Done = true; break; }
      
      //However, if we still haven't hit the endDate and we're at the
      //end of the month, we need to set up to rollover to the next month
      else if ( x == daysInMonth[currentIterationMonth - 1] ) {

        fromAnotherMonth = true;       //We are coming from another month
        currentIterationMonth+=1;   //We need to start in the next month

      }
      
      //And for added rollover ability, if we get to the end of December
      //and we need to roll into January, we set the month iteration back
      //to 1, for the first month
      if ( currentIterationMonth == 13 ) { currentIterationMonth = 1; break; }*/
      
    } //End for loop

      //However, if we still haven't hit the endDate and we're at the
      //end of the month, we need to set up to rollover to the next month
      //else if ( x == daysInMonth[currentIterationMonth - 1] ) {

        fromAnotherMonth = true;       //We are coming from another month
        currentIterationMonth+=1;   //We need to start in the next month

      //}
      if ( currentIterationDate == endDate ) { Done = true; break; }
      //And for added rollover ability, if we get to the end of December
      //and we need to roll into January, we set the month iteration back
      //to 1, for the first month
      if ( currentIterationMonth == 13 ) { currentIterationMonth = 1; }

  } //end while loop

  return dates; //Sends back the vector of dates we workd so hard to get

} //end getDates()

///////////////////////////////////////////////////////////////////////////////
/// @fn setToday()
/// @brief Fetches the current time of the system and parses the day and month 
///   into our MM/DD format and stores it in m_today
///////////////////////////////////////////////////////////////////////////////
void validate::setToday() {
  
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

  if( validateDate( today ) == false ) {
    
    throw Exception( 70, "The date set on your computer is invalid. Exception in (class validate, setToday()" );
  
  }
  
  m_today = today;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn bool managerApproval( string uID, bool approved )
/// @brief approves or disapproves the user with uID based on the approved bool
/// @param string uID is the user ID to approve or disapprove
/// @param bool approved
///   true = user approved
///   false = user denied
/// @pre the user uID must have made a request 
/// @return true if the approval process went alright
/// @return false if the user had not previously made a request
///////////////////////////////////////////////////////////////////////////////
bool validate::managerApproval( string uID, bool approved ) {

  //Storage of requests, one at a time
  vector<string> vacationRequest;

  string approvedRequest = "";
  string deniedRequest = "";

  vector<string> users;

  // If uID is blank, get all users. Otherwise, just the one passed in.
  if (uID == "") {

    users = DATABASE.get_scopes();

  } else {

    users.push_back( uID );

  }
  
  //This will approve requests.
  if ( approved ) {
  
    //We'll run through each user
    for ( int x = 0; x < users.size(); x++ ) {
      
      //get the entries for the current username and put them into a temp vector
      vacationRequest = DATABASE.get_entries( users.at( x ), PENDING_APPROVAL );
      
      if ( vacationRequest.at( 0 ) == DEFAULT_ENTRY ) {
      
        //Do nothing because this employee has no pending requests
      
      } else {
      
        //Since each user may have more than 1 request at a time, we're going 
        //to run through each request the current iteration's user has
        while ( vacationRequest.empty() == false ) {

          string request = vacationRequest[0];

          vector<string> request_vec = parse_request(request);

          // Rules are overridden if validation comes back false.
          bool rules_overridden = !validateLeave(uID, request);
        
          //This gets us a string in the form of RR/RR|SS/SS|EE/EE|T|AA/AA
          approvedRequest = request + "|" + get_today();

          // If the manager overrides the rules, it needs to be logged.
          if (rules_overridden) {

            approvedRequest += "|" + RULES_OVERRIDDEN;

          }

          //Get the number of days the request is
          int vacaLen = num_days( request_vec[1], request_vec[2] );
          
          //Add the current pending request to the approved requests field
          DATABASE.add_entry( users.at( x ), APPROVED_REQUESTS, approvedRequest );

          //Now update the user's vacation balance with vacaLen
          if ( request_vec[3] == SICK_LEAVE ) {

            //This means it is a sick leave request
            //Multiply the vacation length by -1 to make it a subtraction
            addSickLeave( users.at( x ), ( vacaLen * -1 ) );

          } else if ( request_vec[3] == VACATION_LEAVE ) {

            //This means it is a vacation leave request
            //Multiply the vacation length by -1 to make it a subtraction
            addVacationLeave( users.at( x ), vacaLen * -1 );

          }

          //Now remove the request from the pending requests section
          DATABASE.delete_entry(users.at( x ), PENDING_APPROVAL );
          
          //And now clear the request from the temp vector
          vacationRequest.erase( vacationRequest.begin() );
        
        }//end while
      
      }//end else
      
    }//end for
  
  // Deny requests.
  } else if ( !approved ) {
  
    //We'll run through each user
    for ( int x = 0; x < users.size(); x++ ) {
      
      //get the entries for the current username and put them into a temp vector
      vacationRequest = DATABASE.get_entries( users.at( x ), PENDING_APPROVAL );
      
      if ( vacationRequest.at( 0 ) == DEFAULT_ENTRY ) {
      
        //Do nothing because this employee has no pending requests
      
      } else {
      
        //Since each user may have more than 1 request at a time, we're going 
        //to run through each request the current iteration's user has
        while ( vacationRequest.empty() == false ) {
        
          //This gets us a string in the form of RR/RR|SS/SS|EE/EE|T|DD/DD
          approvedRequest = vacationRequest.at( 0 ) + "|" + get_today();
          
          //Add the current pending request to the disapproved requests field
          DATABASE.add_entry( users.at( x ), DISAPPROVED_REQUESTS, approvedRequest );

          //Now remove the request from the pending requests section
          DATABASE.delete_entry( users.at( x ), PENDING_APPROVAL );
          
          //And now clear the request from the temp vector
          vacationRequest.erase( vacationRequest.begin() );
        
        }//end while
      
      }//end else
      
    }//end for
  
  }//end else if

  // SAVE CHANGES.
  DATABASE.save_file();

  return true;

}//end managerApproval()

///////////////////////////////////////////////////////////////////////////////
/// @fn void displayRequest( string uID )
/// @brief Displays any pending leave requests for a user 
/// @param string uID is the user ID to see the pending requests of
/// @note send in a blank ("") uID to se all pending requests for approval
/// @note the displayed text will be sent to the command prompt
///////////////////////////////////////////////////////////////////////////////
void validate::displayPendingRequest( string uID ) {

  //Storage of requests, one at a time
  vector<string> vacationRequest;

  // Store the users for whom we are retrieving requests.
  // If uID == "", this is all users in the database, otherwise it is JUST the uID
  vector<string> users;

  if (uID == "") {

    // Since we store SSOs as scopes, we just get the scopes, 
    //and we have all the users.
    users = DATABASE.get_scopes();

  } else {

    // Otherwise, just add uID
    users.push_back(uID);

  }

  OUTPUT.insert_line(OUTPUT.num_lines(), "PENDING REQUESTS\r");
  OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");
  
  // Run through each user whose requests we need.
  for ( int x = 0; x < users.size(); x++ ) {
    
    //get the entries for a username and put them into a temp vector
    //This will have a vector of strings like this:
    //RR/RR|SS/SS|EE/EE|T
    //RR/RR|SS/SS|EE/EE|T
    vacationRequest = DATABASE.get_entries( users.at( x ), PENDING_APPROVAL );
    
    if ( vacationRequest.at( 0 ) == DEFAULT_ENTRY ) {
    
      OUTPUT.insert_line(OUTPUT.num_lines(), users.at( x ) + "\r");
      OUTPUT.insert_line(OUTPUT.num_lines(), "NONE\r");
      OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");
    
    } else {
      
      //Since each user may have more than 1 request at a time, we need to
      //display them all
      while ( vacationRequest.empty() == false ) {

        vector<string> request_vec = parse_request(vacationRequest[0]);
        
        //here we will need to do some parsing.
        //"Employee NAME requested for SS/SS to EE/EE on RR/RR and was approved on AA/AA"
        OUTPUT.insert_line(OUTPUT.num_lines(), users.at( x ) + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[3] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[1] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[2] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[0] + "\r");
       
        if ( validateLeave( users[x], vacationRequest[0] ) ) {

          OUTPUT.insert_line(OUTPUT.num_lines(), "PASSED\r");

        } else {

          OUTPUT.insert_line(OUTPUT.num_lines(), "FAILED\r");

        }

        OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");

        //Now that we've displayed the request, get it out of the vector of
        //requests and move to the next one in the same user
        vacationRequest.erase( vacationRequest.begin() );
      
      }//end while
    
    }//end else
    
  }//end for

}

///////////////////////////////////////////////////////////////////////////////
/// @fn get_today( )
/// @brief gets today's date as stored by the validate class on instantiation
/// @return string containing today's date in MM/DD format
///////////////////////////////////////////////////////////////////////////////
string validate::get_today( ) {

  // Make sure today is accurate.
  setToday();
  
  return m_today;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void setRules( rulesSystem *rules )
/// @brief sets the rules to be used by the system
/// @param rulesSystem *rules is a pointer to the rules system to be used
///////////////////////////////////////////////////////////////////////////////
void validate::setRules( rulesSystem *rules ) {
  
  m_rules = rules;

}

///////////////////////////////////////////////////////////////////////////////
/// @fn time_t str_to_time(string date)
/// @brief returns a time_t object made from the passed in string
/// @param date is a string in the format MM/DD/YYYY to turn into a time_t
/// @ret time_t ojbect made from the passed in date
///////////////////////////////////////////////////////////////////////////////
time_t validate::str_to_time(string date) {

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
int validate::num_days(string start, string end) {

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
int validate::num_days(time_t start, time_t end) {

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

///////////////////////////////////////////////////////////////////////////////
/// @fn void displayAllRequestHistory( string uID ) 
/// @brief displays the request history for the specified user ID
/// @param the user ID of the user to view the request history of
/// @note pass in a blank string to show all request history for all users
/// @note this will display both denied and approved requests
///////////////////////////////////////////////////////////////////////////////
void validate::displayAllRequestHistory( string uID ) {

  displayPendingRequest( uID );
  displayApprovedRequestHistory( uID );
  displayDeniedRequestHistory( uID );

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void displayDeniedRequestHistory( string uID )
/// @brief displays the denied request history for the specified user ID
/// @param the user ID of the user to view the denied request history of
/// @note pass in a blank string to show denied request history for all users
///////////////////////////////////////////////////////////////////////////////
void validate::displayDeniedRequestHistory( string uID ) {

  //Storage of requests, one at a time
  vector<string> vacationRequest;

  // Store the users for whom we are retrieving requests.
  // If uID == "", this is all users in the database, otherwise it is JUST the uID
  vector<string> users;

  if (uID == "") {

    // Since we store SSOs as scopes, we just get the scopes, 
    //and we have all the users.
    users = DATABASE.get_scopes();

  } else {

    // Otherwise, just add uID
    users.push_back(uID);

  }
  
  OUTPUT.insert_line(OUTPUT.num_lines(), "DENIED REQUESTS\r");
  OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");

  // Run through each user whose requests we need.
  for ( int x = 0; x < users.size(); x++ ) {
    
    //get the entries for a username and put them into a temp vector
    //This will have a vector of strings like this:
    //RR/RR|SS/SS|EE/EE|T|AA/AA
    //RR/RR|SS/SS|EE/EE|T|AA/AA
    vacationRequest = DATABASE.get_entries( users.at( x ), DISAPPROVED_REQUESTS );
    
    if ( vacationRequest.at( 0 ) == DEFAULT_ENTRY ) {
    
      OUTPUT.insert_line(OUTPUT.num_lines(), users.at( x ) + "\r");
      OUTPUT.insert_line(OUTPUT.num_lines(), "NONE\r");
      OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");
    
    } else {
      
      //Since each user may have more than 1 request at a time, we need to
      //display them all
      while ( vacationRequest.empty() == false ) {

        vector<string> request_vec = parse_request(vacationRequest[0]);
        
        //here we will need to do some parsing.
        //"Employee NAME requested for SS/SS to EE/EE on RR/RR and was approved on AA/AA"
        OUTPUT.insert_line(OUTPUT.num_lines(), users.at( x ) + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[3] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[1] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[2] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[0] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[4] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");

        //Now that we've displayed the request, get it out of the vector of
        //requests and move to the next one in the same user
        vacationRequest.erase( vacationRequest.begin() );
      
      }//end while
    
    }//end else
    
  }//end for

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void displayApprovedRequestHistory( string uID )
/// @brief displays the approved request history for the specified user ID
/// @param the user ID of the user to view the approved request history of
/// @note pass in a blank string to show approved request history for all users
///////////////////////////////////////////////////////////////////////////////
void validate::displayApprovedRequestHistory( string uID ) {

  //Storage of requests, one at a time
  vector<string> vacationRequest;

  // Store the users for whom we are retrieving requests.
  // If uID == "", this is all users in the database, otherwise it is JUST the uID
  vector<string> users;

  if (uID == "") {

    // Since we store SSOs as scopes, we just get the scopes, 
    //and we have all the users.
    users = DATABASE.get_scopes();

  } else {

    // Otherwise, just add uID
    users.push_back(uID);

  }
  
  OUTPUT.insert_line(OUTPUT.num_lines(), "APPROVED REQUESTS\r");
  OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");

  // Run through each user whose requests we need.
  for ( int x = 0; x < users.size(); x++ ) {
    
    //get the entries for a username and put them into a temp vector
    //This will have a vector of strings like this:
    //RR/RR|SS/SS|EE/EE|T|AA/AA
    //RR/RR|SS/SS|EE/EE|T|AA/AA
    vacationRequest = DATABASE.get_entries( users.at( x ), APPROVED_REQUESTS );
    
    if ( vacationRequest.at( 0 ) == DEFAULT_ENTRY ) {
    
      OUTPUT.insert_line(OUTPUT.num_lines(), users.at( x ) + "\r");
      OUTPUT.insert_line(OUTPUT.num_lines(), "NONE\r");
      OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");
    
    } else {
      
      //Since each user may have more than 1 request at a time, we need to
      //display them all

// **********************************************************
// For the love of things holy, replace this with a for loop.
// You're just ASKING to thrash memory by deleting the first
// entry and re-indexing the vector every loop iteration.
// **********************************************************
      while ( vacationRequest.empty() == false ) {

        string employee = users[x];
        vector<string> request_vec = parse_request(vacationRequest[0]);
        
        //here we will need to do some parsing.
        //"Employee NAME requested for SS/SS to EE/EE on RR/RR and was approved on AA/AA"
        OUTPUT.insert_line(OUTPUT.num_lines(), users.at( x ) + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[3] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[1] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[2] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[0] + "\r");
        OUTPUT.insert_line(OUTPUT.num_lines(), request_vec[4] + "\r");

        // If we have a sixth entry, that means we have a rule override.
        if (request_vec.size() >= 6) {

          OUTPUT.insert_line(OUTPUT.num_lines(), "RULES OVERRIDDEN\r");

        }
        
        OUTPUT.insert_line(OUTPUT.num_lines(), "***\r");

        //Now that we've displayed the request, get it out of the vector of
        //requests and move to the next one in the same user
        vacationRequest.erase( vacationRequest.begin() );
      
      }//end while
    
    }//end else
    
  }//end for

}

///////////////////////////////////////////////////////////////////////////////
/// @fn int getVacationLeave( uID )
/// @brief returns an int equal to the amount of leave the specified user has
/// @param string uID is the ID of the user to get the leave of
/// @ret int equal to the amount of leave the specified user has
///////////////////////////////////////////////////////////////////////////////
unsigned int validate::getVacationLeave( string uID ) {

  return str_to_int( DATABASE.get_entry( uID, VACATION_LEAVE_BALANCE ) );

}

///////////////////////////////////////////////////////////////////////////////
/// @fn int getSickLeave( uID )
/// @brief returns an int equal to the amount of leave the specified user has
/// @param string uID is the ID of the user to get the leave of
/// @ret int equal to the amount of leave the specified user has
///////////////////////////////////////////////////////////////////////////////
unsigned int validate::getSickLeave( string uID ) {
  
  return str_to_int( DATABASE.get_entry( uID, SICK_LEAVE_BALANCE ) );

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void addVacationLeave( string uID, int toAdd )
/// @brief adds the specified number to the balance of the specified user
/// @param string uID is the ID of the user to add balance to
/// @param int toAdd is the balance to add to the specified user's balance
/// @note if uID is a blank string, the amount toAdd will be added to all 
///   users in the system
/// @note make toAdd a negative number to subtract time instead of adding
///////////////////////////////////////////////////////////////////////////////
void validate::addVacationLeave( string uID, int toAdd ) {
  
  //Storage of requests, one at a time
  vector<string> users;

  //temp hold for the current balance before the changes to the balance
  int currBal = 0;
  
  // If uID is blank, get all users. Otherwise, just the one passed in.
  if (uID == "") {

    users = DATABASE.get_scopes();

  } else {

    users.push_back( uID );

  }
  
  for ( int x = 0; x < users.size(); x++ ) {

    //Get the users current balance
    currBal = str_to_int( DATABASE.get_entry( users.at( x ), VACATION_LEAVE_BALANCE ) );

    //Get the new balance with the added in value
    currBal += toAdd;

    //Clear the old entry
    DATABASE.clear_field( users.at( x ), VACATION_LEAVE_BALANCE );

    //Write the new entry
    DATABASE.add_entry( users.at( x ), VACATION_LEAVE_BALANCE, int_to_str( currBal ) );

  }
  
  //SAVE CHANGES.
  DATABASE.save_file();

}

///////////////////////////////////////////////////////////////////////////////
/// @fn void addSickLeave( string uID, int toAdd )
/// @brief adds the specified number to the balance of the specified user
/// @param string uID is the ID of the user to add balance to
/// @param int toAdd is the balance to add to the specified user's balance
/// @note if uID is a blank string, the amount toAdd will be added to all 
///   users in the system
/// @note make toAdd a negative number to subtract time instead of adding
///////////////////////////////////////////////////////////////////////////////
void validate::addSickLeave( string uID, int toAdd ) {

  //Storage of requests, one at a time
  vector<string> users;

  //temp hold for the current balance before the changes to the balance
  int currBal = 0;
  
  // If uID is blank, get all users. Otherwise, just the one passed in.
  if (uID == "") {

    users = DATABASE.get_scopes();

  } else {

    users.push_back( uID );

  }
  
  for ( int x = 0; x < users.size(); x++ ) {

    //Get the users current balance
    currBal = str_to_int( DATABASE.get_entry( users.at( x ), SICK_LEAVE_BALANCE ) );

    //Get the new balance with the added in value
    currBal+=toAdd;

    //Clear the old entry
    DATABASE.clear_field( users.at( x ), SICK_LEAVE_BALANCE );

    //Write the new entry
    DATABASE.add_entry( users.at( x ), SICK_LEAVE_BALANCE, int_to_str( currBal ) );

  }
  
  //SAVE CHANGES.
  DATABASE.save_file();

}

vector<string> validate::parse_request(string request) {

  // Find lines using the pipe as a delim instead of \n. This just
  // breaks all the entries into separate pieces.
  return str_find_lines(request, "|", false);

}

///END OF FILE-----------------------------------------------------------------