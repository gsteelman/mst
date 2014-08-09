// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file TSP.h
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function declarations for the UCTS for TSP.
/// @note Assignment 2.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class TSP
/// @brief Contains functionality for creating a TSP problem and solving it
///   via uniform cost tree search.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn TSP()
/// @brief Default constructor for the TSP object.
/// @pre None.
/// @post Creates a TSP object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn TSP( const Matrix<double>& m )
/// @brief Constructor that takes a specific graph.
/// @pre m exists.
/// @post Creates a TSP object with the specified graph.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn const Matrix<double>& graph() const
/// @brief Returns the graph used.
/// @pre a TSP object exists.
/// @post Returns the graph used.
/// @return const Matrix<double>& - The graph used.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned int num_cities() const
/// @brief Returns the number of cities in the graph.
/// @pre a TSP object exists.
/// @post Returns the number of cities in the graph.
/// @return unsigned int - The number of cities in the graph.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void set_graph( const Matrix<double>& m )
/// @brief Sets the graph to the specified graph.
/// @pre a TSP object exists.
/// @param const Matrix<double>& m - The graph to set.
/// @post Sets the graph to the specified graph.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void solve_UCGS()
/// @brief Solves the TSP via uniform cost graph search.
/// @pre A TSP object has been seeded with a graph.
/// @post Solves the TSP.
/// @return None.
/// @note Takes time to solve! Will only solve if necessary.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void solve_ILTS()
/// @brief Solves the TSP via iterating length tree search.
/// @pre A TSP object has been seeded with a graph.
/// @post Solves the TSP.
/// @return None.
/// @note Takes time to solve! Will only solve if necessary.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void successor( const search_node& iNode, vector<search_node>& avail )
/// @brief Generates all succeding nodes of iNode and stores them in avail.
/// @pre avail exists. iNode exists.
/// @param const search_node& iNode - The node to generate successors for.
/// @param vector<search_node>& avail - The vector to store successors in.
/// @post Generates all succeding states of iState and stores them in avail.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn const Vector<unsigned int>& get_solution()
/// @brief Returns the solution Vector.
/// @pre The TSP object has been solved.
/// @post Returns the solution Vector.
/// @return const Vector<unsigned int>& - The solution Vector.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn double dist_traveled() const
/// @brief Returns the total distance traversed solving the TSP.
/// @pre The TSP has been solve()'d. 
/// @post Returns the total distance traversed solving the TSP.
/// @return double - The total distance traversed solving the TSP.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool is_goal( const search_node& s ) const
/// @brief Returns whether or not s is a goal node.
/// @pre s exists.
/// @param const search_node& s - The node to check if it is a goal.
/// @post Returns whether or not s is a goal node.
/// @return bool - true if s is a goal node. False otherwise.
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only compiled once
#include "search_node.h"
#include "vector.h"
#include "matrix.h"
#include <vector>

using namespace std;

class TSP
{
  public:
  
    TSP();
    TSP( const Matrix<double>& m );
    
    const Matrix<double>& graph() const;
    void set_graph( const Matrix<double>& m );
    unsigned int num_cities() const;

    void solve_UCGS();
    void solve_ILTS();
    
    const Vector<unsigned int>& get_solution() const;
    
    double dist_traveled() const;

  protected:
    
    void successor( const search_node& iNode, vector<search_node>& avail );
    bool is_goal( const search_node& s ) const;

  private:
    
    Matrix<double> m_graph;           //The graph representation of the cities
    unsigned int m_num_cities;        //The number of cities in the representation
    
    Vector<unsigned int> m_solution;  //The solution to the graph
    double m_total_distance;          //The distance traversed generating the solution
    
    bool m_changed;                   //Marks whether or not we need to resolve
};

// END OF FILE ----------------------------------------------------------------
