// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file AI.h
/// @author Gary Steelman, CS347 AI Team
/// @edit 7 Mar 2010
/// @brief Function declarations for the AI for playing Backgammon.
/// @note Assignment 5.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class AI
/// @brief Contains functions for implementing AI to play Backgammon.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn virtual const char* username()
/// @brief Gets the username of the AI.
/// @pre an AI object exists.
/// @post Returns the username of the AI.
/// @return const char* - The username of the AI.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn virtual const char* password()
/// @brief Gets the password for the AI.
/// @pre an AI object exists.
/// @post Returns the password for the AI.
/// @return const char* - The password for the AI.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn virtual void init()
/// @brief A function that runs exactly one time, before run() on turn 1.
/// @pre init() has not been run before, an AI object exists.
/// @post Runs the init() function one time.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn virtual bool run()
/// @brief Runs each turn to perform the AI execution.
/// @pre It's your turn, and an AI object exists.
/// @post Runs each turn to perform the AI execution.
/// @return true -- Means you end your turn.
///         false - Means you request a status update from the server.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void displayBoard()
/// @brief Outputs the board to the screen.
/// @pre An AI object exists.
/// @post Outputs the board to the screen. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void displayStack()
/// @brief ?
/// @pre An AI object exists.
/// @post ?
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn int getPoint( int )
/// @brief Returns the number of checkers at the specified point.
/// @pre An AI object exists.
/// @param int - The point to get the number of checkers on.
/// @post Returns the number of checkers on a point. 
/// @return if player is O (p1), returns >0
///         if player is X (p0), returns <0
/// @note p0's bar (x's bar) is at point 25
/// @note p1's bar (o's bar) is at point 0
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn int getDie( int )
/// @brief Returns the value of the specified die.
/// @pre It's your turn and you've rolled your dice.
/// @param int - The die to get the value of.
/// @post Returns the value of the specified die.
/// @return The value of the specified die.
/// @note Die numbers are 0-3. Numbers 2 and 3 are valued at zero unless
///   doubles are rolled. 
/// @note Die values are sorted high to low automatically when received from 
///   the server.
///////////////////////////////////////////////////////////////////////////////

#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <queue>
#include "backgammon_state.h"

class AI: public BaseAI
{
  public:
    virtual const char* username();
    virtual const char* password();
    virtual void init();
    virtual bool run();
    
    /*functions available from the BaseAI class (just for my own documentation) 
    in addition to the ones shown here in AI
    
      void serverBoards[0].move(int from, int to)
      void serverBoards[0].bearOff(int from)
      int player0Score() = player x = negative values from getPoint
      int player1Score() = player o = positive values from getPoint
      double player0Time()
      double player1Time()
      int getPlayerID() = player number of current player 0 =x or 1 =o
      int turnNumber() = ?
    */
    
    //p0 = x, pieces return negative vlaues, note he moves backward along the board
    //p1 = o, pieces return positive values
    //initial roll happens
    
  private:
    void displayBoard();
    void displayStack( int, int );
    int getPoint( int );
    int getDie( int );

    void gen_moves( deque<backgammon_state>& states );
    bool continue_generation( const backgammon_state& state );
    bool bear_off_mode( const backgammon_state& state );
};

#endif

// END OF FILE ----------------------------------------------------------------
