// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file driver.cpp
/// @author Gary Steelman
/// @edit 23 Jan 2010
/// @brief A driver for the traveling salesman problem. Solves via UCTS.
/// @note Assignment 2.
/// @note BONUS NOT INCLUDED currently.
/// @note To compile, use the command "make" or "make driver".
/// @note To run, use "./driver <input file path/name>".
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
using std::cout;
using std::endl;

#include "exception.h"
#include "str_manip.h"
#include "matrix.h"
#include "TSP-ucts.h"
#include <fstream>

//PRE-DECLARATIONS ------------------------------------------------------------
void driver( int argc, char* argv[] );
void error_logger( const Exception& e );

//MAIN FUNCTION ---------------------------------------------------------------
int main( int argc, char * argv[] ) 
{
  //Exception handler catches unhandled exceptions and writes to a file.
  try 
  {
    //Don't clutter main.
    driver( argc, argv );
  } 
  
  catch ( Exception e ) 
  {
    //Log the error to file.
    error_logger(e);
    
    //Return the error code so the user knows what happened.
    return e.get_errorCode();
  }
  
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn void driver( int argc, char* argv[] )
/// @brief The driver for this program.
/// @pre None.
/// @param int argc - The number of arguments used on the command line.
/// @param char* argv[] - The arguments used on the command line. 
/// @post Performs the operations for this program.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void driver( int argc, char* argv[] )
{
  //Make sure the correct number of commands were supplied
  if ( argc != 2 )
    throw Exception( 0, "Too many or too few command line arguments." );
  
  cout << "Traveling Salesman Problem (Uniform Cost Tree Search Algorithm)" << endl;
  
  //Open up the specified file
  std::ifstream inFile;
  inFile.open( argv[1] );
  
  //Make sure the file exists and can be read and such
  if ( !inFile.good() )
    throw Exception( 21, "Input file not found." );
  
  cout << "\n>Generating graph representation." << endl;
  Matrix<double> graph;
  
  //Parse the input file
  inFile >> graph;
  
  cout << "\n>Creating problem representation." << endl;
  TSPUCTS TSP( graph );
  
  cout << "\n>Solving the problem starting from city " 
    << TSP.currState().location() << ". This will take time. Please wait." 
    << endl;
  TSP.solve();
  
  cout << "\nSolution: " << endl;
  cout << TSP.get_solution() << endl;
  
  cout << "Total distance traversed: " << endl;
  cout << TSP.distanceTraveled() << endl;
  
  cout << "\nRun complete! Exiting program...\n" << endl;
  
  return;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn void error_logger( const Exception& e )
/// @brief Writes e to a file and also to the screen.
/// @pre e exists.
/// @param const Exception& e - The Exception to write to file and screen.
/// @post Writes e to a file and also to the screen.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
void error_logger( const Exception& e ) 
{
  //Create/open the log file.
  File elog( "errorlog.txt" );
  
  //Store the error message for output to file and screen.
  string msg = "Exception " + int_to_str( e.get_errorCode() ) + ": " + e.get_errorMsg();
  
  //Insert the error at the end of the file.
  elog.insert_line( elog.get_num_lines(), msg );
  
  //Save the file, then close it.
  elog.close(true);
  
  //Show the message to the screen.
  cout << msg << endl;

  return;
}

// END OF FILE ----------------------------------------------------------------
