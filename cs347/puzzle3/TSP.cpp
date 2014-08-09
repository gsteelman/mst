// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file TSP.cpp
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function definitions for the uniform cost tree search algorithm.
/// @note Assignment 2.
///////////////////////////////////////////////////////////////////////////////

#include "TSP.h"
#include "vector.h"
#include "state.h"
#include "search_node.h"
#include <vector>
#include <cstdlib>
#include <functional>
#include <queue>
#include <ctime>
#include <cfloat>

using namespace std;

TSP::TSP():m_num_cities(0), m_total_distance(0), m_changed(true) {}

TSP::TSP( const Matrix<double>& m ):m_graph(m), m_total_distance(0), m_changed(true) 
{
  srand( time( NULL ) ); 
  m_num_cities = m.width();
}

const Matrix<double>& TSP::graph() const 
{  
  return m_graph; 
}

unsigned int TSP::num_cities() const 
{
  return m_num_cities;  
}

void TSP::set_graph( const Matrix<double>& m ) 
{

  srand( time( NULL ) ); 
  m_graph = m;
  m_num_cities = m.width();
  
  m_total_distance = 0;
  m_changed = true;
  
  return;  
}

void TSP::solve_UCGS() 
{
  //We'll only recalculate the solution if we haven't done it already
  if ( m_changed == true )
  {
    //For holding the nodes of the search
    priority_queue<search_node, deque<search_node>, greater<search_node> > frontier;
    
    //For holding nodes already expanded on
    deque<search_node> explored;
    
    //Seed the search tree
    srand( time( NULL ) ); 
    State initState( m_graph.width(), rand()%m_num_cities );
    search_node root( initState, 0 );
    root.m_path.push_back( initState.location() );
    search_node curr_node = root;
    
    //Set the first node
    frontier.push( root );
    
    //Holds the search nodes generated by the successor function
    vector<search_node> avail;
    
    while ( !frontier.empty() )
    { 
      //Grab the node at the top
      curr_node = frontier.top();
      
      //If it's a goal we're done
      if ( is_goal( curr_node ) )
        break;
      
      //Otherwise we'll need to generate more successors from it
      frontier.pop();
      avail.clear();
      successor( curr_node, avail );
      
      //In the case we've reached a state where all cities have been visited
      if ( avail.empty() )
      {
        avail.push_back( curr_node );
        avail.back().m_path.push_back( curr_node.m_path[0] );
        avail.back().set_cost( curr_node.cost() + m_graph[curr_node.m_path[0]][curr_node.get_state().location()] );
        avail.back().get_state().set_location( curr_node.m_path[0] );
      }
     
      explored.push_back( curr_node );

      bool append = true;
      
      //Push all generated States onto the search queue, but only if we
      //haven't seen them before. Takes time, but stops the algorithm from
      //using gigabytes of memory.
      for ( unsigned int i = 0; i < avail.size(); i++ ) {
      
        append = true;
        
        for ( unsigned int j = 0; j < explored.size(); j++ ) {
        
          if ( avail[i] == explored[j] )
            append = false;
        }
        
        if ( append )
          frontier.push( avail[i] );
      }
    } 
    
    m_solution = curr_node.m_path;
    m_total_distance = curr_node.cost();
    m_changed = false;
  }

  return;
}

void TSP::solve_ILTS()
{
  //We'll only recalculate the solution if we haven't done it already
  if ( m_changed == true )
  {
    //For holding the nodes of the search
    //puts the node with the largest path cost on the top
    priority_queue<search_node, deque<search_node>, greater<search_node> > frontier;
    
    //Holds the search nodes generated by the successor function
    vector<search_node> avail;
    
    //Seed the search tree
    srand( time( NULL ) ); 
    State initState( m_graph.width(), rand()%m_num_cities );
    search_node root( initState, 0 );
    root.m_path.push_back( initState.location() );
    search_node curr_node = root;
    
    // 1
    double MAXPATHCOST = 0;
    bool GOALFOUND = false;
    
    while ( !GOALFOUND )
    {
      // 2
      double NEXTPATHCOST = DBL_MAX;

      //Set the first node
      // 3
      frontier.push( root );
      
      // 10
      while ( !frontier.empty() )
      { 
        //Grab the node at the top
        // 4
        curr_node = frontier.top();
        
        // 6
        //If it's a goal we're done
        if ( is_goal( curr_node ) )
        {
          GOALFOUND = true;
          break;
        }
        
        // 5
        //Otherwise we'll need to generate more successors from it
        frontier.pop();
        avail.clear();
        
        // 7
        successor( curr_node, avail );
        
        //In the case we've reached a state where all cities have been visited
        if ( avail.empty() )
        {
          avail.push_back( curr_node );
          avail.back().m_path.push_back( curr_node.m_path[0] );
          avail.back().set_cost( curr_node.cost() + m_graph[curr_node.m_path[0]][curr_node.get_state().location()] );
          avail.back().get_state().set_location( curr_node.m_path[0] );
        }

        for ( unsigned int i = 0; i < avail.size(); i++ )
        {
          // 8
          if ( avail[i].cost() > MAXPATHCOST )
          {
            if ( NEXTPATHCOST > avail[i].cost() )
            {
              NEXTPATHCOST = avail[i].cost();           
            }
          // 9
          }
          else
          {
            frontier.push( avail[i] );
          }
        }  
        // 10
      }
      
      // 11
      MAXPATHCOST = NEXTPATHCOST;
    }
    
    m_solution = curr_node.m_path;
    m_total_distance = curr_node.cost();
    m_changed = false;
  }

  return;
}

void TSP::successor( const search_node& iNode, vector<search_node>& avail ) 
{   
  //For each city in the current state
  for ( unsigned long int i = 0; i < m_num_cities; i++ )
  {
    //If that city has not been visited
    if ( !iNode.get_state().get_visited()[i] )
    {
      //Then push it into the list of available states to move to
      avail.push_back( iNode );
      
      //And update it to reflect what would happen after we move there
      avail.back().get_state().set_visited(i);
      avail.back().get_state().set_location(i);
      avail.back().m_path.push_back(i);
      avail.back().set_cost( iNode.cost() + m_graph[iNode.get_state().location()][avail.back().get_state().location()] );
    }
  }

  return;
}

const Vector<unsigned int>& TSP::get_solution() const 
{
  return m_solution;
}

double TSP::dist_traveled() const 
{
  return m_total_distance; 
}

//Returns if the state is a goal state
bool TSP::is_goal( const search_node& s ) const
{
  //If we aren't in the initial city, there's no way we're done
  if ( s.get_state().location() != s.m_path[0] )
    return false;  
  
  //Check each city for visited status
  for ( unsigned long int i = 0; i < m_num_cities; i++ )
    if ( s.get_state().get_visited()[i] == false )
      return false;
  
  return true;
}

// END OF FILE ----------------------------------------------------------------
