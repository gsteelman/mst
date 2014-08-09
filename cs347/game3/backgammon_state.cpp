// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file backgammon_state.cpp
/// @author Gary Steelman, CS347 AI Team
/// @edit 7 Mar 2010
/// @brief Collection of variables to hold the state of the backgammon board.
/// @note Assignment 5.
///////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <iostream>
#include "exception.h"
#include "backgammon_state.h"

using namespace std;

//Default constructor
backgammon_state::backgammon_state() { }

backgammon_state::~backgammon_state() 
{ 
}

backgammon_state& backgammon_state::operator=( const backgammon_state& rhs )
{
  //make sure we aren't assigning to ourselves
  if ( this == &rhs )
    return *this;
    
  m_board = rhs.m_board;
  m_move = rhs.m_move;
  m_bear = rhs.m_bear;
  m_dice = rhs.m_dice;
  m_dice_used = rhs.m_dice_used;
  m_bear_off = rhs.m_bear_off;
  m_player = rhs.m_player;
  m_score = rhs.m_score;
  
  return *this;
}

void backgammon_state::print() const
{
  cout << "b: ";
  for ( int i = 0; i < m_board.size(); i++ )
    cout << m_board[i] << " ";
  cout << endl;
  cout << "m: ";
  for ( int i = 0; i < m_move.size(); i++ )
    cout << m_move[i] << " ";
  cout << endl;
  cout << "d: ";
  for ( int i = 0; i < m_dice.size(); i++ )
    cout << m_dice[i] << "(" << m_dice_used[i] << ") ";
  cout << endl;
  cout << "p: " << m_player << " f: " << m_bear_off << endl;
  
  return;
}

// END OF FILE ----------------------------------------------------------------
