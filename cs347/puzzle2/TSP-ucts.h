// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file TSP-ucts.h
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function declarations for the UCTS for TSP.
/// @note Assignment 2.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class TSPUCTS
/// @brief Contains functionality for creating a TSP problem and solving it
///   via uniform cost tree search.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn TSPUCTS()
/// @brief Default constructor for the TSPUCTS object.
/// @pre None.
/// @post Creates a TSPUCTS object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn TSPUCTS( const Matrix<double>& m )
/// @brief Constructor that takes a specific graph.
/// @pre m exists.
/// @post Creates a TSPUCTS object with the specified graph.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn const Matrix<double>& getGraph() const
/// @brief Returns the graph used.
/// @pre a TSPUCTS object exists.
/// @post Returns the graph used.
/// @return const Matrix<double>& - The graph used.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned int getNumCities() const
/// @brief Returns the number of cities in the graph.
/// @pre a TSPUCTS object exists.
/// @post Returns the number of cities in the graph.
/// @return unsigned int - The number of cities in the graph.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setGraph( const Matrix<double>& m )
/// @brief Sets the graph to the specified graph.
/// @pre a TSPUCTS object exists.
/// @param const Matrix<double>& m - The graph to set.
/// @post Sets the graph to the specified graph.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn const State& currState() const
/// @brief Returns the current State.
/// @pre a TSPUCTS object exists.
/// @post Returns the current State.
/// @return const State& - The current State.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setCurrState( const State& s )
/// @brief Sets the current State to the specified State.
/// @pre A TSPUCTS object exists.
/// @post Sets the current State to the specified State.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void solve()
/// @brief Solves the TSPUCTS.
/// @pre A TSPUCTS object has been seeded with a graph.
/// @post Solves the TSPUCTS.
/// @return None.
/// @note Takes time to solve! Will only solve if necessary.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void successor( const State& iState, vector<State>& avail )
/// @brief Generates all succeding states of iState and stores them in avail.
/// @pre avail exists. iState exists.
/// @param const State& iState - The State to generate successors for.
/// @param vector<State>& avail - The vector to store successors in.
/// @post Generates all succeding states of iState and stores them in avail.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn const Vector<unsigned int>& get_solution()
/// @brief Returns the solution Vector.
/// @pre The TSPUCTS object has been solved.
/// @post Returns the solution Vector.
/// @return const Vector<unsigned int>& - The solution Vector.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn double distanceTraveled() const
/// @brief Returns the total distance traversed solving the TSPUCTS.
/// @pre The TSPUCTS has been solve()'d. 
/// @post Returns the total distance traversed solving the TSPUCTS.
/// @return double - The total distance traversed solving the TSPUCTS.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool isGoal( const State& s ) const
/// @brief Returns whether or not s is a goal state.
/// @pre s exists.
/// @param const State& s - The State to check if it is a goal.
/// @post Returns whether or not s is a goal state.
/// @return bool - true if s is a goal state. False otherwise.
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only compiled once
#include "state.h"
#include "vector.h"
#include <vector>
#include "matrix.h"

class TSPUCTS
{
  public:
    TSPUCTS();
    TSPUCTS( const Matrix<double>& m );
    
    const Matrix<double>& getGraph() const;
    unsigned int getNumCities() const;
    void setGraph( const Matrix<double>& m );
    
    const State& currState() const;
    void setCurrState( const State& s );
    
    void solve();
    const Vector<unsigned int>& get_solution() const;
    
    double distanceTraveled() const;

  protected:
    void successor( const State& iState, vector<State>& avail );
    bool isGoal( const State& s ) const;

  private:
    Matrix<double> m_graph;           //The graph representation of the cities
    unsigned int m_numCities;         //The number of cities in the representation
    
    State m_cState;                   //The current state information
    
    Vector<unsigned int> m_solution;  //The solution to the graph
    double m_totalDistance;           //The distance traversed generating the solution
    
    bool m_changed;                   //Marks whether or not we need to resolve
};

// END OF FILE ----------------------------------------------------------------
