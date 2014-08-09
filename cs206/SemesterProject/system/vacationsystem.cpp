//////////////////////////////////////////////////////////////////////
/// @file vacationsystem.cpp
/// @brief -- Vacation system driver
//////////////////////////////////////////////////////////////////////

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

#include "vacationsystem.h"

#include "../common.h"

VacationSystem::VacationSystem() {

  // Set the database up for general use.
  initialize_database();

}

VacationSystem::VacationSystem(int argc, char * argv[]) {

  // Set the database up for general use.
  initialize_database();

  // Constructor with command line.
  parse_cmd_line(argc, argv);

}

VacationSystem::~VacationSystem() {

  // Empty destructor

}

void VacationSystem::parse_cmd_line(int argc, char * argv[]) {
  
  vector< vector<string> > command_list;
  
  for (int x = 0; x < argc; x++) {
  
    // '-' is the MAGIC STRING denoting a command.
    if (str_left(argv[x], 2) == "--") {
    
      // If it IS a command, push on a new vector for it.
      command_list.push_back( vector<string>(1, argv[x]) ); 
      
    } else {

      // As long as we HAVE a command, add it.
      if (command_list.size() >= 1) {
    
        // If it's NOT a command, push the input onto the top vector.
        command_list[command_list.size() - 1].push_back(argv[x]);

      }
      
    }
  
  }
  
  /* COMMAND LINE OPTIONS
  * --h:  help
  * --l:  login           <SSO> <password>
  * --r:  request         <start> <end> <"sick"/"vacation">
  * --var: view all reqs  <SSO/"all">
  * --vpr: view pending   <SSO/"all">
  * --vap: view approved  <SSO/"all">
  * --vdr: view denied    <SSO/"all">
  * --gl: grant leave     <SSO/"all"> <"sick"/"vacation"> <num days>
  * --ar: approve request <SSO> <y/n>
  */
  
  for (int x = 0; x < command_list.size(); x++) {
  
    string command = command_list[x][0];
    
    // Case sensitivity is insignificant in commands.
    command = str_tolower(command);
    
    if (command == "--l" || command == "--login") {
    
      // Log in.
      if (command_list[x].size() < 3) {
      
        cout << "Invalid request. [" << command_list[x].size() - 1 << "] is too few parameters for \"" << command_list[x][0] << "\"." << endl;
        
      } else {
      
        // Usernames are case-insensitive.
        m_username = str_tolower(command_list[x][1]);

        // Passwords are case-SENSITIVE.
        m_password = command_list[x][2];
        
      }
      
      cout << "Login failed. Try again tomorrow when we've implemented the SSO system." << endl;
      
    /* if (command == "--l") */
    } else if (command == "--r" || command == "--request") {
    
      // Request time.
      if (command_list[x].size() < 4) {
      
        cout << "Invalid request. [" << command_list[x].size() - 1 << "] is too few parameters for \"" << command_list[x][0] << "\"." << endl;
        
      } else {

        m_request_system.addRequest(m_username, command_list[x][1], command_list[x][2], command_list[x][3]);

      }
      
    /* else if (command == "--r") */
    } else if (command == "--var") {
    
      // View request.
      if (command_list[x].size() < 2) {
      
        cout << "Invalid request. [" << command_list[x].size() - 1 << "] is too few parameters for \"" << command_list[x][0] << "\"." << endl;
        
      } else {
      
        if (str_tolower(command_list[x][1]) == "all") {
        
          // Pass the displayRequest function a BLANK SSO
          // to display ALL the requests.
          command_list[x][1] = "";
          
        }
      
        m_validate_system.displayAllRequestHistory(command_list[x][1]);
        
      }
      
    /* else if (command == "--var") */
    } else if (command == "--vpr") {
    
      // View request.
      if (command_list[x].size() < 2) {
      
        cout << "Invalid request. [" << command_list[x].size() - 1 << "] is too few parameters for \"" << command_list[x][0] << "\"." << endl;
        
      } else {
      
        if (str_tolower(command_list[x][1]) == "all") {
        
          // Pass the displayRequest function a BLANK SSO
          // to display ALL the requests.
          command_list[x][1] = "";
          
        }
      
        m_validate_system.displayPendingRequest(command_list[x][1]);
        
      }
      
    /* else if (command == "--vpr") */
    } else if (command == "--vap") {
    
      // View request.
      if (command_list[x].size() < 2) {
      
        cout << "Invalid request. [" << command_list[x].size() - 1 << "] is too few parameters for \"" << command_list[x][0] << "\"." << endl;
        
      } else {
      
        if (str_tolower(command_list[x][1]) == "all") {
        
          // Pass the displayRequest function a BLANK SSO
          // to display ALL the requests.
          command_list[x][1] = "";
          
        }
      
        m_validate_system.displayApprovedRequestHistory(command_list[x][1]);
        
      }
      
    /* else if (command == "--vap") */
    } else if (command == "--vdr") {
    
      // View request.
      if (command_list[x].size() < 2) {
      
        cout << "Invalid request. [" << command_list[x].size() - 1 << "] is too few parameters for \"" << command_list[x][0] << "\"." << endl;
        
      } else {
      
        if (str_tolower(command_list[x][1]) == "all") {
        
          // Pass the displayRequest function a BLANK SSO
          // to display ALL the requests.
          command_list[x][1] = "";
          
        }
      
        m_validate_system.displayDeniedRequestHistory(command_list[x][1]);
        
      }
      
    /* else if (command == "--vdr") */
    } else if (command == "--gl") {
    
      // Request time.
      if (command_list[x].size() < 4) {
      
        cout << "Invalid request. [" << command_list[x].size() - 1 << "] is too few parameters for \"" << command_list[x][0] << "\"." << endl;
        
      } else {

        string leaveType = str_tolower(command_list[x][2]);
        int leave_time = str_to_int(command_list[x][3]);
      
        if (str_tolower(command_list[x][1]) == "all") {
        
          // Pass the displayRequest function a BLANK SSO
          // to display ALL the requests.
          command_list[x][1] = "";
          
        }

        if (leaveType == SICK_LEAVE) {

          m_validate_system.addSickLeave(command_list[x][1], leave_time);

        } else if (leaveType == VACATION_LEAVE) {

          m_validate_system.addVacationLeave(command_list[x][1], leave_time);

        } else {
      
          cout << "Invalid request. [" << command_list[x][2] << "] is an invalid leave type." << endl;

        }

      }
      
    /* else if (command == "--r") */
    } else if (command == "--ar" || command == "--approverequest" || command == "--approve") {
    
      // Approve request.
      if (command_list[x].size() < 3) {
      
        cout << "Invalid request. [" << command_list[x].size() - 1 << "] is too few parameters for \"" << command_list[x][0] << "\"." << endl;
        
      } else {
      
        // Hooray!
        bool approve = ( str_left(str_tolower(command_list[x][2]), 3) == "yes" ); 
      
        m_validate_system.managerApproval(command_list[x][1], approve);
        
      }
      
    /* else if (command == "--ar") */
    } else {

      // If they didn't ask for help...
      if (command != "--h" && command != "--help") {
    
        // Tell them they're doing it wrong.
        cout << command << " is an invalid command." << endl;

      }
      
      show_help();
      
    } /* else */
  
  } /* for (int x = 0; x < command_list.size(); x++) */
  
}

