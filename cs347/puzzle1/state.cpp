// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file state.h
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function declarations for a state of the TSP.
/// @note Assignment 1.
///////////////////////////////////////////////////////////////////////////////

#include "state.h"

//Default constructor
State::State()
{
  //Do nothing, the constructors of Vector and unsigned int handle themselves.
}

//Given a vector of visited status and a location
State::State( const Vector<bool>& cities, const unsigned int& loc, const double& cost )
{
  m_visited = cities;
  m_loc = loc;
  m_cost = cost;
}

//Given a specific size and a location
State::State( const unsigned int& size, const unsigned int& loc, const double& cost )
{
  m_visited.set_size( size, false );
  m_loc = loc;
  m_cost = cost;
}

//Gets the cities visited
Vector<bool> State::getVisited() const
{
  return m_visited;
}

//Sets the specified city to visited (true) status
void State::setVisited( const unsigned int& n )
{
  if ( n > m_visited.size() )
    throw Exception( 2, "Out of bounds access. State::setVisited()" );
    
  m_visited[n] = true;
  
  return;
}

//Gets the current location
unsigned int State::location() const
{
  return m_loc;
}

//Sets the current location
void State::setLocation( const unsigned int& n )
{
  if ( n > m_visited.size() )
    throw Exception( 3, "Out of bounds access. State::setLocation()" );
  m_loc = n;

  return;
}

//Gets the cost 
double State::cost() const
{
  return m_cost;
}

//sets the cost
void State::setCost( const double& d )
{
  m_cost = d;
  
  return;
}

//Equality operator
bool State::operator==( const State& rhs ) const
{
  if ( (m_visited == rhs.m_visited) && (m_loc == rhs.m_loc) && (m_cost == rhs.m_cost) )
    return true;
    
  return false;
}

//Inequality operator
bool State::operator!=( const State& rhs ) const
{
  return !( *this == rhs );
}

//Access operator
bool& State::operator[]( const unsigned int& n )
{
  if ( n > m_visited.size() )
    throw Exception( 4, "Out of bounds access. State::operator[]" );
    
  return m_visited[n];
}

//const access operator
const bool& State::operator[]( const unsigned int& n ) const
{
  if ( n > m_visited.size() )
    throw Exception( 5, "Out of bounds access. State::operator[] const" );
    
  return m_visited[n];
}

//assignment operator
State& State::operator=( const State& rhs )
{
  //check for self assignment
  if ( this == &rhs )
    return *this;
  
  m_visited = rhs.m_visited;
  m_loc = rhs.m_loc;
  m_cost = rhs.m_cost;
  
  return *this;
} 

// END OF FILE ----------------------------------------------------------------
