// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file Account.cpp
/// @edit 31 Sept 2009
/// @brief The implementation for the Account class
///////////////////////////////////////////////////////////////////////////////

#include "Account.h"
#include <iostream>
#include <string>

Account::Account() 
{
  m_cBal = 0;
  m_sBal = 0;
}

Account::~Account()
{
}

double Account::get_cBal() const
{
  return m_cBal;
}

double Account::get_sBal() const
{
  return m_sBal;
}

void Account::set_cBal( const double& amount )
{
  m_cBal = amount;
  return;
}

void Account::set_sBal( const double& amount )
{
  m_sBal = amount;
  return;
}

void Account::deposit ( const int& to, const double& amount )
{
  //Depositing to the checking account
  if ( to == 0 )
  {
    set_cBal( get_cBal() + amount );
  }
  
  //Depositing to the savigns account
  else if ( to == 1)
  {
    set_sBal( get_sBal() + amount );
  }
  
  //Depositing money to nowhere...
  else
  {
    std::cout << "Error has occurred in depositing" << std::endl;
  } 
  
  return;
}

void Account::transfer( const int& to, const double& amount )
{
  //Transfer to checking account
  //Withdraw from savings, deposit to checkings
  if ( to == 0 )
  {
    withdraw( 1, amount );
    deposit( 0, amount );
  }
  
  //Transfer to savings account
  //Withdraw from checking, deposit to saving
  else if ( to == 1 )
  {
    withdraw( 0, amount );
    deposit( 1, amount );
  }
  
  return;
}

void Account::withdraw( const int& from, const double& amount )
{
  //Withdrawing from the checking account
  if ( from == 0 )
  {
    set_cBal( get_cBal() - amount );
  }
  
  //Withdrawing from the savigns account
  else if ( from == 1)
  {
    set_sBal( get_sBal() - amount );
    
  }
  
  //Withdrawing from somewhere that doesn't exist...
  else
  {
    std::cout << "Error has occurred in withdrawing." << std::endl;
  } 
  
  return;
}

std::string Account::get_uName( const int& uID )
{
  if ( uID == 1 )
    return "Bruce";
  else if ( uID == 2 )
    return "Jennfier";
  else if ( uID == 3 )
    return "Jill";
  
  return "NONAME";
}

// END OF FILE ----------------------------------------------------------------
