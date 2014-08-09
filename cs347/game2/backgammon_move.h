// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file backgammon_state.h
/// @author Gary Steelman, CS347 AI Team
/// @edit 7 Mar 2010
/// @brief Collection of variables to hold the state of a backgammon move.
///   Basically it holds 4 values, the first two are "from, to" for the first
///   die, the second two are "from, to" for the second die.
/// @note Assignment 5.
///////////////////////////////////////////////////////////////////////////////

#ifndef BACKGAMMON_MOVE_H
#define BACKGAMMON_MOVE_H

#include <queue>
#include "exception.h"

using namespace std;

struct backgammon_move
{
  public:
    backgammon_move() {}
    backgammon_move( deque<char> move ):m_move(move) {}
    
    backgammon_move& operator=( const backgammon_move& rhs )
    {
      m_move = rhs.m_move;
    }
    
    char operator[]( const unsigned int& n )
    {
      if ( n > 3 )
        throw Exception( 1, "Index out of range. backgammon_move::operator[]" );
        
      return m_move[n];
    }
    
    char operator[]( const unsigned int& n ) const
    {
      if ( n > 3 )
        throw Exception( 1, "Index out of range. backgammon_move::operator[]" );
        
      return m_move[n];
    }
    
    deque<char> m_move; //0-3
};

#endif

// END OF FILE ----------------------------------------------------------------
