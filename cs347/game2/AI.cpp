// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file AI.cpp
/// @author Gary Steelman, CS347 AI Team
/// @edit 7 Mar 2010
/// @brief Function definitions for the AI for playing Backgammon.
/// @note Assignment 5.
///////////////////////////////////////////////////////////////////////////////

#include "AI.h"
#include "backgammon_state.h"
#include <queue>
#include <ctime>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

const char* AI::username()
{
  return "Shell AI";
  //return "Efsie";
}

const char* AI::password()
{
  return "password";
}

//Run on turn 1 before run(), the board is still set up just fine though
void AI::init()
{
  return;
}

//Our AI goes here...
bool AI::run()
{
  //displayBoard();
  
  //SETUP
  //Grab the board state
  deque<int> initial_board(26);
  for ( int i = 0; i < 26; i++ )
  {
    initial_board[i] = getPoint(i);
  }
  
  //Grab the dice
  deque<int> dice;
  for ( int i = 0; getDie(i) != 0; i++ )
  {
    dice.push_back( getDie(i) );
  }
  
  //sort the dice highest to lowest
  sort( dice.begin(), dice.end(), greater<int>() );
  
  deque<bool> diceUsed(dice.size(), false);  
  deque<int> moves;
  
  backgammon_state initial_state( initial_board, moves, dice, diceUsed, getPlayerID() );
  
  //cout << "initial backgammon state: " << endl;
  //initial_state.print();
  
  deque<backgammon_state> legal_moves;
  legal_moves.push_back( initial_state );
  
  //GENERATION
  gen_moves( legal_moves );
  
  //cout << "Number of moves generated: " << legal_moves.size() << endl;
  
  if ( legal_moves.empty() ) //we had no legal moves...:( Unlucky rolls or what?
  {
    //cout << "No legal moves generated :(" << endl;
    return true;
  }
  
  else //we have legal moves
  {
    //For this assignment, randomly choose a move and then perform it
    srand( time( NULL ) );
    unsigned int move_to_make = rand() % legal_moves.size();
    
    //cout << "The state we're moving to: ";
    //legal_moves[move_to_make].print();
    
    for ( unsigned int j = 0; j < legal_moves[move_to_make].m_move.size(); j+=2 )
    {
      //cout << "moves to make: " << legal_moves[move_to_make].m_move.size()/2 << endl;
      //cout << "moving from " << legal_moves[move_to_make].m_move[j] << " to " << legal_moves[move_to_make].m_move[j+1] << endl;
      serverBoards[0].move( legal_moves[move_to_make].m_move[j], legal_moves[move_to_make].m_move[j+1] );
    }
  }
  
  //cin.get();
  
  return true;
}

