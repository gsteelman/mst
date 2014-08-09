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
/// @fn const Vector<bool>& get_visited() const
/// @brief Returns the vector representing the visited status of each city.
/// @pre A State object exists.
/// @post Returns the vector representing the visited status of each city.
/// @return const Vector<bool>& - represents the visited status of each city.
/// @note At each index in the returned vector, true means the city has been
///   visited. false means the city has not been visited.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<bool>& get_visited()
/// @brief Returns the vector representing the visited status of each city.
/// @pre A State object exists.
/// @post Returns the vector representing the visited status of each city.
/// @return Vector<bool>& - represents the visited status of each city.
/// @note At each index in the returned vector, true means the city has been
///   visited. false means the city has not been visited.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void set_visited( const unsigned int& n )
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
/// @fn void set_location( const unsigned int& n )
/// @brief Sets the specified city to current location.
/// @pre n < number of cities in the State.
/// @param const unsigned int& n - The city to set as the current location.
/// @post Sets the specified city to current location.
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
/// @fn State& operator=( const State& rhs )
/// @brief Assignment operator for State objects.
/// @pre A State object exists, rhs exists.
/// @param const State& rhs - The State to set the calling object equal to.
/// @post Sets the calling object's data equal to rhs' data.
/// @return State& - The calling object's address after edits.
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only included once during compilation
#include <vector>

using namespace std;

class State
{
  public:
    State();
    State( const vector<bool>& cities, const unsigned int& loc );
    State( const unsigned int& size, const unsigned int& loc );
    
    vector<bool>& get_visited();
    const vector<bool>& get_visited() const;
    void set_visited( const unsigned int& n );
    
    unsigned int location() const;
    void set_location( const unsigned int& n );
    
    bool operator==( const State& rhs ) const;
    bool operator!=( const State& rhs ) const;
    
    State& operator=( const State& rhs ); 
    
  private:
    //Array representing the visited status of each city in the list
    vector<bool> m_visited; 

    //Represents the current location of the salesman
    unsigned int m_loc;
};

// END OF FILE ----------------------------------------------------------------
