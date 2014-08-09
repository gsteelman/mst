// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file TSP-Rand.cpp
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function definitions for the random selection solution to TSP.
/// @note Assignment 1.
///////////////////////////////////////////////////////////////////////////////

#include "TSP-rand.h"
#include "Vector.h"
#include "state.h"
#include <cstdlib>
#include <ctime>

//Default constructor
TSPRand::TSPRand()
{
  m_numCities = 0;
  m_totalDistance = 0;
  m_changed = true;
}

//Constructor given a graph
TSPRand::TSPRand( const Matrix<double>& m )
{
  srand( time( NULL ) ); //Since we start in a random city
  m_graph = m;
  m_numCities = m.width();
  
  unsigned int startCity = rand() % m.width();
  State defaultState( m.width(), startCity, 0 );
  m_cState = defaultState;
  m_cState.setVisited( startCity );
  m_solution.push_back( startCity );
  m_nState = defaultState;
  
  m_numCities = 0;
  m_totalDistance = 0;
  m_changed = true;
}

//Gets the graph
Matrix<double> TSPRand::getGraph() const
{
  return m_graph;
}

//Gets the number of cities
unsigned int TSPRand::getNumCities() const
{
  return m_numCities;
}

//Sets the graph to a specified matrix
void TSPRand::setGraph( const Matrix<double>& m )
{
  srand( time( NULL ) ); //Since we start in a random city
  m_graph = m;
  m_numCities = m.width();
  
  unsigned int startCity = rand() % m.width();
  State defaultState( m.width(), startCity, 0 );
  m_cState = defaultState;
  m_cState.setVisited( startCity );
  m_solution.push_back( startCity );
  m_nState = defaultState;
  
  m_numCities = 0;
  m_totalDistance = 0;
  m_changed = true;
  
  return;
}

//Gets the current state
State TSPRand::currState() const
{
  return m_cState;
}

//Sets the current state
void TSPRand::setCurrState( const State& s )
{
  m_cState = s;
  m_changed = true;
  
  return;
}

//Gets the next state
State TSPRand::nextState() const
{
  return m_nState;
}

//Sets the next state
void TSPRand::setNextState( const State& s )
{
  m_nState = s;
  m_changed = true;
  
  return;
}

//Solves the TSP 
void TSPRand::solve() 
{
  //We'll only recalculate the solution if we haven't done it already
  if ( m_changed == true )
  {
    //To hold all available successor states
    Vector<State> avail;
    
    do
    {
      //Grab all available successor states
      avail = successor( m_cState );
      
      //Choose a random one
      unsigned int goTo = rand() % avail.size();
    
      //Relocate to it
      move( m_cState, avail[goTo] );
    } 
    while( avail.size() > 1 );
    
    m_changed = false;
  }

  return;
}

//Generates all successors of the given state
Vector<State> TSPRand::successor( const State& iState )
{
  Vector<State> avail;
  State nState;
  
  //For each city in the current state
  for ( unsigned long int i = 0; i < iState.getVisited().size(); i++ )
  {
    //If that city has not been visited
    if ( iState[i] == false )
    {
      //Make a copy State, mark the current city visited and note its location
      nState = iState;
      nState.setVisited( i );
      nState.setLocation( i );
      
      //Then push it into the list of available states to move to
      avail.push_back( nState );
    }
  }
  
  return avail;
}

//"moves" from lhs to rhs States
void TSPRand::move( State& iState, State& nState )
{
  //Record the city we are moving to
  m_solution.push_back( nState.location() );
  
  //Record the distance from iState to nState, as pulled from the graph
  m_totalDistance += m_graph[iState.location()][nState.location()];
  
  //Make the current state where we wanted to go to
  iState = nState;

  return;
}

//Returns the solution vector
Vector<unsigned int> TSPRand::get_solution()
{
  return m_solution;
}

//returns the distance traveled
double TSPRand::distanceTraveled() const
{
  return m_totalDistance;
}

// END OF FILE ----------------------------------------------------------------