void AI::gen_moves( deque<backgammon_state>& states )
{
  //For each state given
  for ( unsigned int i = 0; i < states.size(); i++ )
  {
    //Check to see if we've used all the die available already
    //Given that we generate states and add them to the back of the deque,
    //And then remove the front of the queue, as we move along we update the
    //states to reflect the number of die left to use. So the first one we reach
    //that says it has all die used means that all following states in the deque
    //Are also finished. Basically the goal test.
    if ( !continue_generation( states[i] ) )
    {
      //cout << "all states generated" << endl;
      return;
    }
    
    //if we are in singles mode
    if ( states[i].m_dice.size() == 2 )
    {
      //cout << "lol singles!" << endl;
      
      //if we need to use die 0 AND die 1 because both have not been used
      if ( (states[i].m_dice_used[0] == false) && (states[i].m_dice_used[1] == false) )
      {
        //For checking for bar moves
        //deque<backgammon_state> bar_moves;
        //states[i].print();
        //cout << "  USE BOTH DICE!" << endl;
        
        for ( int k = 0; k < 2; k++ )
        {
          //cout << "    dieVal = " << getDie(k) << endl;
          for ( int j = 0; j < 25; j++ )
          {
            //cout << 25-j << " ";
            
            if (   (states[i].m_player == 0)     //If x is at play
                && (states[i].m_board[25-j] < 0) //If x owns the spot
                && ((25-j-getDie(k)) > 0)        //If we wouldn't move off the board
                && (states[i].m_board[25-j-getDie(k)] <= 1) //And if the spot to move to is open
                )
            {
              //cout << "+ ";              
              //Make a copy of our current state, move one of our pieces
              states.push_back( states[i] );
              states.back().m_board[25-j] += 1;
              states.back().m_board[25-j-getDie(k)] -= 1;
              
              //If we hit o in moving, move one of o's pieces to the bar
              if ( states[i].m_board[25-j-getDie(k)] == 1 )
              {
                states.back().m_board[25-j-getDie(k)] -= 1;
                states.back().m_board[0] += 1;
              }
              
              //record the move 
              states.back().m_move.push_back(25-j);
              states.back().m_move.push_back(25-j-getDie(k));
              states.back().m_dice_used[k] = true;
              
              //cout << "\n    x generated state: " << endl;
              //states.back().print();  

              //coudl doa  check after state generation for if the m_move starts with 25 or 0
              //then if it does, just return that move to do
              if ( states.back().m_move[0] == 25 )
              {
                //cout << "BAR MOVE RECOGNIZED LOL" << endl;
                //cout << "moving from " << states.back().m_move[0] << " to " << states.back().m_move[1] << endl;
                  serverBoards[0].move( states.back().m_move[0], states.back().m_move[1] );
              }
              
              else if ( (states.back().m_move.size() > 2) && states.back().m_move[2] == 25 )
              {
                //cout << "BAR MOVE RECOGNIZED LOL - 4" << endl;
                //cout << "moving from " << states.back().m_move[2] << " to " << states.back().m_move[3] << endl;
                  serverBoards[0].move( states.back().m_move[2], states.back().m_move[3] );
              }
              
            } //End x generation
            
            //PUT X BEAR OFF CHECK/MOVE GEN HERE, since the "stay on the board"
            //check will fail if we need to bear off...
            
            else if ( (states[i].m_player == 1)   //If o is at play
                && (states[i].m_board[j] > 0)     //If o owns the spot
                && (j+getDie(k) < 25)             //If we won't move off the board
                && (states[i].m_board[j+getDie(k)] >= -1) //The spot we want to move to is open
                )
            {
              //cout << "+ ";
              //Make a copy of our current state, move one of our pieces 
              states.push_back( states[i] );
              states.back().m_board[j] -= 1;
              states.back().m_board[j+getDie(k)] += 1;
              
              //If we hit x in moving, move one of x's pieces to the bar
              if ( states[i].m_board[j+getDie(k)] == -1 )
              {
                states.back().m_board[j+getDie(k)] += 1;
                states.back().m_board[25] -= 1;
              }
              
              //record the actual move
              states.back().m_move.push_back(j);
              states.back().m_move.push_back(j+getDie(k));
              states.back().m_dice_used[k] = true;
              
              //cout << "\n    o generated state: " << endl;
              //states.back().print();
              
              if ( states.back().m_move[0] == 0 )
              {
                //cout << "BAR MOVE RECOGNIZED LOL" << endl;
                //cout << "moving from " << states.back().m_move[0] << " to " << states.back().m_move[1] << endl;
                  serverBoards[0].move( states.back().m_move[0], states.back().m_move[1] );
              }
              
              else if ( (states.back().m_move.size() > 2) && states.back().m_move[2] == 25 )
              {
                //cout << "BAR MOVE RECOGNIZED LOL - 4" << endl;
                //cout << "moving from " << states.back().m_move[2] << " to " << states.back().m_move[3] << endl;
                  serverBoards[0].move( states.back().m_move[2], states.back().m_move[3] );
              }
            }
            
            //Otherwise, if we're in bear-off mode...
            else if ( bear_off_mode( states[i] ) )
            {
              //if we're o
              if ( states[i].m_player == 0 )
              {
                //If our move would go off the board
                if ( getDie(k) + j > 24 )
                {
                  //We'll bear it off
                  serverBoards[0].bearOff( j );
                }
                
                //But if we don't have a piece at our current location and we're
                //still wantin to bear off, move to the next location until we
                //find something to bear off
                else
                {
                  for ( int n = j; n < 25; n++ )
                  {
                    if ( getPoint(n) > 0 )
                    {
                      serverBoards[0].bearOff( n );
                    }
                  }
                }
                
              }
              
              //we're x instead
              else 
              {
                if ( getDie(k) - j < 1 )
                {
                  //we bear off
                  serverBoards[0].bearOff( j );
                }
                
                else
                {
                  for ( int n = j; n > 0; n-- )
                  {
                    if ( getPoint(n) < 0 )
                    {
                      serverBoards[0].bearOff( n );
                    }
                  }
                }
              }
            }
            
          } //End 0..25
          
          states.pop_front();
          //cout << "\nafter state generation states.size() = " << states.size() << endl;
          gen_moves( states);
          
        } //End 0..2
      }
      
      //Only using die 0
      else if ( (states[i].m_dice_used[0] == false) && (states[i].m_dice_used[1] == true) )
      {
        //states[i].print();
        //cout << "ONLY USE DIE 0!" << endl;
        //cout << "    dieVal = " << getDie(0) << endl;
        for ( int j = 0; j < 25; j++ )
        {
          //cout << j << " ";
          if (   (states[i].m_player == 0)     //If x is at play
              && (states[i].m_board[25-j] < 0) //If x owns the spot
              && ((25-j-getDie(0)) > 0)        //If we wouldn't move off the board
              && (states[i].m_board[25-j-getDie(0)] <= 1) //And if the spot to move to is open
              )
          {
            //cout << "+ ";
            //Ma0e a copy of our current state, move one of our pieces
            states.push_back( states[i] );
            states.back().m_board[25-j] += 1;
            states.back().m_board[25-j-getDie(0)] -= 1;
            
            //If we hit o in moving, move one of o's pieces to the bar
            if ( states[i].m_board[25-j-getDie(0)] == 1 )
            {
              states.back().m_board[25-j-getDie(0)] -= 1;
              states.back().m_board[0] += 1;
            }
            
            //record the move 
            states.back().m_move.push_back(25-j);
            states.back().m_move.push_back(25-j-getDie(0));
            states.back().m_dice_used[0] = true;
            
            //cout << "\n    x generated state: " << endl;
            //states.back().print();
          } //End x generation
          
          else if ( (states[i].m_player == 1)   //If o is at play
              && (states[i].m_board[j] > 0)     //If o owns the spot
              && (j+getDie(0) < 25)             //If we won't move off the board
              && (states[i].m_board[j+getDie(0)] >= -1)
              )
          {
            //cout << "+ ";
            //Ma0e a copy of our current state, move one of our pieces 
            states.push_back( states[i] );
            states.back().m_board[j] -= 1;
            states.back().m_board[j+getDie(0)] += 1;
            
            //If we hit x in moving, move one of x's pieces to the bar
            if ( states[i].m_board[j+getDie(0)] == -1 )
            {
              states.back().m_board[j+getDie(0)] += 1;
              states.back().m_board[25] -= 1;
            }
            
            //record the actual move
            states.back().m_move.push_back(j);
            states.back().m_move.push_back(j+getDie(0));
            states.back().m_dice_used[0] = true;
            
            //cout << "\n    o generated state: " << endl;
            //states.back().print();
          } //End o generation
        } //End 0..25
        //cout << "\nafter state generation states.size() = " << states.size() << endl;
        
        //Now that we've generated using only die 0
        states.pop_front();
      } //End using only die 0
      
      //Only using die 1
      else if ( (states[i].m_dice_used[0] == true) && (states[i].m_dice_used[1] == false) )
      {
        //states[i].print();
        //cout << "ONLY USE DIE 1!" << endl;
        //cout << "    dieVal = " << getDie(1) << endl;
        for ( int j = 0; j < 25; j++ )
        {
          //cout << j << " ";
          if (   (states[i].m_player == 0)     //If x is at play
              && (states[i].m_board[25-j] < 0) //If x owns the spot
              && ((25-j-getDie(1)) > 0)        //If we wouldn't move off the board
              && (states[i].m_board[25-j-getDie(1)] <= 1) //And if the spot to move to is open
              )
          {
            //cout << "+ ";
            //Ma0e a copy of our current state, move one of our pieces
            states.push_back( states[i] );
            states.back().m_board[25-j] += 1;
            states.back().m_board[25-j-getDie(1)] -= 1;
            
            //If we hit o in moving, move one of o's pieces to the bar
            if ( states[i].m_board[25-j-getDie(1)] == 1 )
            {
              states.back().m_board[25-j-getDie(1)] -= 1;
              states.back().m_board[0] += 1;
            }
            
            //record the move 
            states.back().m_move.push_back(25-j);
            states.back().m_move.push_back(25-j-getDie(1));
            states.back().m_dice_used[1] = true;
            
            //cout << "\n    x generated state: " << endl;
            //states.back().print();
          } //End x generation
          
          else if ( (states[i].m_player == 1)   //If o is at play
              && (states[i].m_board[j] > 0)     //If o owns the spot
              && (j+getDie(1) < 25)             //If we won't move off the board
              && (states[i].m_board[j+getDie(1)] >= -1)
              )
          {
            //cout << "+ ";
            //Ma0e a copy of our current state, move one of our pieces 
            states.push_back( states[i] );
            states.back().m_board[j] -= 1;
            states.back().m_board[j+getDie(1)] += 1;
            
            //If we hit x in moving, move one of x's pieces to the bar
            if ( states[i].m_board[j+getDie(1)] == -1 )
            {
              states.back().m_board[j+getDie(1)] += 1;
              states.back().m_board[25] -= 1;
            }
            
            //record the actual move
            states.back().m_move.push_back(j);
            states.back().m_move.push_back(j+getDie(1));
            states.back().m_dice_used[1] = true;
            
            //cout << "\n    o generated state: " << endl;
            //states.back().print();
          } //End o generation
        } //End 0..25
        //cout << "\nafter state generation states.size() = " << states.size() << endl;
        
        //Now that we've generated using only die 1
        states.pop_front();
      } //End using only die 0
    } //End singles mode
    
    //Rolled doubles, yeah buddy
    else
    {
      //cout << "lol doubles!" << endl;
      
      //cout << "    dieVal = " << getDie(0) << endl;
      for ( int j = 0; j < 25; j++ )
      {
        //cout << j << " ";
        if (   (states[i].m_player == 0)     //If x is at play
            && (states[i].m_board[25-j] < 0) //If x owns the spot
            && ((25-j-getDie(0)) > 0)        //If we wouldn't move off the board
            && (states[i].m_board[25-j-getDie(0)] <= 1) //And if the spot to move to is open
            )
        {
          //cout << "+ ";
          //Make a copy of our current state, move one of our pieces
          states.push_back( states[i] );
          states.back().m_board[25-j] += 1;
          states.back().m_board[25-j-getDie(0)] -= 1;
          
          //If we hit o in moving, move one of o's pieces to the bar
          if ( states[i].m_board[25-j-getDie(0)] == 1 )
          {
            states.back().m_board[25-j-getDie(0)] -= 1;
            states.back().m_board[0] += 1;
          }
          
          //record the move 
          states.back().m_move.push_back(25-j);
          states.back().m_move.push_back(25-j-getDie(0));
          
          //Update the die used for this iteration
          for ( int k = 0; k < 4; k++ )
          {
            if ( states[i].m_dice_used[k] == false )
            {
              states.back().m_dice_used[k] = true;
              break;
            }
          }
          
          //cout << "\n    x generated state: " << endl;
          //states.back().print();
          
          if ( states.back().m_move[0] == 25 )
          {
            //cout << "BAR MOVE RECOGNIZED LOL" << endl;
            //cout << "moving from " << states.back().m_move[0] << " to " << states.back().m_move[1] << endl;
              serverBoards[0].move( states.back().m_move[0], states.back().m_move[1] );
          }
          
        } //End x generation
        
        else if ( (states[i].m_player == 1)   //If o is at play
            && (states[i].m_board[j] > 0)     //If o owns the spot
            && (j+getDie(0) < 25)             //If we won't move off the board
            && (states[i].m_board[j+getDie(0)] >= -1)
            )
        {
          //cout << "+ ";
          //Make a copy of our current state, move one of our pieces 
          states.push_back( states[i] );
          states.back().m_board[j] -= 1;
          states.back().m_board[j+getDie(0)] += 1;
          
          //If we hit x in moving, move one of x's pieces to the bar
          if ( states[i].m_board[j+getDie(0)] == -1 )
          {
            states.back().m_board[j+getDie(0)] += 1;
            states.back().m_board[25] -= 1;
          }
          
          //record the actual move
          states.back().m_move.push_back(j);
          states.back().m_move.push_back(j+getDie(0));
          
          //Update the die used for this iteration
          for ( int k = 0; k < 4; k++ )
          {
            if ( states[i].m_dice_used[k] == false )
            {
              states.back().m_dice_used[k] = true;
              break;
            }
          }
          
          //cout << "\n    o generated state: " << endl;
          //states.back().print();
          
          if ( states.back().m_move[0] == 0 )
          {
            //cout << "BAR MOVE RECOGNIZED LOL" << endl;
            //cout << "moving from " << states.back().m_move[0] << " to " << states.back().m_move[1] << endl;
              serverBoards[0].move( states.back().m_move[0], states.back().m_move[1] );
          }
          
          else if ( (states.back().m_move.size() > 2) && states.back().m_move[2] == 25 )
          {
            //cout << "BAR MOVE RECOGNIZED LOL - 4" << endl;
            //cout << "moving from " << states.back().m_move[2] << " to " << states.back().m_move[3] << endl;
              serverBoards[0].move( states.back().m_move[2], states.back().m_move[3] );
          }
          
        } //End o generation
        
        //Otherwise, if we're in bear-off mode...
        else if ( bear_off_mode( states[i] ) )
        {
          //if we're o
          if ( states[i].m_player == 0 )
          {
            //If our move would go off the board
            if ( getDie(0) + j > 24 )
            {
              //We'll bear it off
              serverBoards[0].bearOff( j );
            }
            
            //But if we don't have a piece at our current location and we're
            //still wantin to bear off, move to the next location until we
            //find something to bear off
            else
            {
              for ( int n = j; n < 25; n++ )
              {
                if ( getPoint(n) > 0 )
                {
                  serverBoards[0].bearOff( n );
                }
              }
            }
            
          }
          
          //we're x instead
          else 
          {
            if ( getDie(0) - j < 1 )
            {
              //we bear off
              serverBoards[0].bearOff( j );
            }
            
            else
            {
              for ( int n = j; n > 0; n-- )
              {
                if ( getPoint(n) < 0 )
                {
                  serverBoards[0].bearOff( n );
                }
              }
            }
          }
        }
        
      } //End 0..25
      //cout << "\nafter state generation states.size() = " << states.size() << endl;
    } //Doubles    
  } // loop on states.size() 
}                                        

