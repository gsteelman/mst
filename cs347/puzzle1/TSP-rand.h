// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file TSP-Rand.h
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function declarations for the random selection solution to TSP.
/// @note Assignment 1.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class TSPRand
/// @brief Contains functionality for creating a TSP problem and solving it
///   via a random selection algorithm.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn TSPRand()
/// @brief Default constructor for the TSPRand object.
/// @pre None.
/// @post Creates a TSPRand object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn TSPRand( const Matrix<double>& m )
/// @brief Constructor that takes a specific graph.
/// @pre m exists.
/// @post Creates a TSPRand object with the specified graph.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix<double> getGraph() const
/// @brief Returns the graph used.
/// @pre a TSPRand object exists.
/// @post Returns the graph used.
/// @return Matrix<double> - The graph used.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned int getNumCities() const
/// @brief Returns the number of cities in the graph.
/// @pre a TSPRand object exists.
/// @post Returns the number of cities in the graph.
/// @return unsigned int - The number of cities in the graph.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setGraph( const Matrix<double>& m )
/// @brief Sets the graph to the specified graph.
/// @pre a TSPRand object exists.
/// @param const Matrix<double>& m - The graph to set.
/// @post Sets the graph to the specified graph.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn State currState() const
/// @brief Returns the current State.
/// @pre a TSPRand object exists.
/// @post Returns the current State.
/// @return State - The current State.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setCurrState( const State& s )
/// @brief Sets the current State to the specified State.
/// @pre A TSPRand object exists.
/// @post Sets the current State to the specified State.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn State nextState() const
/// @brief Returns the next State.
/// @pre a TSPRand object exists.
/// @post Returns the next State.
/// @return State - The next State.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setNextState( const State& s )
/// @brief Sets the next State to the specified State.
/// @pre A TSPRand object exists.
/// @post Sets the next State to the specified State.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void solve()
/// @brief Solves the TSPRand.
/// @pre A TSPRand object has been seeded with a graph.
/// @post Solves the TSPRand.
/// @return None.
/// @note Takes time to solve! Will only solve if necessary.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<unsigned int> get_solution()
/// @brief Returns the solution Vector.
/// @pre The TSPRand object has been solved.
/// @post Returns the solution Vector.
/// @return Vector<unsigned int> - The solution Vector.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn double distanceTraveled() const
/// @brief Returns the total distance traversed solving the TSPRand.
/// @pre The TSPRand has been solve()'d. 
/// @post Returns the total distance traversed solving the TSPRand.
/// @return double - The total distance traversed solving the TSPRand.
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only compiled once
#include "state.h"
#include "Vector.h"
#include "matrix.h"

class TSPRand
{
  public:
    TSPRand();
    TSPRand( const Matrix<double>& m );
    
    Matrix<double> getGraph() const;
    unsigned int getNumCities() const;
    void setGraph( const Matrix<double>& m );
    
    State currState() const;
    void setCurrState( const State& s );
    
    State nextState() const;
    void setNextState( const State& s );
    
    void solve();
    Vector<unsigned int> get_solution();
    
    double distanceTraveled() const;
  
  protected:
    Vector<State> successor( const State& iState );
    void move( State& iState, State& nState );

  private:
    Matrix<double> m_graph;           //The graph representation of the cities
    unsigned int m_numCities;         //The number of cities in the representation
    
    State m_cState;                   //The current state information
    State m_nState;                   //The next state information
    
    Vector<unsigned int> m_solution;  //The solution to the graph
    double m_totalDistance;           //The distance traversed generating the solution
    
    bool m_changed;                   //Marks whether or not we need to resolve
};

// END OF FILE ----------------------------------------------------------------
