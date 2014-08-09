/*
  @file bitonic_sort.cpp
  @desc A simple parallel implementation of the bitonic sort algorithm.
        This can be used to sort arrays of numbers quickly.
  @auth Gary Steelman
  @date 02 Apr 2011
  @note This program utilizes the MPI parallel library on a 64-bit cluster.
*/

// STL libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

// MPI library for parallel computation
#include <mpi.h>

// Global constants for readability and maintainability
#define _MASTER_ID    0    // Master ID
#define _PERCENT_SEND 10.0 // Percentage of data set sent as a chunk to communication
                           // partner whenever swapping happens

using namespace std;

/***
  PRE-DECLARATIONS
***/
void driver( int argc, char* argv[] );

void mergeSort( vector<int>& v );
void mergeInternalSort( vector<int>& v, vector<int>& temp, int lhs, int rhs );
void merge( vector<int>& v, vector<int>& temp, int left, int right, int rightE );

/***
  MAIN
***/
int main( int argc, char * argv[] )
{
  driver( argc, argv );

  return 0;
}

/*
  @fn    void driver( int argc, char* argv[] )
  @brief The driver for this program.
  @pre   argv[1] contains a number of random numbers to generate and sort or an
          input file
  @param int argc - The number of arguments used on the command line.
  @param char* argv[] -- The arguments used on the command line.
          [0] -- Executable Name
          [1] -- 0 if parameter [2] is a number
                 1 if parameter [2] is an input file
          [2] -- A number (ie 500000) of random numbers for the program to
                 generate and then sort. This number must be divisible by 2.
                 OR a filename (ie "input.txt") containing one number per line
                 which is a list of numbers to sort.
  @post Performs the operations for this program.
  @return N/A.
*/
void driver( int argc, char* argv[] )
{
  // Check for correct number of supplied arguments via command line
  if ( argc != 3 )
  {
    cout << "Incorrect call from the command line. Use the syntax: \n"
         << "./BITONIC [0 | 1] [numbers to sort | filename]" << endl;
    MPI_Finalize();
    return;
  }

  /***
    Variables
  **/
  int         numProcs         = 0; // Number of processes being used
  int         myID             = 0; // Holds the rank of each process
  char        inputType        = atoi( argv[1] ); // The type of input: number or file
  int         numToSort        = 0; // The number of numbers to sort if inputType = 0
  string      fileLoc          = "";// The location of the input file if inputType = 1
  vector<int> myNumbers;            // Container for the numbers for this process

  double      wallClockStart   = 0; // Starting time of the algorithm
  double      wallClockEnd     = 0; // Ending time of the algorithm

  char        currWorkingDir[255];  // The current working directory
              getcwd( currWorkingDir, 255 );

  // Initialize the MPI background work
  MPI_Init( &argc, &argv );

  // Do this FIRST (to avoid error)
  MPI_Comm_size( MPI_COMM_WORLD, &numProcs );
  MPI_Comm_rank( MPI_COMM_WORLD, &myID );

  /***
    Populate local numbers based on inputType
  ***/

  // Input type is the number of numbers to sort
  if ( inputType == 0 )
  {
    numToSort = atoi( argv[2] );

    // Ensure the number of numbers to sort is even
    if ( (numToSort & 1) != 0 || numToSort < 0 )
    {
      if ( myID == _MASTER_ID )
        cout << "The number of numbers to sort must be divisible by 2 and > 0." << endl;

      MPI_Finalize();
      return;
    }

    myNumbers.resize( numToSort / numProcs );

    srand( time( NULL ) );

    for ( int i = 0; i < myNumbers.size(); i++ )
    {
      myNumbers[i] = rand() % numToSort;
    }
  }

  // Input type is a file of numbers to sort
  else if ( inputType == 1 )
  {
    fileLoc = argv[2];

    if ( myID == _MASTER_ID )
    {
      cout << "Running from " << currWorkingDir << endl;
      cout << "Attepmting to open file " << currWorkingDir << "/" << fileLoc << endl;
    }

    ifstream inFile;
    inFile.open( fileLoc.c_str() );

    if ( !inFile.is_open() )
    {
      if ( myID == _MASTER_ID )
        cout << "Error opening the input file \"" << fileLoc << endl;

      MPI_Finalize();
      return;
    }

    // Calculate the number of numbers in the file
    int inFileLength =
      count
        (
        istreambuf_iterator<char>(inFile),
        istreambuf_iterator<char>(),
        '\n'
        );

    if ( (inFileLength & 1) != 0 || inFileLength == 0 )
    {
      if ( myID == _MASTER_ID )
      {
        cout << "The number of numbers in the file, " << inFileLength
             << " is not divisible by 2 and > 0." << endl;
      }

      MPI_Finalize();
      return;
    }

    myNumbers.resize( inFileLength / numProcs );

    // Ensure reading from beginning of file
    inFile.seekg( 0, ios::beg );

    // Advance inFile read pointer to the beginning of this process' interval
    string currNum = "";
    for ( int i = 0; i < ( myID * myNumbers.size() ); ++i )
      getline( inFile, currNum );

    // Read in the numbers for this process
    for ( int i = 0; ( i < myNumbers.size() && getline( inFile, currNum ) ); i++ )
      myNumbers[i] = atoi( currNum.c_str() );

    inFile.close();
  }

  else
  {
    if ( myID == _MASTER_ID )
      cout << "Your input type must be a 0 (for a number) or a 1 (for a file)." << endl;

    MPI_Finalize();
    return;
  }

  // Ensure all processes have finished reading input before continuing
  MPI_Barrier( MPI_COMM_WORLD );

  // Start clock
  if ( myID == _MASTER_ID )
  {
    cout << "Number of processes to be used: " << numProcs << endl;
    cout << "Number of numbers per process: " << myNumbers.size() << endl;
    cout << "Taking "
         << (static_cast<double>(myNumbers.size()) * static_cast<double>(sizeof(int)) / 1024.0 / 1024.0)
         << " MB of RAM" << endl;
    wallClockStart = MPI_Wtime();
  }

  /***
    Perform local sort on initial myNumbers
  ***/

  sort ( myNumbers.begin(), myNumbers.end() );
  // mergeSort( myNumbers );

  /***
    Perform parallel bitonic sort
  ***/

  int   d             = log(numProcs)/log(2.0); // Dimension of the hypercube
  int   swapPartner   = 0;     // Process this process will binary compare
                               // and swap with each step
  bool  windowIDEven  = false; // Whether or not the window ID is even
  bool  jBitZero      = false; // Whether or not the jth bit of myID is zero
  
  vector<int> sort_buf( myNumbers.size()*2 );
  MPI_Status status;
  
  for ( int i = 1; i <= d; i++ )
  {
    // Calculate windowID and determine if it is even or odd
    windowIDEven = ((myID >> i) & 1) ? false : true;

    for ( int j = (i-1); j >= 0; j-- )
    {
      // Calculate communication partner by XOR with 1 shifted left j positions
      swapPartner = ( myID ^ (1 << j) );

      // Determine if the jth bit of myID is 0
      jBitZero = ( (myID & (1 << j)) ? false : true );      

      // COMPARE LOW
      if ( (windowIDEven && jBitZero) || (!windowIDEven && !jBitZero) )
      {
        // Send entire array as one block to swapPartner 
        MPI_Send( &myNumbers[0], myNumbers.size(), MPI_INT, swapPartner, 0, MPI_COMM_WORLD );
        
        // After numbers have been edited and sorted, receive new set
        MPI_Recv( &myNumbers[0], myNumbers.size(), MPI_INT, swapPartner, 0, MPI_COMM_WORLD, &status );        
      }

      // COMPARE HIGH
      else
      {          
        // Receive low's entire array in one block
        MPI_Recv( &sort_buf[0], myNumbers.size(), MPI_INT, swapPartner, 0, MPI_COMM_WORLD, &status );
        
        copy( myNumbers.begin(), myNumbers.end(), sort_buf.begin()+myNumbers.size() );
        
        sort( sort_buf.begin(), sort_buf.end() );
        // mergeSort( sort_buf );
        
        myNumbers.assign( sort_buf.begin() + myNumbers.size(), sort_buf.end() );
        
        // Send low the lower half of the array
        MPI_Send( &sort_buf[0], myNumbers.size(), MPI_INT, swapPartner, 0, MPI_COMM_WORLD );
      }
    }
  }

  // Wait for all processes to finish bitonic sorting
  MPI_Barrier( MPI_COMM_WORLD );

  // Stop clock
  if ( myID == _MASTER_ID )
  {
    wallClockEnd = MPI_Wtime();
    cout << "Computation complete." << endl;
    cout << "Wall clock time used: " << endl;
    cout << (wallClockEnd - wallClockStart) << " seconds, eqivalent to: \n"
         << (wallClockEnd - wallClockStart) / 60.0 << " minutes."
         << endl;
  }

  // Output the 10 numbers starting at index 100,000
  if ( myID * myNumbers.size() == 100000 )
  {
    for ( int k = 0; k < 10; k++ )
    {
      cout << myNumbers[k] << " ";
    }
    cout << endl;
  }
  
  // Output the 10 numbers starting at index 200,000
  if ( myID * myNumbers.size() == 200000 )
  {
    for ( int k = 0; k < 10; k++ )
    {
      cout << myNumbers[k] << " ";
    }
    cout << endl;
  }

  // Finish the parallel computation
  MPI_Finalize();

  return;
}

void mergeSort( vector<int>& v )
{
  vector<int> temp( v.size() );
  mergeInternalSort( v, temp, 0, v.size() - 1 );
  
  return;
}

void mergeInternalSort( vector<int>& v, vector<int>& temp, int lhs, int rhs )
{
  if ( lhs < rhs )
  {
    int center = ( lhs + rhs ) / 2;
    mergeInternalSort( v, temp, lhs, center );
    mergeInternalSort( v, temp, center + 1, rhs );
    merge( v, temp, lhs, center + 1, rhs );
  }
  
  return;
}

void merge( vector<int>& v, vector<int>& temp, int left, int right, int rightE )
{
  int leftE   = right - 1;
  int tempPos = left;
  int numElms = rightE - left + 1;
  
  while ( left <= leftE && right <= rightE )
  {
    if ( v[left] <= v[right] )
      temp[tempPos++] = v[left++];

    else 
      temp[tempPos++] = v[right++];
  }
  
  while ( left <= leftE )
    temp[tempPos++] = v[left++];
  
  while ( right <= rightE )
    temp[tempPos++] = v[right++];
    
  for ( int i = 0; i < numElms; i++, rightE-- )
  {
    v[rightE] = temp[rightE];
  }
  
  return;
}

/* END OF FILE */
