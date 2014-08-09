// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file state.h
/// @author Gary Steelman
/// @edit 24 Jan 2010
/// @brief Function declarations for a state of the TSP.
/// @note Assignment 1.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class State
/// @brief Contains data storage for visited cities and current location.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn State()
/// @brief Default constructor for State.
/// @pre None.
/// @post Creates a State object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn State( const Vector<bool>& cities, const unsigned int& loc )
/// @brief Constructor that takes a pre-determined set of city visit status and
///   a specific location for a State representation.
/// @pre cities exists; loc exists.
/// @param const Vector<bool>& cities - The visited status for each city. 
/// @param const unsigned int& loc - The location for the salesman.
/// @post Creates a State object with the specified city visited status and 
///   salesman location.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn State( const unsigned int& size, const unsigned int& loc )
/// @brief Constructor that takes a predetermined number of cities and a 
///   specific location for the salesman.
/// @pre size exists; loc exists.
/// @param const unsigned int& size - The number of cities to have in the 
///   representation.
/// @param const unsigned int& loc - The location for the salesman.
/// @post Creates a State object with the specified number of cities and 
///   salesman location.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn const Vector<bool>& getVisited() const
/// @brief Returns the vector representing the visited status of each city.
/// @pre A State object exists.
/// @post Returns the vector representing the visited status of each city.
/// @return const Vector<bool>& - represents the visited status of each city.
/// @note At each index in the returned vector, true means the city has been
///   visited. false means the city has not been visited.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<bool>& getVisited()
/// @brief Returns the vector representing the visited status of each city.
/// @pre A State object exists.
/// @post Returns the vector representing the visited status of each city.
/// @return Vector<bool>& - represents the visited status of each city.
/// @note At each index in the returned vector, true means the city has been
///   visited. false means the city has not been visited.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setVisited( const unsigned int& n )
/// @brief Sets the specified city to visited (true) status.
/// @pre n < number of cities in the State.
/// @param const unsigned int& n - The city to visit.
/// @post Sets the specified city to visited (true) status.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned int location() const
/// @brief Returns the current location of the salesman.
/// @pre A State object exists.
/// @post Returns the current location of the salesman.
/// @return unsigned int - represents the location of the salesman.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setLocation( const unsigned int& n )
/// @brief Sets the specified city to current location.
/// @pre n < number of cities in the State.
/// @param const unsigned int& n - The city to set as the current location.
/// @post Sets the specified city to current location.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn double cost() const
/// @brief Returns the cost to reach this state from the previous state.
/// @pre None.
/// @post Returns the cost to reach this state from the previous state.
/// @return double - the cost to reach this state from the previous state.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void setCost( const unsigned double& d )
/// @brief Sets the cost to reach this state from the previous state.
/// @pre d exists.
/// @post Sets the cost to reach this state from the previous state.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator==( const State& rhs ) const
/// @brief Equivilancy operator for State objects.
/// @pre A State object exists, rhs exists.
/// @param const State& rhs - The State being compared to. 
/// @post Returns true if the State objects are equal.
/// @return bool - true if the State objects are equal.
///                false if the State objects are not equal.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator!=( const State& rhs ) const
/// @brief Inequivilancy operator for State objects.
/// @pre A State object exists, rhs exists.
/// @param const State& rhs - The State being compared to. 
/// @post Returns true if the State objects are not equal.
/// @return bool - true if the State objects are not equal.
///                false if the State objects are equal.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator>( const State& rhs ) const
/// @brief Returns whether or not the left hand State's cost > right hand State's
/// @pre rhs Exists.
/// @param const State& rhs - The right hand side of the > operator.
/// @post Returns whether or not the left hand State's cost > right hand State's
/// @return bool - true if the State on the left hand side has a higher cost.
///                false if the State on the left hand side has a lower cost.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool& operator[]( const unsigned int& n )
/// @fn const bool& operator[]( const unsigned int& n ) const
/// @brief Returns the visited status of city n.
/// @pre A State object exists.
/// @pre n < number of cities in the State.
/// @param const unsigned int& n - The city data to access.
/// @post Returns the visited status of city n.
/// @return bool - The visited status of city n. 
/// @note At each index true means the city has been visited. 
///                     false means the city has not been visited.
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn State& operator=( const State& rhs )
/// @brief Assignment operator for State objects.
/// @pre A State object exists, rhs exists.
/// @param const State& rhs - The State to set the calling object equal to.
/// @post Sets the calling object's data equal to rhs' data.
/// @return State& - The calling object's address after edits.
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only included once during compilation
#include "vector.h"
#include <vector>

class State
{
  public:
    State();
    State( const vector<bool>& cities, const unsigned int& loc, const double& cost );
    State( const unsigned int& size, const unsigned int& loc, const double& cost );
    
    vector<bool>& getVisited();
    const vector<bool>& getVisited() const;
    void setVisited( const unsigned int& n );
    
    unsigned int location() const;
    void setLocation( const unsigned int& n );
    
    double cost() const;
    void setCost( const double& d );
    
    bool operator==( const State& rhs ) const;
    bool operator!=( const State& rhs ) const;
    
    bool operator>( const State& rhs ) const;
    
    State& operator=( const State& rhs ); 
    
    //Array representing the path taken to get to this city
    Vector<unsigned int> m_path;
    
  private:
    //Array representing the visited status of each city in the list
    vector<bool> m_visited; 

    //Represents the current location of the salesman
    unsigned int m_loc;
    
    //Cost to arrive at this state
    double m_cost;
};

// END OF FILE ----------------------------------------------------------------
