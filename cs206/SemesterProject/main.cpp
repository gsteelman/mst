//////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @brief -- Main file
//////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include "system/vacationsystem.h"

#include "common.h"
#include "library/errorlog.h"
#include "library/exception.h"

File OUTPUT;

int main(int argc, char * argv[]) {

  try {

    OUTPUT.open(OUTPUT_PATH);
    OUTPUT.clear();

    // Do something!
    VacationSystem vacation_system(argc, argv);

    OUTPUT.insert_line(OUTPUT.num_lines(), "XXX\r");
    OUTPUT.close(true);

  } catch (Exception & e) {

    OUTPUT.insert_line(OUTPUT.num_lines(), "ERROR, CHECK ERRORLOG.TXT\r");
    OUTPUT.insert_line(OUTPUT.num_lines(), "XXX\r");
    OUTPUT.close(true);

    // Create a log of the error.
    ErrorLog(e, "errorlog.txt");

    // Return the error code for notification.
    return e.error_code();

  }

  return 0;

}