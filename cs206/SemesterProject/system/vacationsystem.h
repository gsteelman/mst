//////////////////////////////////////////////////////////////////////
/// @file vacationsystem.h
/// @brief -- Vacation system driver
//////////////////////////////////////////////////////////////////////

#ifndef VACATIONSYSTEM_H
#define VACATIONSYSTEM_H

#include <string>
using std::string;

#include "../database/database.h"
#include "../rulesSystem/rulesSystem.h"
#include "../requestTime/requestTime.h"
#include "../validate/validate.h"

class VacationSystem {

  public:

    VacationSystem();
    VacationSystem(int argc, char * argv[]);
    ~VacationSystem();

    void parse_cmd_line(int argc, char * argv[]);

    void show_help();

    // Other public functions -- Probably unnecessary.

  protected:

    // Protected functions
    void initialize_database();

  private:

    // Variables
    requestTime m_request_system;
    rulesSystem m_rules_system;
    validate    m_validate_system;
    
    string      m_username;
    string      m_password;

};

#endif