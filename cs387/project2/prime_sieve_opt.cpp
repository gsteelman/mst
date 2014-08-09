/* BEGINNING OF FILE */
/*******************************************************************************
  @file prime_sieve.cpp
  @desc A simple parallel processing implementation of the prime number seive
        to find all prime numbers between 0 and a supplied number N.
  @auth Gary Steelman
  @date 4 Feb 2011
*******************************************************************************/

// My libraries
#include "numeric_types.h"
#include "str_manip.h"

// STL libraries
#include <iostream>
#include <cmath>
#include <vector>

// MPI library for parallel computation
#include <mpi.h>

// Global constants for readability and maintainability
#define _MASTER_ID           0         // Master ID
#define _PRIME               0         // Mark numbers as 0 if they are prime
#define _NONPRIME            1         // Mark numbers as 1 if they are nonprime
#define _GET_PRIMES_AFTER_ME 1000000   // Output a list of primes after this number
#define _LIST_NUM_PRIMES     20        // Output this many primes

using namespace std;

/*******************************************************************************
PRE-DECLARATIONS
*******************************************************************************/
void driver( int argc, char* argv[] );

/*******************************************************************************
MAIN
*******************************************************************************/
int main( int argc, char * argv[] )
{
  driver( argc, argv );

  return 0;
}

