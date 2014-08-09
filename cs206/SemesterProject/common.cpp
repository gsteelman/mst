//////////////////////////////////////////////////////////////////////
/// @file common.cpp
/// @brief -- Common header file. Includes global variables that
///           need to be defined across multiple files.
//////////////////////////////////////////////////////////////////////

#include "common.h"

//////////////////////////////////////////////////////////////////////
/// GLOBAL CONSTANTS
//////////////////////////////////////////////////////////////////////
// Database fields.
const string PENDING_APPROVAL       = "VACATION_REQUESTS_PENDING_MANAGER_APPROVAL";
const string APPROVED_REQUESTS      = "APPROVED_VACATION_REQUESTS";
const string DISAPPROVED_REQUESTS   = "DISAPPROVED_VACATION_REQUESTS";
const string SICK_LEAVE_BALANCE     = "SICK_LEAVE_BALANCE";
const string VACATION_LEAVE_BALANCE = "VACATION_LEAVE_BALANCE";
const string ON_VACATION            = "ON_VACATION";
const string USER_CLASS             = "USER_CLASS";

// Database defaults.
const unsigned int DEFAULT_VACATION_TIME  = 365;
const unsigned int DEFAULT_SICK_TIME      = 10;
const string RULES_OVERRIDDEN             = "Rules System Overridden by Manager.";

// Random strings.
const string SICK_LEAVE             = "sick";
const string VACATION_LEAVE         = "vacation";

// File paths.
const string DATABASE_PATH          = "database.dbm";
const string RULESET_PATH           = "RulesSystem/test.ruleset";
const string OUTPUT_PATH            = "output.txt";

//////////////////////////////////////////////////////////////////////
/// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////
Database DATABASE;