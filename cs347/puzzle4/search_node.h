// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file state.h
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function declarations for a state of the TSP.
/// @note Assignment 1.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class search_node
/// @brief Contains the state and path information for a state of the TSP
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn search_node()
/// @brief Default constructor for a search node.
/// @pre None.
/// @post Creates a default search_node object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn search_node( const State& s, const double& cost )
/// @brief Constructor for a search_node given a specific state and cost.
/// @pre s, cost exist.
/// @param s - the State to inclue in the search_node.
/// @param cost - the cumulative path cost to arrive at s.
/// @post Creates a search_node object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn State& get_state();
/// @fn const State& get_state() const;
/// @brief Returns the state contained in the node.
/// @pre a search_node object exists.
/// @post Returns the state contained in the node.
/// @return state& - reference to the state contained in the node.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn double cost() const
/// @brief Returns the cost to reach this node.
/// @pre a search_node object exists.
/// @post Returns the cost to reach this node.
/// @return double - the cost to reach this node.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void set_cost( const double& d )
/// @brief sets the cost to reach this node to d.
/// @pre d exists.
/// @param const double& d - the cost to set the path cost to.
/// @post sets the cost to reach this node to d.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator==( const search_node& rhs ) const
/// @brief Checks to see if two nodes are equivalent.
/// @pre rhs exists.
/// @param const search_node& rhs - The node to compare to.
/// @post Checks to see if two nodes are equivalent.
/// @return bool - true if the nodes are equivalent, false otherwise.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator!=( const search_node& rhs ) const
/// @brief Checks to see if two nodes are not equivalent.
/// @pre rhs exists.
/// @param const search_node& rhs - The node to compare to.
/// @post Checks to see if two nodes are not equivalent.
/// @return bool - true if the nodes are not equivalent, false otherwise.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator>( const search_node& rhs ) const
/// @brief Checks to see if lhs' path cost > rhs' path cost.
/// @pre rhs exists.
/// @param const search_node& rhs - The node to compare to.
/// @post Checks to see if lhs' path cost > rhs' path cost.
/// @return bool - true if lhs' path cost > rhs', false otherwise.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator<( const search_node& rhs ) const
/// @brief Checks to see if lhs' path cost < rhs' path cost.
/// @pre rhs exists.
/// @param const search_node& rhs - The node to compare to.
/// @post Checks to see if lhs' path cost < rhs' path cost.
/// @return bool - true if lhs' path cost < rhs', false otherwise.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn search_node& operator=( const search_node& rhs )
/// @brief sets the calling object equal to rhs.
/// @pre rhs exists.
/// @param const search_node& rhs - The node to set to.
/// @post sets the calling object equal to rhs.
/// @return search_node& - Reference to the calling object after it has been
///   changed.
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only included once during compilation
#include "vector.h"
#include "state.h"

using namespace std;

class search_node
{
  public:
  
    search_node();
    search_node( const State& s, const double& cost );

    State& get_state();
    const State& get_state() const;
    
    const double& cost() const;
    void set_cost( const double& d );
    
    bool operator==( const search_node& rhs ) const;
    bool operator!=( const search_node& rhs ) const;
    
    bool operator>( const search_node& rhs ) const;
    bool operator<( const search_node& rhs ) const;
    
    search_node& operator=( const search_node& rhs ); 
    
    //Array representing the path taken to get to this city
    Vector<unsigned int> m_path;
    
  private:
  
    State m_state;  //State held by this search node
    
    double m_cost;  //Cost to arrive at m_state
};