void VacationSystem::show_help() {

  // JEREMY EDIT: Help should list the commands and their options, not give users
  //              an essay on possible usages. Command-line users don't want to
  //              have to open separate documentation to get a list of commands.
  cout << "Vacation System Help:" << endl << endl;
  cout << "-Command <parameter1> <parameter2> ... <parameterN>" << endl << endl;
  cout << "--help" << endl;
  cout << "  Shows this documentation." << endl;
  cout << "  Aliases: -h" << endl << endl;
  cout << "--login <username> <password>" << endl;
  cout << "  Sends login information to the SSO system." << endl;
  cout << "  Aliases: -l" << endl << endl;
  cout << "--request <start> <end> <\"sick\" OR \"vacation\">" << endl;
  cout << "  Puts a request into the database. Dates should be formatted as MM/DD" << endl;
  cout << "  Aliases: --r" << endl << endl;
  cout << "--viewrequest <SSO>" << endl;
  cout << "  Lists all pending requests from <SSO>." << endl;
  cout << "  Input \"all\" for <SSO> to view all requests pending approval." << endl;
  cout << "  Only users of \"Manager\" class or higher may use this function." << endl;
  cout << "  Aliases: --view --vr" << endl << endl;
  cout << "--approverequest <SSO> <yes/no>" << endl;
  cout << "  Approve request from <SSO>." << endl;
  cout << "  Only users of \"Manager\" class or higher may use this function." << endl;
  cout << "  Aliases: --approve --ar" << endl << endl;

}

void VacationSystem::initialize_database() {

  // Initialize the database.
  DATABASE.open(DATABASE_PATH);

  // Add the fields we always use to the global scope.
  DATABASE.add_field(PENDING_APPROVAL);
  DATABASE.add_field(APPROVED_REQUESTS);
  DATABASE.add_field(DISAPPROVED_REQUESTS);
  DATABASE.add_field(ON_VACATION);
  DATABASE.add_field(SICK_LEAVE_BALANCE);
  DATABASE.add_field(VACATION_LEAVE_BALANCE);
  DATABASE.add_field(USER_CLASS);

  // Add some default sick leave and vacation time to the global scope.
  // Note that these entries WILL NOT be passed along to other scopes,
  // whereas the fields will. This is just a convenient place to store
  // default values. 
  //DATABASE.clear_field(GLOBAL_SCOPE, SICK_LEAVE_BALANCE);
  //DATABASE.clear_field(GLOBAL_SCOPE, VACATION_LEAVE_BALANCE);
  DATABASE.edit_entry( GLOBAL_SCOPE, SICK_LEAVE_BALANCE, int_to_str( DEFAULT_SICK_TIME ) );
  DATABASE.edit_entry( GLOBAL_SCOPE, VACATION_LEAVE_BALANCE, int_to_str( DEFAULT_VACATION_TIME ) );

  //////////////////////////////////////////////////////////
  /// DEBUG/TESTING FIELDS
  //////////////////////////////////////////////////////////
  DATABASE.edit_entry("jadvxd", USER_CLASS, "manager");
  DATABASE.edit_entry("gws4g2", USER_CLASS, "manager");
  DATABASE.edit_entry("mtvnxx", USER_CLASS, "manager");

  // Save changes
  DATABASE.save_file();

}