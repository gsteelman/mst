// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file search_node.cpp
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function definitions for a search node of the TSP.
///////////////////////////////////////////////////////////////////////////////

#include "search_node.h"

search_node::search_node():m_cost(0) {}

search_node::search_node( const State& s, const double& cost):m_state(s), m_cost(cost)
{}

State& search_node::get_state()
{
  return m_state;
}

const State& search_node::get_state() const
{
  return m_state;
}

const double& search_node::cost() const
{
  return m_cost;
}

void search_node::set_cost( const double& d )
{
  m_cost = d;
}

bool search_node::operator==( const search_node& rhs ) const 
{
  if (   (m_state == rhs.m_state) 
      && (m_cost == rhs.m_cost) 
      && (m_path == rhs.m_path)
     )
      return true;
  
  return false;
}

bool search_node::operator>( const search_node& rhs ) const
{
  return (m_cost > rhs.m_cost);
}

bool search_node::operator<( const search_node& rhs ) const
{
  return (m_cost < rhs.m_cost);
}

bool search_node::operator!=( const search_node& rhs ) const 
{
  return !( *this == rhs ); 
}

search_node& search_node::operator=( const search_node& rhs ) 
{
  //check for self assignment
  if ( this == &rhs )
    return *this;
  
  m_state = rhs.m_state;
  m_cost = rhs.m_cost;
  m_path = rhs.m_path;
  
  return *this;
} 

// END OF FILE ----------------------------------------------------------------
