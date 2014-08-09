//////////////////////////////////////////////////////////////////////
/// @file errorlog.cpp
/// @author Jeremy Davidson
/// @brief -- Error logging
//////////////////////////////////////////////////////////////////////

#include <ctime>
#include <string>
using std::string;

#include "errorlog.h"
#include "exception.h"
#include "file.h"
#include "strmanip.h"

//////////////////////////////////////////////////////////////////////
/// @fn ErrorLog(Exception e, string filename)
/// @brief -- Takes an Exception and reports the error to a log file
///           as denoted by filename.
//////////////////////////////////////////////////////////////////////
ErrorLog::ErrorLog(Exception e, string filename) {

  // Open a log file (creates it if one doesn't exist).
  File log_file(filename);

  // Get the time from the system.
  time_t curr_time;
  time(&curr_time);

  // Char array for ctime_s (function guarantees a return size of 26)
  char time_char[26];

  // Retrieve.
  ctime_s(time_char, sizeof(time_char), &curr_time);

  // A string for us to store it in.
  string time_str = time_char;

  // ctime() includes a '\n' character at the end, and
  // we don't want that.
  time_str = "[" + str_left(time_str, time_str.length() - 1) + "]";

  // Insert the date/time the error was found.
  string error_line = time_str;

  // Add the error code.
  error_line += " Error " + int_to_str(e.error_code());

  // And the error message.
  error_line += ": " + e.error_message();

  // Put it at the end of the file.
  log_file.insert_line(log_file.num_lines(), error_line);

  log_file.save_file();

  log_file.close();

}
