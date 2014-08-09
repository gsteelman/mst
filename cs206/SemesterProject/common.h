//////////////////////////////////////////////////////////////////////
/// @file common.h
/// @brief -- Common header file. Includes global variables that
///           need to be defined across multiple files.
//////////////////////////////////////////////////////////////////////

#ifndef COMMON_H
#define COMMON_H

//////////////////////////////////////////////////////////////////////
/// HEADERS
//////////////////////////////////////////////////////////////////////
#include <string>
using std::string;

#include "database/database.h"
#include "library/file.h"

//////////////////////////////////////////////////////////////////////
/// GLOBAL CONSTANTS
//////////////////////////////////////////////////////////////////////
extern const string PENDING_APPROVAL;
extern const string APPROVED_REQUESTS;
extern const string DISAPPROVED_REQUESTS;
extern const string SICK_LEAVE_BALANCE;
extern const string VACATION_LEAVE_BALANCE;
extern const string ON_VACATION;
extern const string USER_CLASS;

// Database defaults.
extern const unsigned int DEFAULT_VACATION_TIME;
extern const unsigned int DEFAULT_SICK_TIME;
extern const string RULES_OVERRIDDEN;

// Random strings.
extern const string SICK_LEAVE;
extern const string VACATION_LEAVE;

// File paths.
extern const string DATABASE_PATH;
extern const string RULESET_PATH;
extern const string OUTPUT_PATH;

//////////////////////////////////////////////////////////////////////
/// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////
extern Database DATABASE;

// Declared in main.cpp
extern File OUTPUT;

#endif