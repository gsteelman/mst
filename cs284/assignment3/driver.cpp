// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file driver.cpp
/// @edit 22 Oct 2009
/// @brief The driver for the paged memory simulation program. 
/// @note Run the executable followed by the parameters listed in this order:
///   1) program list
///   2) program trace
///   3) page size (1, 2, 4, 8, or 16)
///   4) page replacement algorithm
///     least recently used -> lru
///     first in first out  -> fifo
///     clock cycle         -> clock
///   5) prepaging or demandpaging implementation
///     prepaging   -> p
///     demandpaging-> d
///   So a sample run of the program would look like this:
///   ./driver programlist programtrace 2 lru d
/// @throws 
///   Exception( 1, "Invalid number of runtime parameters." )
///   Exception( 2, "Invalid program list location. " )
///   Exception( 3, "Invalid program trace location." )
///   Exception( 4, "Invalid page size." )
///   Exception( 5, "Invalid replacement algorithm selected." )
///   Exception( 6, "Invalid paging style selected." )
///   Exception( 7, "Invalid replacement algorithm attempted." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void argCheck(  const int& n,
///                const string& programlist,
///                const string& programtrace,
///                const int& pageSize,
///                const string& replaceAlg,
///                const string& pagingStyle
///             )
/// @brief Checks the input parameters for correctness
/// @pre None.
/// @param const int& n - The number of parameters being used on the command line
/// @param const string& programlist - The location of the program list
/// @param const string& programtrace - The location of the program trace
/// @param const int& pageSize - The size of the pages in main memory
/// @post Completes execution and does nothing if the passed parameters
///   all fall into expected categories. 
/// @return None.  
///////////////////////////////////////////////////////////////////////////////

//Includes --------------------------------------------------------------------
#include "File.h"
#include "str_manip.h"
#include "exception.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// GLOBAL VARIABLES //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//The number of expected arguments to be run on the command line. 
int _NUM_ARGS_EXPECTED = 6;

//The size of the main memory (number of slots available)
unsigned int _MAIN_MEMORY_SIZE = 512;

//This is our counter for timestamping
unsigned long int _TIMESTAMP = 1;

//This will be our counter for the unique page ID for each page used between runs
unsigned long int _UNIQUE_PAGE_ID = 1;

//Just tells us if our memory is full or not so we don't have to search the 
//whole thing every time
bool _MEM_FULL = false;

///////////////////////////////////////////////////////////////////////////////
/// FUNCTION DECLARATIONS /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void argCheck(  const int& n,
                const string& programlist,
                const string& programtrace,
                const int& pageSize,
                const string& replaceAlg,
                const string& pagingStyle
             );
             

void printMem( const vector<long unsigned int>& m, 
               const vector<unsigned long int>& timestamp );
void initMem( vector<long unsigned int>& m, 
              const vector<vector<long unsigned int> >& pt, 
              vector<unsigned long int>& timestamp 
            );

void printPT( const vector<vector<long unsigned int> >& pt ); 
void initPT( const File& f, 
             vector<vector<long unsigned int> >& pt, 
             const unsigned int& pageSize );

void performTrace(  //const File& f,
                    ifstream& is, 
                    vector<unsigned long int>& m,
                    vector<unsigned long int>& ts,
                    vector<vector<unsigned long int> >& pt,
                    const string& ralg,
                    const string& rstyle,
                    const int& pageSize
                 );

void lru( //const File& f, 
          ifstream& is,
          vector<unsigned long int>& m,
          vector<unsigned long int>& ts,
          vector<vector<unsigned long int> >& pt,
          const string& rstyle,
          const int& pageSize
        );

void fifo( ifstream& is,
           vector<unsigned long int>& m,
           vector<unsigned long int>& ts,
           vector<vector<unsigned long int> >& pt,
           const string& rstyle,
           const int& pageSize
         );

void clock( ifstream& is,
            vector<unsigned long int>& m,
            vector<unsigned long int>& ts,
            vector<vector<unsigned long int> >& pt,
            const string& rstyle,
            const int& pageSize
          );

long int checkMemory( const vector<unsigned long int>& m, 
  const unsigned long int& pageID );
  
void loadPage( vector<long unsigned int>& m, 
               vector<unsigned long int>& ts,
               const long unsigned int& target,
               vector<vector<long unsigned int> >& pt, 
               const long unsigned int& process,
               const long unsigned int& source 
             );

