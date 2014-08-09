// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file Account.h
/// @edit 31 Sept 2009
/// @brief The header for the Account class
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class Account
/// @brief Contains functionality for operations between 2 different banking
///   accounts.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Account() 
/// @brief The default constructor for the Account class
/// @Pre None
/// @Post Creates an object of type Account with default parameters
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Account()
/// @brief The default destructor for the Account class
/// @Pre An object of type Account exists
/// @Post Destroys the object of type Account
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn double get_cBal() const
/// @brief Returns the checking account balance of the Account 
/// @Pre An object of type Account exists
/// @Post Returns the checking account balance of the Account 
/// @return Returns a double, the checking account balance of the Account 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn double get_sBal() const
/// @brief Returns the saving account balance of the Account 
/// @Pre An object of type Account exists
/// @Post Returns the checking account balance of the Account 
/// @return Returns a double, the checking account balance of the Account 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void set_cBal( const double& amount )
/// @brief Sets the value of the checking account to amount
/// @Pre An object of type Account exists
/// @param const double& amount - the amount to set the account balance to
/// @Post Sets the value of the checking account to amount
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void set_sBal( const double& amount )
/// @brief Sets the value of the saving account to amount
/// @Pre An object of type Account exists
/// @param const double& amount - the amount to set the account balance to
/// @Post Sets the value of the saving account to amount
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void deposit ( const int& to, const int& uID, const double& amount )
/// @brief Deposits an amount of money into a specified account given a 
///   specified user
/// @Pre An object of type Account exists
/// @param const int& to - the account number to deposit to; 0=check 1=save
/// @param const double& amount - the amount of money to deposit 
/// @Post Adds amount to the current balance of the specified account
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void transfer( const int& to, const int& uID, const double& amount )
/// @brief Tranfers an amount of money into a specified account given a 
///   specified user
/// @Pre An object of type Account exists
/// @param const int& to - the account number to transfer to; 0=check 1=save
/// @param const double& amount - the amount of money to transfer
/// @Post Transfers amount to the current balance of the specified account
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void withdraw( const int& from, const int& uID, const double& amount )
/// @brief Withdraws an amount of money from a specified account given a 
///   specified user
/// @Pre An object of type Account exists
/// @param const int& from - the account number to withdraw from; 0=check 1=save
/// @param const double& amount - the amount of money to withdraw
/// @Post Subtracts amount from the current balance of the specified account
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn std::string get_uName( const int& uID )
/// @brief Returns the name of a user given a user ID number
/// @Pre None.
/// @param const int& uID - the user ID for the person you want to know the
///   name of
/// @Post Returns the name of a user given a user ID number
/// @return string the name of a user given a user ID number
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

class Account
{
  public:
    Account();
    ~Account();
    
    double  get_cBal() const;
    double  get_sBal() const;
    void    set_cBal( const double& amount );
    void    set_sBal( const double& amount );
    void    deposit ( const int& to, const double& amount );
    void    transfer( const int& to, const double& amount );
    void    withdraw( const int& from, const double& amount );
    std::string get_uName( const int& uID );
  
  private:
    double m_cBal; //Account ID 0
    double m_sBal; //Account ID 1
};
