// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file driver.cpp
/// @edit 31 Sept 2009
/// @brief The driver to run the threading example program
/// @note run the executable for this driver followed only by the file names
///   of where the data set is located. The specified syntax for this driver is
///   "driver father.txt mother.txt daughter.txt"
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void *start_routine( void * passedStruct )
/// @brief the start of execution for each thread in the program
/// @pre Non
/// @param void * passedStruct is a struct of type Account
/// @post Executes the behavior of each thread
///////////////////////////////////////////////////////////////////////////////

#include "Account.h"
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <fstream>

using namespace std;

//Holds basic information about each thread
struct threadInfo
{
  string inputFile;
  int uID; 
};

//Predeclarations
void *start_routine( void * );

//GLOBAL VARIABLES

pthread_mutex_t Cmutex; //mutex for the checking account
pthread_mutex_t Smutex; //mutex for the savings account
Account familyAcc;

int main(int argc, char *argv[])
{
  //creates 3 threads, one for each family member
  pthread_t threadFather;
  pthread_t threadMother;
  pthread_t threadDaughter;
  
  //Initializes the 2 mutex variables
  pthread_mutex_init ( &Cmutex , NULL );
  pthread_mutex_init ( &Smutex , NULL );
  
  /*Argument argv[1] = father.txt
    Argument argv[2] = mother.txt
    Argument argv[3] = daughter.txt */
  //Creates a place to hold input file location and user IDs for each thread
  threadInfo father;
  father.inputFile = argv[1];
  father.uID = (int) 1;
  threadInfo mother;
  mother.inputFile = argv[2];
  mother.uID = (int) 2;
  threadInfo daughter;
  daughter.inputFile = argv[3];
  daughter.uID = (int) 3;
  
  //Makes sure the threads actually get created, else we end
  if ( pthread_create( &threadDaughter, NULL, start_routine, (void *)&daughter) != 0 )
    return 1;
  if ( pthread_create( &threadFather, NULL, start_routine, (void *)&father) != 0 )
    return 1;
  if ( pthread_create( &threadMother, NULL, start_routine, (void *)&mother) != 0 )
    return 1;
  
  //Joins the threads to make them wait until all have finished before ending
  pthread_join( threadFather, NULL );
  pthread_join( threadMother, NULL );
  pthread_join( threadDaughter, NULL );

  cout << "----- Final Account Balances -----" << endl;
  cout << "Checking: $" << familyAcc.get_cBal() << endl;
  cout << "Savings:  $" << familyAcc.get_sBal() << endl;
  
  return 0;
}