///////////////////////////////////////////////////////////////////////////////
/// FUNCTION DEFINITIONS///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[] )
{
  try
  {
    string programListLocation = argv[1]; //The desired programlist location
    string programTraceLocation = argv[2];//The desired programtrace location
    int pageSize = str_to_int( argv[3] ); //The desired page size
    string replaceAlg = str_tolower( argv[4] ); //The desired replacement algorithm
    string pagingStyle = str_tolower( argv[5] );//The desired paging style
    
    cout << "Checking for input parameter correctness...";
      argCheck( argc, programListLocation, programTraceLocation, pageSize,
        replaceAlg, pagingStyle );
    cout << "done!" << endl;
    
    cout << "Loading file datas..." << endl;
    cout << "    Program list...";
      File programList( argv[1], true );    //Loads the programlist 
      programList.remove_blank_lines();
    cout << "done!" << endl;
    cout << "    Program trace...";
      ifstream programTrace( programTraceLocation.c_str(), ifstream::binary );
      //File programTrace( programTraceLocation, true );
    cout << "done!" << endl;
    
    cout << "Creating main memory representation...";
      vector<unsigned long int> MM( _MAIN_MEMORY_SIZE / pageSize );
      vector<unsigned long int> timestamp( MM.size() );
    cout << "done!" << endl;
    
    cout << "Creating page table representation...";
      vector<vector<unsigned long int> > PT;
    cout << "done!" << endl;

    cout << "Initializing page table representation...";
      initPT( programList, PT, pageSize );
    cout << "done!" << endl;
    
    cout << "Initializing main memory representation...";
      initMem( MM, PT, timestamp );
    cout << "done!" << endl;
    
    cout << "after default load of main memory: " << endl;
    printMem( MM, timestamp);
    
    
    cout << "Performing program trace...";
    performTrace( programTrace, MM, timestamp, PT, replaceAlg, pagingStyle, pageSize );
    cout << "done!" << endl;
    
    printMem( MM, timestamp );
    printPT( PT );
    
    cout << "Total page swaps made: " << _TIMESTAMP << endl;
    
    //cin.get();
    
  }
  
  //outputs our exception to the screen so we can see what happened.
  catch (Exception e)
  {
    cout << endl;
    cout << "Error: " << e.get_errorCode() << " - " 
      << e.get_errorMsg() << std::endl;
  }
  
  return 0;
}

void argCheck(  const int& n,
                const string& programlist,
                const string& programtrace,
                const int& pageSize,
                const string& replaceAlg,
                const string& pagingStyle
             )
{
  //Makes sure we are running with the proper parameters.
  if ( n != _NUM_ARGS_EXPECTED )
    throw Exception( 1, "Invalid number of runtime parameters." );
  else if ( programlist == "" )
    throw Exception( 2, "Invalid program list location. " );
  else if ( programtrace == "" )
    throw Exception( 3, "Invalid program trace location." );
  else if ( pageSize != 1 &&
            pageSize != 2 &&
            pageSize != 4 &&
            pageSize != 8 &&
            pageSize != 16 &&
            pageSize != 32 )
    throw Exception( 4, "Invalid page size." );
  else if ( (replaceAlg != "lru") && (replaceAlg != "fifo") && (replaceAlg != "clock") )
    throw Exception( 5, "Invalid replacement algorithm selected." );
  else if ( pagingStyle != "d" && pagingStyle != "p" )
    throw Exception( 6, "Invalid paging style selected." );
  else {}   
  
  return;
}

//Prints the main memory
void printMem( const vector<long unsigned int>& m, 
  const vector<unsigned long int>& timestamp )
{
  cout << "<Memory>" << endl;
  cout << "<index> <unique id> <timestamp>" << endl;
  for ( unsigned int i = 0; i < m.size(); i++ )
    cout <<  i << ": " << m[i] << " - " << timestamp[i] << endl;
  cout << "</Memory>" << endl;
  
  return;
}

//Prints the page table, all of it
void printPT( const vector<vector<long unsigned int> >& pt )
{
  cout << "<pageTable>" << endl;
  cout << "<process> <unique id>" << endl;
  for ( unsigned int i = 0; i < pt.size(); i++ )
  {
    for ( unsigned int j = 0; j < pt[i].size(); j++ )
    {
      cout << i << ": " << pt[i][j] << endl;
    }
  }
  cout << "</pageTable>" << endl;
  
  return;
}

//initializes the main memory with a certain number of pages based on pagesize
void initMem( vector<long unsigned int>& m, 
              const vector<vector<long unsigned int> >& pt, 
              vector<unsigned long int>& timestamp 
            )
{
  unsigned long int initialNumPages = m.size() / pt.size();

  //for each process in our page table...
  for ( unsigned long int i = 0; i < pt.size(); i++ )
  {
    //we allocate the specified number of pages...
    for ( unsigned long int j = 0; j < initialNumPages; j++ )
    {
      m[(i*initialNumPages) + j] = pt[i][j];
      timestamp[(i*initialNumPages) + j] = _TIMESTAMP;
      _TIMESTAMP++;
    }
  }
  
  return;
}

//void fillPageTable( const File& f, pageTable& p )
void initPT( const File& f, vector<vector<long unsigned int> >& pt, 
  const unsigned int& pageSize )
{
  vector<string> lineData;
  long unsigned int numPages = 0;
  
  pt.resize( f.get_num_lines() );
  
  for ( unsigned int i = 0; i < f.get_num_lines(); i++ )
  {
    if ( f.get_line( i ) == "" ) {} //Make sure we don't try to use a blank line
    else
    {
      lineData = str_breakup( f.get_line( i ), " " );   //Get the current line
      numPages = str_to_ulint( lineData[1] ) / pageSize;//Calc number of pages
      pt[i].resize( numPages );  //Set the page table size to the num of pages
      for ( unsigned int j = 0; j < numPages; j++ ) 
      {
        //Store the unique ID of the page in each spot
        pt[i][j] = _UNIQUE_PAGE_ID;
        _UNIQUE_PAGE_ID++;
      }
    }
  }
  
  return;
}