//Checks to see if we have reached a "goal" state: One that has used all of its dice
bool AI::continue_generation( const backgammon_state& state )
{
  for ( int i = 0; i < state.m_dice_used.size(); i++ )
    if ( state.m_dice_used[i] == false )
      return true;
      
  return false;
}

//Checks to see if the player is in position to start bearing off pieces
bool AI::bear_off_mode( const backgammon_state& state )
{
  if ( state.m_player == 0 )
  {
    for ( int i = 25; i > 6; i-- )
    {
      if ( state.m_board[i] != 0 )
      {
        return false;
      }
    }
  }
  
  else
  {
    for ( int i = 0; i < 19; i++ )
    {
      if ( state.m_board[i] != 0 )
      {
        return false;
      }
    }
  }
  
  return false;
}

void AI::displayBoard()
{
  cout << "Dice : ";
  
  for ( int i = 0; i < 4; i++ )
  {
    cout << getDie(i);
    if (i < 3)
    {
      cout << ",";
    }
  }
  
  cout << endl;
  
  if ( getPlayerID() == 0 )
  {
    cout << "You are X." << endl;
  }
  
  else
  {
    cout << "You are O." << endl;
  }
  
  cout << "Scores    X: " << player0Score() << "   O: " << player1Score();
  cout << endl;
  cout << "Times     X: " << player0Time() <<  "   O: " << player1Time();
  cout << endl;
  cout << "   +24-23-22-21-20-19--25--18-17-16-15-14-13-+" << endl;
  
  for ( int row = 1; row < 6; row++ )
  {
    cout << "   ";
    cout << "|";
    
    for (int col = 24; col > 18; col --)
    {
      displayStack(col, row);
    }
    
    cout << "|";
    displayStack(25, row);
    cout << "|";
    
    for (int col = 18; col > 12; col--)
    {
      displayStack(col, row);
    }
    
    cout << "|" << endl;
  }
  
  cout << "   |                  |BAR|                  |" << endl;
  
  for (int row = 5; row > 0; row --)
  {
    cout << "   ";
    cout << "|";
    
    for (int col = 1; col < 7; col ++)
    {
      displayStack(col, row);
    }
    
    cout << "|";
    displayStack(0, row);
    cout << "|";
    
    for (int col = 7; col < 13; col++)
    {
      displayStack(col, row);
    }
    
    cout << "|" << endl;
  }
  
  cout << "   +1--2--3--4--5--6---0---7--8--9--10-11-12-+" << endl;
  
  return;
}