//performs the logic necessary for all these accounts
void *start_routine( void * passedStruct )
{
  //Recast passedStruct into a useful local struct
  threadInfo actStruct;
  actStruct = *(threadInfo *) passedStruct;
     
  //Each transaction will be it's own vector of miniature strings
  //And then an entire vector containing each transaction
  vector<vector<string> > transactions;
  
  ifstream inFile;
  inFile.open( actStruct.inputFile.c_str() );
  
  //Creates a temporary vector for holding the contents of the file
  vector<string> fileContents;
  string currLine = "";

  //Grabs the contents of the file
  while ( !inFile.eof() )
  {
    getline( inFile, currLine);
    fileContents.push_back( currLine );
  }
  
  //Resizes transactions to the number of lines in fileContents
  transactions.resize( fileContents.size() );
  
  //Make there be 3 blank strings in each part of the inner strings on the 
  //transactions vector so we can just change them at will later
  for ( unsigned int i = 0; i < transactions.size(); i++ )
  {
    transactions[i].resize( 3, "" );
  }
  
  //Run through each line in fileContents, parsing each field and inserting it
  //into transactions[transactionline[properfield]]
  for ( unsigned int i = 0; i < fileContents.size(); i++ )
  {
    int lhs = 0;
    int rhs = 0;
    currLine = fileContents[i];
    
    if ( currLine != "" )
    {
      //Find the first space
      rhs = currLine.find( " " );
            
      //the first field of each transaction needs to be the character for
      //the type of transaction, in this case, just a t, d, or w
      transactions[i][0] = currLine.substr( lhs, rhs );
      
      //Need to move lhs and rhs to indexes for the next substring
      lhs = rhs + 1;
      rhs = currLine.find( " ", lhs );
      transactions[i][1] = currLine.substr( lhs, rhs );
      
      //and now move to the last field
      lhs = rhs + 1;
      rhs = currLine.length();
      transactions[i][2] = currLine.substr( lhs, rhs );
      
      //And this should give us a vector of vectors of strings, with each
      //of the strings containing a field of info from the file    
    }
  }
  
  //run a for loop through all transactions, pulling each piece of info
  //as we need it and then peformign the proper actions
  int acc = 0;
  double amount = 0;
  string trans = "";
  
  for ( unsigned int i = 0; i < transactions.size(); i++ )
  {
    trans = transactions[i][0].c_str();           //The type of transaction
    acc = atoi( transactions[i][1].c_str() );     //The current account we work with
    amount = atof( transactions[i][2].c_str() );  //The amount we are working with
  
    //Lock the proper account we are operating on
    if ( trans == "t" )
    {
      pthread_mutex_lock( &Cmutex );
      pthread_mutex_lock( &Smutex );
    }
    else if ( acc == 0 )
      pthread_mutex_lock( &Cmutex );
    else if ( acc == 1 )
      pthread_mutex_lock( &Smutex );
    
    //Logic for if we're going to overdraft
    //if(w from checking and wamount > checkingbalance)
    if ( trans == "w" 
      && acc == 0
      && amount > familyAcc.get_cBal() )
    {
      //Grab money from savings to take care of it
      //If we have some money in savings, we can go negative, it doesn't matter
      if ( familyAcc.get_sBal() > 0 )
      {
        //allow balance to go negative
        familyAcc.transfer( 0, amount );
        familyAcc.withdraw( 0, amount );
        cout << familyAcc.get_uName( actStruct.uID ) << ": Transferred $" 
            << amount << " from savings to checking to cover withdraw." << endl;
        cout << familyAcc.get_uName( actStruct.uID ) << ": Withdrew $" 
            << amount << " from checking." << endl;
      }
      //Otherwise, notify them they have no money
      else
      {
        cout << familyAcc.get_uName( actStruct.uID ) << ": You do not have $" 
        << amount << " in your checking account and not enough in your "
        << "savings account to cover it. Transaction denied." << endl;
      }
    }
    
    //if(w or t from saving and wamount > savingsbalance and savingsbalance is +)
    else if ( (trans == "w" || trans == "t")
      && acc == 1
      && amount > familyAcc.get_sBal()
      && familyAcc.get_sBal() > 0 )
    {
      //allow balance to go negative
      if ( trans == "w")
      {
        familyAcc.withdraw( 1, amount );
        cout << familyAcc.get_uName( actStruct.uID ) << ": Withdrew $" 
            << amount << " from savings." << endl;
      }
      else if ( trans == "t" )
      {
        familyAcc.transfer( 1, amount );
        cout << familyAcc.get_uName( actStruct.uID ) << ": Transferred $" 
            << amount << " from checking to savings." << endl;
      }
    }
    
    //if(w or t from saving and savingsbalance is -) 
    else if ( (trans == "w" || trans == "t")
      && acc == 1
      && familyAcc.get_sBal() <= 0 )
    {
      //Don't make a transaction, print a warning
      cout << familyAcc.get_uName( actStruct.uID ) << ": You do not have $" 
        << amount << " in your savings account. Transaction denied." << endl;
    }
     
    //if(t from checking and wamount > checkingbalance and checkingbalance > 0) 
    else if ( trans == "t"
      && acc == 0
      && amount > familyAcc.get_cBal()
      && familyAcc.get_cBal() > 0 )
    {
      //allow balance to go negative, print warning
      familyAcc.transfer( 0, amount );
      cout << familyAcc.get_uName( actStruct.uID ) << ": Transferred $" 
        << amount << " from checking to savings. However, you have" 
        << " now overdrawn your account." << endl;
    }
    
    //if(t from checking and checkingbalance <0 )
    else if ( trans == "t"
      && acc == 0
      && familyAcc.get_cBal() <= 0 )
    {
      //Don't make a transaction, print a warning
      cout << familyAcc.get_uName( actStruct.uID ) << ": You do not have $" 
        << amount << " in your checking account to transfer." 
        << " Transaction denied." << endl;
    }
    
    //If we made it to here, that means we can go ahead with the transaction
    else
    {    
      if ( trans == "d" )
      {
        familyAcc.deposit( acc, amount );
        if ( acc == 0 )
          cout << familyAcc.get_uName( actStruct.uID ) << ": Deposited $" 
            << amount << " to checking." << endl;
        else if ( acc == 1 )
          cout << familyAcc.get_uName( actStruct.uID ) << ": Deposited $" 
            << amount << " to savings." << endl;
      }  
      else if ( trans == "t" )
      {
        familyAcc.transfer( acc, amount );
        if ( acc == 0 )
          cout << familyAcc.get_uName( actStruct.uID ) << ": Transferred $" 
            << amount << " from savings to checking." << endl;
        else if ( acc == 1 )
          cout << familyAcc.get_uName( actStruct.uID ) << ": Transferred $" 
            << amount << " from checking to savings." << endl;
      }
      else if (trans == "w" )
      {
        familyAcc.withdraw( acc, amount );
        if ( acc == 0 )
          cout << familyAcc.get_uName( actStruct.uID ) << ": Withdrew $" 
            << amount << " from checking." << endl;
        else if ( acc == 1 )
          cout << familyAcc.get_uName( actStruct.uID ) << ": Withdrew $" 
            << amount << " from savings." << endl;
      }   
      else
        cout << "There was an error in making the transaction for transaction "
          << i << " in user " << familyAcc.get_uName( actStruct.uID ) << endl;
    }
    
    cout << "> New checking balance: $" << familyAcc.get_cBal() << endl;
    cout << "> New savings balance: $" << familyAcc.get_sBal() << endl;
    
    //unlock the proper mutex
    if ( trans == "t" )
    {
      pthread_mutex_unlock( &Cmutex );
      pthread_mutex_unlock( &Smutex );
    }
    else if ( acc == 0 )
    {
      pthread_mutex_unlock( &Cmutex );
    }
    else if ( acc == 1 )
    {
      pthread_mutex_unlock( &Smutex );
    }
  }
}

// END OF FILE ----------------------------------------------------------------