void performTrace(  //const File& f,
                    ifstream& is, 
                    vector<unsigned long int>& m,
                    vector<unsigned long int>& ts,
                    vector<vector<unsigned long int> >& pt,
                    const string& ralg,
                    const string& rstyle,
                    const int& pageSize
                 )
{
  //Calls the proper algorithm's function
  if ( ralg == "lru" )
    lru( is, m, ts, pt, rstyle, pageSize );
    //lru( f, m, ts, pt, rstyle, pageSize );
  //else if ( ralg == "fifo" )
    //fifo( is, m, ts, pt, rstyle, pageSize );
  //else if ( ralg == "clock" )
    //clock( is, m, ts, pt, rstyle, pageSize );
  //else
    //throw Exception( 7, "Invalid replacement algorithm attempted." );
  
  
  return;
}

void lru( ifstream& is,
//void lru( const File& f, 
          vector<unsigned long int>& m,
          vector<unsigned long int>& ts,
          vector<vector<unsigned long int> >& pt,
          const string& rstyle,
          const int& pageSize
        )
{
  vector<string> currInstruction;
  long int memLoc = 0;
  string currLine = "";
  while( getline( is, currLine ) )
  {
    cout << "currline: " << currLine;
    currInstruction = str_breakup( currLine, " " );
    unsigned long int currPID = str_to_ulint( currInstruction[0] );
    unsigned long int currPageID = str_to_ulint( currInstruction[1] ) / pageSize;
    cout << "  currPID: " << currPID << " currPageID: " << currPageID 
      << " -> " << pt[currPID][currPageID] << endl;
    //-1 means the page we want is not in memory
    //anything else means  the page we want IS in memory
    memLoc = checkMemory( m, pt[currPID][currPageID] );
    cout << " memLoc gives index number for main memory: " << memLoc << endl;
    
    //It means the page was not found in main memory, so we need to swap it into
    //memory
    if ( memLoc == -1 )
    {
      //Find the oldest page in main memory
      unsigned long int oldestIndexVal = ULONG_MAX;
      unsigned long int oldestIndex = 0;
      for ( unsigned long int k = 0; k < ts.size(); k++ )
      {
        if ( ts[k] < oldestIndexVal)
        {
          oldestIndex = k;
          oldestIndexVal = ts[k];
        }
        else {}
      }
      cout << "  oldestIndex: " << oldestIndex << endl;
      
      //And now that we know where the oldest page in main memory is and 
      //Which page is trying to be put into main memory, we perform a swap 
      //into main memory
      loadPage( m, ts, oldestIndex, pt, currPID, currPageID );
    }
    else {}
    
    //lineNumber++;
  }  
  
  return;
}

void fifo( ifstream& is,
           vector<unsigned long int>& m,
           vector<unsigned long int>& ts,
           vector<vector<unsigned long int> >& pt,
           const string& rstyle,
           const int& pageSize
         )
{

  return;
}

void clock( ifstream& is,
            vector<unsigned long int>& m,
            vector<unsigned long int>& ts,
            vector<vector<unsigned long int> >& pt,
            const string& rstyle,
            const int& pageSize
          )
{

  return;
}

//Returns the index in memory where the page is at, -1 if it isn't there
long int checkMemory( const vector<unsigned long int>& m, 
  const unsigned long int& pageID )
{
  long int loc = -1;
  
  for ( unsigned int i = 0; i < m.size(); i++ )
  {
    if ( m[i] == pageID )
    {
      return i;
    }
  }
  
  return loc;
}

void loadPage( vector<long unsigned int>& m, 
               vector<long unsigned int>& ts,
               const long unsigned int& target,
               vector<vector<long unsigned int> >& pt, 
               const long unsigned int& process,
               const long unsigned int& source 
             )
{
  cout << "   Initiaiting page loading into memory" << endl;
  
  //returns a valid location if 0 is found
  //otherwise -1
  long int emptyLoc = target;
  for (unsigned long int i = 0; i < m.size(); i++ )
  {
    if ( m[i] == 0 )
    {
      emptyLoc = i;
      break;
    } 
  }
  
  m[emptyLoc] = pt[process][source];
  ts[emptyLoc] = _TIMESTAMP;
  
  /*if ( emptyLoc == -1 )   //Means we do not have an empty spot
  {
    m[target] = pt[process][source];
    ts[target] = _TIMESTAMP;
  }
  
  else //there're empty spots, we'll just drop a page into that
  {
    m[emptyLoc] = pt[process][source];
    ts[emptyLoc] = _TIMESTAMP;
    
  }*/
  cout << "   timestamp: " << _TIMESTAMP << endl;
  _TIMESTAMP++;
  return;
}
    

// END OF FILE ----------------------------------------------------------------