//Writes 3 characters of the ASCII GUI to the screen
void AI::displayStack( int point, int height )
{
  int checkers = getPoint(point);
  char player = 'O';
  
  if ( checkers < 0 )
  {
    checkers *= -1;
    player = 'X';
  }
  
  if ( checkers < height )
  {
    cout << "  ";
  }
  
  else if ( height < 5 )
  {
    cout << player << " ";
  }
  
  else if ( checkers < 10 )
  {
    cout << checkers << " ";
  }
  
  else
  {
    cout << checkers;
  }
  
  cout << " ";
  
  return;
}

int AI::getDie( int i )
{
  switch ( i )
  {
    case 0:
      return serverBoards[0].die1();
    case 1:
      return serverBoards[0].die2();
    case 2:
      return serverBoards[0].die3();
    case 3:
      return serverBoards[0].die4();
    default:
      cout << "ERROR: getDie expects an index 0 to 3." << endl;
      return 0;
  }
}

int AI::getPoint( int i )
{
  switch ( i )
  {
    case 0:
      return serverBoards[0].bar0();
    case 1:
      return serverBoards[0].point1();
    case 2:
      return serverBoards[0].point2();
    case 3:
      return serverBoards[0].point3();
    case 4:
      return serverBoards[0].point4();
    case 5:
      return serverBoards[0].point5();
    case 6:
      return serverBoards[0].point6();
    case 7:
      return serverBoards[0].point7();
    case 8:
      return serverBoards[0].point8();
    case 9:
      return serverBoards[0].point9();
    case 10:
      return serverBoards[0].point10();
    case 11:
      return serverBoards[0].point11();
    case 12:
      return serverBoards[0].point12();
    case 13:
      return serverBoards[0].point13();
    case 14:
      return serverBoards[0].point14();
    case 15:
      return serverBoards[0].point15();
    case 16:
      return serverBoards[0].point16();
    case 17:
      return serverBoards[0].point17();
    case 18:
      return serverBoards[0].point18();
    case 19:
      return serverBoards[0].point19();
    case 20:
      return serverBoards[0].point20();
    case 21:
      return serverBoards[0].point21();
    case 22:
      return serverBoards[0].point22();
    case 23:
      return serverBoards[0].point23();
    case 24:
      return serverBoards[0].point24();
    case 25:
      return serverBoards[0].bar25();
    default:
      cout << "ERROR: getPoint requires an index 0 to 25." << endl;
      return 0;
  }
}

//The default run() function included
/*
bool AI::run()
{
  //Default code provided by professor to manually play.
  int action, from, to;
  displayBoard();
  cout << "Select an action:" << endl
    << "  1. Move" << endl
    << "  2. Bear Off" << endl
    << "  3. End turn" << endl;
  cin >> action;
  switch (action)
  {
    case 1:
    cout << "Move piece from where?" << endl;
    cin >> from;
    cout << "Move piece to where?" << endl;
    cin >> to;
    serverBoards[0].move(from, to);
    break;
    case 2:
    cout << "Bear off from where?" << endl;
    cin >> from;
    serverBoards[0].bearOff(from);
    break;
    case 3:
    cout << "Ending your turn" << endl;
    break;
  }
  //Returning true ends your turn, returning false requests a status update
  //and starts over at run.
  return action==3;
}*/

// END OF FILE ----------------------------------------------------------------

