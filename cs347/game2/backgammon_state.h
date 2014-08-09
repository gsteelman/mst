// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file backgammon_state.h
/// @author Gary Steelman, CS347 AI Team
/// @edit 7 Mar 2010
/// @brief Collection of variables to hold the state of the backgammon board.
/// @note Assignment 5.
///////////////////////////////////////////////////////////////////////////////

#ifndef BACKGAMMON_STATE_H
#define BACKGAMMON_STATE_H

#include <queue>
#include "exception.h"

using namespace std;

struct backgammon_state
{
  public: 
    deque<int> m_board;
    deque<int> m_move;
    deque<int> m_dice;
    deque<bool> m_dice_used;
    int m_player;
    
    backgammon_state();
    backgammon_state( const deque<int>& board, 
                      const deque<int>& move,
                      const deque<int>& dice,  
                      const deque<bool>& dice_used,
                      const int& player
                    );
    
    backgammon_state& operator=( const backgammon_state& rhs );

    void print();
};

#endif

// END OF FILE ----------------------------------------------------------------

