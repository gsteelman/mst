///BEGINNING OF FILE-----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file validate.h
/// @auth Gary Steelman, Jacob Alyea
/// @edit 15 Apr 2009
/// @brief This is the declaration for all of the validation functions to be used
///   in the functions elsewhere
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn validate( void )
/// @brief the default constructor for the validate class
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~validate( void )
/// @brief the default destructor for the validate class
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn validateDate( string date )
/// @brief Checks the passed date for validity in format and numbering
/// @param string date is the date to be checked
/// @return true if the date is valid (in "MM/DD" format with possible real days)
/// @return false if the date is invalid
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool validateLeave( string startDate, string endDate )
/// @brief checks a leave range of dates against the rules in the passed rules
///   and then returns whether or not the range follows the rules
/// @param string startDate is the start date for the requested vacation 
/// @param string endDate is the end date for the requested vacation
/// @param rulesSystem &rules is rules system to check the dates against for
///   verification of leave time
/// @return false if the request is denied for any reason
/// @return true if the request is accepted
/// @pre Assumes a rulesSystem has been defined by using setRules()
/// @note the parameters startDate and endDate must be in "MM/DD" where MM is 
///   the month number and DD is the day number
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn vector<string> getDates( string startDate, string endDate )
/// @brief Returns a vector of strings that contain all the dates between 
///   startDate and endDate, inclusively
/// @param string startDate is the start date for the requested vacation 
/// @param string endDate is the end date for the requested vacation
/// @pre Assumes the dates being passed in have already been validated
///   using the validateDate function
/// @note the parameters startDate and endDate must be in "MM/DD" where MM is 
///   the month number and DD is the day number
/// @note all of the strings (dates) in the vector returned will be in the 
///   format of "MM/DD"
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool managerApproval( string uID, bool approved )
/// @brief approves or disapproves the user with uID based on the approved bool
/// @param string uID is the user ID to approve or disapprove
/// @note send in a blank ("") uID to see all pending requests for approval
/// @param bool approved
///   true = user approved
///   false = user denied
/// @pre the user uID must have made a request 
/// @return true if the approval process went alright
/// @return false if the user had not previously made a request
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void displayRequest( string uID )
/// @brief Displays any pending leave requests for a user 
/// @param string uID is the user ID to see the pending requests of
/// @note send in a blank ("") uID to se all pending requests for approval
/// @note the displayed text will be sent to the command prompt
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setToday()
/// @brief Grabs the current time of the system and parses the day and month 
///   into our MM/DD format and stores it in m_today
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn string get_today( )
/// @brief gets today's date as stored by the validate class on instantiation
/// @return string containing today's date in MM/DD format
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setRules( rulesSystem *rules )
/// @brief sets the rules to be used by the system
/// @param rulesSystem *rules is a pointer to the rules system to be used
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn time_t str_to_time(string date)
/// @brief returns a time_t object made from the passed in string
/// @param date is a string in the format MM/DD/YYYY to turn into a time_t
/// @ret time_t ojbect made from the passed in date
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn int num_days(time_t start, time_t end)
/// @brief gets the number of days between the start time and end time
/// @param time_t start is the start time_t object
/// @param time_t end is the end time_t object
/// @return int that is the number of days betwee the 2 dates
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn int num_days(string start, string end)
/// @brief gets the number of days between the start string and the end string
/// @param string start is the start date
/// @param string end is the end date
/// @ret int that is the number of days between the 2 dates
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn int getVacationLeave( uID )
/// @brief returns an int equal to the amount of leave the specified user has
/// @param string uID is the ID of the user to get the leave of
/// @ret int equal to the amount of leave the specified user has
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn int getSickLeave( uID )
/// @brief returns an int equal to the amount of leave the specified user has
/// @param string uID is the ID of the user to get the leave of
/// @ret int equal to the amount of leave the specified user has
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void addVacationLeave( string uID, int toAdd )
/// @brief adds the specified number to the balance of the specified user
/// @param string uID is the ID of the user to add balance to
/// @param int toAdd is the balance to add to the specified user's balance
/// @note if uID is a blank string, the amount toAdd will be added to all 
///   users in the system
/// @note make toAdd a negative number to subtract time instead of adding
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void addSickLeave( string uID, int toAdd )
/// @brief adds the specified number to the balance of the specified user
/// @param string uID is the ID of the user to add balance to
/// @param int toAdd is the balance to add to the specified user's balance
/// @note if uID is a blank string, the amount toAdd will be added to all 
///   users in the system
/// @note make toAdd a negative number to subtract time instead of adding
///////////////////////////////////////////////////////////////////////////////

#ifndef VALIDATE_H
#define VALIDATE_H

#include "../rulesSystem/rulesSystem.h"
#include "../database/database.h"

#include <string> //Gives us the string library to work with 
using std::string;

#include <vector> //Gives us the vector library to work with 
using std::vector;

class validate {

  public:

    validate();
    
    ~validate();
    
    void displayPendingRequest( string uID );
    void displayAllRequestHistory( string uID );
    void displayDeniedRequestHistory( string uID );
    void displayApprovedRequestHistory( string uID );

    unsigned int getVacationLeave( string uID );
    unsigned int getSickLeave( string uID );
    void addVacationLeave( string uID, int toAdd );
    void addSickLeave( string uID, int toAdd );

    bool managerApproval( string uID, bool approved );
    
    bool validateDate( string date );
    bool validateLeave( string uID, string request );
    
    string get_today();

    void setRules( rulesSystem *rules );

    vector<string> parse_request(string request);

  private:
    
    void setToday(); 
    
    vector<string> getDates( string startDate, string endDate );

    rulesSystem * m_rules; //This will be the rules system the system validates by

    string m_today; //stores the date in MM/DD of the day the class is used

    time_t str_to_time( string date );

    int num_days( string start, string end );

    int num_days( time_t start, time_t end );

};

#endif

///END OF FILE-----------------------------------------------------------------