/*******************************************************************************
  @fn void driver( int argc, char* argv[] )
  @brief The driver for this program.
  @pre argv[1] contains a number representing the upper bound to search to
  @param int argc - The number of arguments used on the command line.
  @param char* argv[] -- The arguments used on the command line.
          [0] -- Executable Name
          [1] -- Number for the upper bound for searching to
  @post Performs the operations for this program.
  @return N/A.
*******************************************************************************/
void driver( int argc, char* argv[] )
{
  sint32    numProcs         = 0; // Number of processes being used
  sint32    myID             = 0; // Holds the rank of each process

  sdouble64 myNumPrimes      = 0; // Number of primes this process has found
  sdouble64 numPrimes        = 0; // Sum of myNumPrimes
  sdouble64 wallClockStart   = 0; // Starting time of the algorithm
  sdouble64 wallClockEnd     = 0; // Ending time of the algorithm

  sdouble64 globalUBound     = atof( argv[1] ); // The upper bound to search to
  uint32    sqrtGlobalUBound = static_cast<uint32>(sqrt( globalUBound ));

  sdouble64 myLBound         = 0; // The lower bound for this process' search interval
  sdouble64 myUBound         = 0; // The upper bound for this process' search interval
  uint32    myIntervalSize   = 0; // The size of this process' search interval

  uint32    currPrime        = 0; // The number assumed prime by master whose multiples
                                  // are marked out by all processes
  sdouble64 currPrimeSquared = 0; // currPrime * currPrime
  uint32    prevPrime        = 0; // The previous currPrime
  uint32    currPrimeNextMult= 0; // The first multiple of currPrime in this
                                  // process' interval
  vector<bool> myNumbers;         // The markings for primacy of numbers

  // Initialize the MPI background work
  MPI_Init( &argc, &argv );

  // Do this FIRST (to avoid error)
  MPI_Comm_size( MPI_COMM_WORLD, &numProcs );
  MPI_Comm_rank( MPI_COMM_WORLD, &myID );

  // Master searches 0..sqrt(N) or the whole search space
  if ( myID == _MASTER_ID )
  {
    myLBound = 0;

    // Protection for only one process running
    if ( numProcs > 1 )
    {
      myUBound = sqrtGlobalUBound;
    }

    // Versus multiple processes running
    else
    {
      myUBound = globalUBound;
    }

    myIntervalSize = static_cast<uint32>(myUBound - myLBound);
  }

  // Slaves split the remaining interval evenly based on process ID
  else
  {
    // The width of each interval
    myIntervalSize = static_cast<uint32>(ceil( 1.0 / (sdouble64)(numProcs - 1) * (globalUBound - (sdouble64)sqrtGlobalUBound) ));

    // Set the lower bound of the slaves' intervals based on ID
    myLBound = (sdouble64)sqrtGlobalUBound + (sdouble64)(myID - 1) * (sdouble64)myIntervalSize;

    // Set the upper bound of the slaves' intervals based on their lower bound
    // If the last interval being assigned is this one, ensure that the upper 
    // bound does not exceed globalUBound
    myUBound = ( (myID + 1) == numProcs) ? ( globalUBound ) : ( myLBound + (sdouble64)myIntervalSize );
  }

  // All processes begin searching at 2
  currPrime = 2;

  // If the interval size is > UINT32_MAX then we have a problem because
  // C++ can't have a vector of size larger than UINT32_MAX and this problem
  // becomes infeasible with this implementation
  if ( (myUBound - myLBound) > (sdouble64)UINT32_MAX )
  {
    cout << "Process " << myID
         << " memory allocation problem: too big for STL vector." << endl;

    MPI_Finalize();

    return;
  }

  cout << "Process " << myID << " searching ["
       << myLBound << "," << myUBound << "); size = " << myIntervalSize << endl;

  // Resizing the arrays here avoids looped memory reallocation later
  myNumbers.resize( myIntervalSize, _PRIME );

  // Each process waits for all processes to initialize.
  MPI_Barrier( MPI_COMM_WORLD );

  if ( myID == _MASTER_ID )
  {
    // Master will not count 0 and 1 as prime
    myNumbers[0] = _NONPRIME;
    myNumbers[1] = _NONPRIME;

    cout << "Number of processes to be used: " << numProcs << endl;
    cout << "Beginning location of primes in the interval ["
         << myLBound << "," << static_cast<uint32>(globalUBound) << "]" << endl;
    wallClockStart = MPI_Wtime();
  }

  while ( currPrime < sqrtGlobalUBound )
  {    
    // Broadcast the next prime number in the list to all processes
    MPI_Bcast( &currPrime, 1, MPI_UNSIGNED_LONG, _MASTER_ID, MPI_COMM_WORLD );
  
    currPrimeSquared = (currPrime * currPrime);

    // Find least multiple of currPrime in this process' interval
    if ( myLBound >= currPrimeSquared )
    {
      currPrimeNextMult = static_cast<uint32>(
                            floor(fmod((currPrime - floor(fmod(myLBound, currPrime))), currPrime))
                          );
    }
    
    // Find currPrimeSquared in our interval, start with that
    else if ( myUBound >= currPrimeSquared && myLBound <= currPrimeSquared )
    {
      currPrimeNextMult = currPrimeSquared;
    }
    
    // Search begins too high for this process
    else
    {
      continue;
    }
    
    // Mark all multiples of currPrime as nonprime in this interval
    for ( uint32 i = currPrimeNextMult; i < myIntervalSize; i+=currPrime )
    {
      myNumbers[i] = _NONPRIME;
    }

    // Select the next prime in the master's interval
    if ( myID == _MASTER_ID )
    {
      for ( uint32 i = currPrime + 1; i <= sqrtGlobalUBound; i++ )
      {
        // Current number is recognized as prime
        if ( myNumbers[i] == _PRIME || i == sqrtGlobalUBound )
        {
          currPrime = i;
          break;
        }
      }
    }
  }

  // Wait for all processes to finish markings
  MPI_Barrier( MPI_COMM_WORLD );

  if ( myID == _MASTER_ID )
  {
    wallClockEnd = MPI_Wtime();
    cout << "Computation complete." << endl;
    cout << "Wall clock time used: " << endl;
    cout << (wallClockEnd - wallClockStart)        << " seconds, eqivalent to: \n"
         << (wallClockEnd - wallClockStart) / 60.0 << " minutes."
         << endl;
  }

  // Count the number of primes found by this process
  for ( uint32 i = 0; i < myIntervalSize; i++ )
  {
    if ( myNumbers[i] == _PRIME )
    {
      myNumPrimes++;
    }
  }

  // Combine all myNumPrimes from each process, totaling the number of primes
  // discovered globally and output it
  MPI_Reduce( &myNumPrimes, &numPrimes, 1, MPI_DOUBLE, MPI_SUM, _MASTER_ID, MPI_COMM_WORLD );

  if ( myID == _MASTER_ID )
  {
    cout << "The number of primes in [" << myLBound << ","
         << static_cast<uint32>(globalUBound) << "] is "
         << static_cast<uint32>(numPrimes) << endl;
    cout << "The first " << _LIST_NUM_PRIMES << " after " << _GET_PRIMES_AFTER_ME
         << " are: " << endl;
  }

  MPI_Barrier( MPI_COMM_WORLD );
  
  if ( myLBound <= _GET_PRIMES_AFTER_ME )
  {
    currPrimeNextMult = floor(fmod(((sdouble64)_GET_PRIMES_AFTER_ME - floor(fmod(myLBound, (sdouble64)_GET_PRIMES_AFTER_ME))), (sdouble64)_GET_PRIMES_AFTER_ME));

    // Check to make sure the multiple found is actually _GET_PRIMES_AFTER_ME
    // and not just a multiple of it
    if ( myLBound + currPrimeNextMult == _GET_PRIMES_AFTER_ME )
    {
      // Count the number of primes output
      uint32 j = 0;

      // Loop through the numbers after _GET_PRIMES_AFTER_ME and output
      // whenever a number is found to be prime
      for ( uint32 i = currPrimeNextMult; i < myIntervalSize; i++ )
      {
        if ( myNumbers[i] == _PRIME )
        {
          cout << static_cast<uint32>(myLBound) + i << endl;
          j++;
        }

        if ( j >= _LIST_NUM_PRIMES )
        {
          break;
        }
      }
    }
  }

  MPI_Barrier( MPI_COMM_WORLD );
  
  if ( myID == _MASTER_ID )
  {
    cout << "The greatest prime number found is: " << endl;
  }
  
  MPI_Barrier( MPI_COMM_WORLD );
  
  // Start at the highest processing interval and work backward to find
  // the greatest prime number found
  if ( numProcs > 1 && myID == numProcs - 1 )
  {
    for ( uint32 i = myIntervalSize; i >= 0; i-- )
    {
      if ( myNumbers[i] == _PRIME )
      {
        cout << static_cast<uint32>(myLBound) + i << endl;
        break;
      }
    }
  }
  
  else if ( numProcs == 1 )
  {
    for ( uint32 i = myIntervalSize; i >= 0; i-- )
    {
      if ( myNumbers[i] == _PRIME )
      {
        cout << i << endl;
        break;
      }
    }
  }
  
  // Finish the parallel computation
  MPI_Finalize();

  return;
}

/* END OF FILE */
