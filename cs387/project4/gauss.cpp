/*
  @file gauss.cpp
  @desc Performs gaussian elimination on a matrix to reduce to upper-triangular
          form then computes and outputs the determinant of the matrix.
  @auth Gary Steelman
  @date 05 Apr 2011
  @note This program utilizes the MPI parallel library on a 64-bit cluster.
*/

// STL libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

// MPI library for parallel computation
#include <mpi.h>

// Global constants for readability and maintainability
#define _MASTER_ID 0 // Master ID

using namespace std;

/***
  PRE-DECLARATIONS
***/
void driver( int argc, char* argv[] );
bool myCompare( double i, double j );

/***
  MAIN
***/
int main( int argc, char * argv[] )
{
  driver( argc, argv );

  MPI_Finalize();

  return 0;
}

/*
  @fn    void driver( int argc, char* argv[] )
  @brief The driver for this program.
  @pre   argv[1] contains the name of an input file containing the matrix to
            perform computations on. The required format of the file is described
            in instructions.htm or can be generated using generate_matrix.pl
  @param int argc - The number of arguments used on the command line.
  @param char* argv[] -- The arguments used on the command line.
          [0] -- Executable Name
          [1] -- Name of input file containing the values for the matrix
  @post Performs the operations for this program.
  @return N/A.
*/
void driver( int argc, char* argv[] )
{
  // Check for correct number of supplied arguments via command line
  if ( argc != 2 )
  {
    cout << "Incorrect call from the command line. Use the syntax: \n"
         << "./GAUSS [filename]" << endl;

    return;
  }

  /***
    Variables
  **/
  int            numProcs       = 0;       // Number of processes being used
  int            myID           = 0;       // Holds the rank of each process
  string         fileLoc        = argv[1]; // The location of the input file
  string         currLine       = "";      // The current line of the input file
  int            dimension      = 0;       // The dimensionality of the nxn matrix
  int            extraCols      = 0;       // The number of extra columns that must
                                           // be appended to the matrix to make it square
  vector< vector<double> > myNumbers;      // Container for the numbers for this process
                                           // [numCols][dimension]
  double         determinant    = 0;       // The determinant of the matrix

  double         wallClockStart = 0;       // Starting time of the algorithm
  double         wallClockEnd   = 0;       // Ending time of the algorithm

  char           currWorkingDir[255];      // The current working directory
                 getcwd( currWorkingDir, 255 );

  int    local_max_idx = 0;
  double local_det     = 1.0;
  int    numSwaps      = 0;
  int    my_i          = 0;
  vector<double> mult_factors;

  // Initialize the MPI background work
  MPI_Init( &argc, &argv );

  // Do this FIRST (to avoid error)
  MPI_Comm_size( MPI_COMM_WORLD, &numProcs );
  MPI_Comm_rank( MPI_COMM_WORLD, &myID );

  /***
    Populate local numbers based on processor ID
  ***/

  if ( myID == _MASTER_ID )
  {
    cout << "Running from " << currWorkingDir << endl;
    cout << "Attepmting to open file " << fileLoc << endl;
  }

  ifstream inFile;
  inFile.open( fileLoc.c_str() );

  if ( !inFile.is_open() )
  {
    if ( myID == _MASTER_ID )
      cout << "Error opening the input file \"" << fileLoc << endl;

    return;
  }

  // Ensure reading from beginning of file
  inFile.seekg( 0, ios::beg );

  // Get the dimensionality and number of "identity columns" necessary
  getline( inFile, currLine );
  dimension = atoi( currLine.c_str() );
  extraCols = (numProcs - (dimension % numProcs)) % numProcs;

  // Creates a column of proper size to append to this process' columns
  vector<double> app_col( dimension + extraCols, 0.0 );

  for ( int i = 0; i < dimension; i++ )
  {
    // This process needs to store |dimension| numbers in a column
    if ( i % numProcs == myID )
    {
      for ( int j = 0; (j < dimension && getline( inFile, currLine) ); j++ )
        app_col[j] = atof( currLine.c_str() );

      myNumbers.push_back( app_col );
    }

    // This process does not need to store numbers, just advance
    else
      for ( int j = 0; (j < dimension && getline( inFile, currLine) ); j++ ) {}
  }

  inFile.close();

  // This process got shorted a column because the number of columns isn't even
  // multiple of the number of processes and needs an identity column
  if ( myNumbers.size() < ceil( dimension / static_cast<float>(numProcs) ) )
  {
    app_col.clear();
    app_col.resize( dimension + extraCols, 0.0 );
    app_col[dimension + myID - 2] = 1.0;
    myNumbers.push_back( app_col );
  }

  // Ensure all processes have finished reading input before continuing
  MPI_Barrier( MPI_COMM_WORLD );

  // Start clock
  if ( myID == _MASTER_ID )
  {
    cout << "Number of processes to be used: " << numProcs << endl;
    cout << "Dimension of matrix: " << dimension << "x" << dimension << endl;
    cout << "        Expanded to: " << dimension+extraCols << "x" << dimension+extraCols << endl;

    wallClockStart = MPI_Wtime();
  }

  // For each column in the matrix
  for ( int i = 0; i < (dimension + extraCols); i++ )
  {
    // This process performs operations on its my_ith column relative to the
    // iteration over the entire matrix
    my_i = i / numProcs;

  /***
    Perform pivoting to avoid divide by zero and error propogation
  ***/

    local_max_idx = i;

    if ( i % numProcs == myID )
    {
      // Locate the max value at or below the diagonal in this column
      for ( int j = local_max_idx; j < myNumbers[my_i].size(); j++ )
        if ( myCompare( myNumbers[my_i][local_max_idx], myNumbers[my_i][j] ) )
          local_max_idx = j;

      // Multiply the local determinant value to be placed on the diagonal
      local_det *= myNumbers[my_i][local_max_idx];
    }

    // Broadcast the location of the max value found to all processes
    MPI_Bcast( &local_max_idx, 1, MPI_DOUBLE, (i % numProcs), MPI_COMM_WORLD );

    // Perform row swap, increment swap counter once
    if ( i != local_max_idx )
    {
      for ( int j = 0; j < myNumbers.size(); j++ )
        swap( myNumbers[j][i], myNumbers[j][local_max_idx] );

      numSwaps++;
    }

  /***
    Calculate multiplication factors for row reduction
  ***/
  
    // Number of multiplication factors is the number of number of rows below i
    mult_factors.resize( dimension + extraCols - i - 1 );

    if ( mult_factors.size() > 0 )
    {
      if ( i % numProcs == myID )
      {
        // Populate multiplication factors to zero out this column
        for ( int j = 0; j < mult_factors.size(); j++ )
        {
          // Avoid divide by 0 by populating with a 0
          mult_factors[j] =
            (myNumbers[my_i][i] == 0.0) ?
            0.0 :
            myNumbers[my_i][i+1+j] / myNumbers[my_i][i]
          ;
        }
      }

      // Broadcast multiplication factors for row operations
      MPI_Bcast( &mult_factors[0], mult_factors.size(), MPI_DOUBLE, (i % numProcs ), MPI_COMM_WORLD );

  /***
    Reduce row values based on multiplication factors
  ***/

      // All processes perform row operation on their columns
      for ( int k = 0; k < myNumbers.size(); k++ )
        for ( int j = 0; j < mult_factors.size(); j++ )
          myNumbers[k][i+1+j] -= mult_factors[j] * myNumbers[k][i];
    }
  }

  /***
    Calculate determinant of the resultant matrix
  ***/

  // Reduce w/ multiply across all processes' local determinant factors to obtain
  // global determinant. Change determinant's sign based on number of row swaps
  MPI_Reduce( &local_det, &determinant, 1, MPI_DOUBLE, MPI_PROD, _MASTER_ID, MPI_COMM_WORLD );
  determinant = (numSwaps & 1) ? (-1*determinant) : (determinant);

  // Stop clock
  if ( myID == _MASTER_ID )
  {
    wallClockEnd = MPI_Wtime();
    cout << "Computation complete." << endl;
    cout << "Wall clock time used: " << endl;
    cout << (wallClockEnd - wallClockStart) << " seconds, eqivalent to: \n"
         << (wallClockEnd - wallClockStart) / 60.0 << " minutes."
         << endl;
    cout << "The computed determinant of the orignal matrix is: " << determinant << endl;
  }

  return;
}

inline bool myCompare( double i, double j )
{
  return (fabs( i ) < fabs ( j ));
}

/* END OF FILE */
