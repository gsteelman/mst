// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file state.cpp
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function definitions for a state of the TSP.
///////////////////////////////////////////////////////////////////////////////

#include "state.h"
#include "exception.h"

State::State():m_loc(0) {}

State::State( const vector<bool>& cities, const unsigned int& loc ):m_loc(loc)
{
  if ( loc > cities.size() )
    throw Exception( 4, "Out of bounds access. Invalid start location. State::State()" );
    
  m_visited = cities;
  m_visited[loc] = true;
}

State::State( const unsigned int& size, const unsigned int& loc ):m_loc(loc) 
{
  if ( loc > size )
    throw Exception( 4, "Out of bounds access. Invalid start location. State::State()" );
    
  m_visited.resize( size, false );
  m_visited[loc] = true;
}

vector<bool>& State::get_visited() 
{
  return m_visited;
}

const vector<bool>& State::get_visited() const 
{
  return m_visited;
}

void State::set_visited( const unsigned int& n ) 
{
  if ( n > m_visited.size() )
    throw Exception( 2, "Out of bounds access. State::set_visited()" );
    
  m_visited[n] = true;
  
  return;
}

void State::set_unvisited( const unsigned int& n ) 
{
  if ( n > m_visited.size() )
    throw Exception( 2, "Out of bounds access. State::set_unvisited()" );
    
  m_visited[n] = false;
  
  return;
}

unsigned int State::location() const 
{
  return m_loc; 
}

void State::set_location( const unsigned int& n ) 
{
  if ( n > m_visited.size() )
    throw Exception( 3, "Out of bounds access. State::set_location()" );
    
  m_loc = n;

  return; 
}

bool State::operator==( const State& rhs ) const 
{
  if ( (m_visited == rhs.m_visited) && (m_loc == rhs.m_loc) )
      return true;
  
  return false;
}

bool State::operator!=( const State& rhs ) const 
{
  return !( *this == rhs ); 
}

State& State::operator=( const State& rhs ) 
{
  //check for self assignment
  if ( this == &rhs )
    return *this;
  
  m_visited = rhs.m_visited;
  m_loc = rhs.m_loc;
  
  return *this;
} 

// END OF FILE ----------------------------------------------------------------
