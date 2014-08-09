// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file state.cpp
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function definitions for a state of the TSP.
/// @note Assignment 2.
///////////////////////////////////////////////////////////////////////////////

#include "state.h"

State::State():m_loc(0), m_cost(0) {}

State::State( const vector<bool>& cities, const unsigned int& loc, const double& cost ) {

  if ( loc > cities.size() )
    throw Exception( 4, "Out of bounds access. Invalid start location. State::State()" );
    
  m_visited = cities;
  m_loc = loc;
  m_visited[loc] = true;
  m_path.push_back( loc );
  m_cost = cost;
  
}

State::State( const unsigned int& size, const unsigned int& loc, const double& cost ) {

  if ( loc > size )
    throw Exception( 4, "Out of bounds access. Invalid start location. State::State()" );
    
  m_visited.resize( size, false );
  m_loc = loc;
  m_visited[loc] = true;
  m_path.push_back( loc );
  m_cost = cost;
  
}

const vector<bool>& State::getVisited() const {

  return m_visited;
  
}

vector<bool>& State::getVisited() {

  return m_visited;
  
}

void State::setVisited( const unsigned int& n ) {

  if ( n > m_visited.size() )
    throw Exception( 2, "Out of bounds access. State::setVisited()" );
    
  m_visited[n] = true;
  
  return;
  
}

unsigned int State::location() const {

  return m_loc;
  
}

void State::setLocation( const unsigned int& n ) {

  if ( n > m_visited.size() )
    throw Exception( 3, "Out of bounds access. State::setLocation()" );
    
  m_loc = n;

  return;
  
}

double State::cost() const {

  return m_cost;
  
}

void State::setCost( const double& d ) {

  m_cost = d;
  
  return;
  
}

bool State::operator==( const State& rhs ) const {

  if ( (m_visited == rhs.m_visited) && (m_loc == rhs.m_loc) )
      return true;
  
  return false;
  
}

bool State::operator!=( const State& rhs ) const {

  return !( *this == rhs );
  
}

bool State::operator>( const State& rhs ) const {

  return ( m_cost > rhs.m_cost );
  
}

State& State::operator=( const State& rhs ) {

  //check for self assignment
  if ( this == &rhs )
    return *this;
  
  m_visited = rhs.m_visited;
  m_loc = rhs.m_loc;
  m_cost = rhs.m_cost;
  m_path = rhs.m_path;
  
  return *this;
  
} 

// END OF FILE ----------------------------------------------------------------
