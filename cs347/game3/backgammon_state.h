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
    //Data
    deque<int> m_board;           //The number of checkers on each triangle
    deque<int> m_move;            //The moves taken to reach this state
    deque<int> m_bear;            //The moves taken to reach this state were borne off
    deque<int> m_dice;            //The dice rolled for this state
    deque<bool> m_dice_used;      //The dice used for this state
    bool m_bear_off;              //The state requires bearing instead of moving
    int m_player;                 //The player at play, 0 or 1
    int m_score;
	
    //Functions
    backgammon_state();
                    
    ~backgammon_state();					
    
    backgammon_state& operator=( const backgammon_state& rhs );
    
    void print() const;
};

#endif

// END OF FILE ----------------------------------------------------------------

