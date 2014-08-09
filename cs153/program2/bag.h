///////////////////////////////////////////////////////////////////////////////
/// @file bag.h
/// @author Gary Steelman, CS153-B
/// @edited 29 Jan 08
/// @brief Bag class header file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class Bag
/// @brief Contains the prototypes for the Bag class
///   This class has templated functionality for adding, subtracting elements
///   from an array, sorting arrays.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Bag
/// @brief Default constructor for the Bag class
/// @pre None
/// @post Creates a Bag class with the default values
/// @return Nothing.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_back
/// @brief Adds an item to the end of the bag 
/// @pre A Bag object exists, x is of same datatype as the Bag
/// @post Adds the passed parameter to the end of the bag 
/// @param x passed parameter will be added to the end of the bag
/// @return Nothing.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_back
/// @brief Removes the last element in the bag
/// @pre A Bag object exists
/// @post Removes the last element in the bag
/// @return Nothing.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn operator[]
/// @brief Overloads the Bag class to use []
/// @pre None
/// @post Adds functionality such that Bag[] refers to an element in the m_data
///   array
/// @return Nothing.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn search
/// @brief Searches the m_data array for passed parameter 
/// @pre A Bag object exists, x is of same datatype as the Bag
/// @post Returns the first located index of x (search is from index 0 to larger
///   indicies values)
/// @param x passed searched for in the m_data array
/// @return Returns the first located index of x 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn sort
/// @brief Sorts the Bag from least value to greatest value
/// @pre A Bag object exists
/// @post Sorts the Bag class from least value to greatest value
/// @return Nothing.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size
/// @brief Gets the number of how many elements are currently being used
/// @pre A Bag object exists
/// @post None
/// @return m_size
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn max_size
/// @brief Gets the number of how many elements are available to be used
/// @pre A Bag object exists
/// @post None
/// @return m_max_size
///////////////////////////////////////////////////////////////////////////////

#ifndef BAG_H
#define BAG_H

#include <iostream>
#include "selectionsort.h"

///Global Variables
const int _INITIALDATASIZE = 20; ///< Holds the initial size of the array

template <class generic>

class Bag
{
  public:
    Bag();
    void push_back( generic x );
    void pop_back();
    generic& operator[]( unsigned int x );
    unsigned int search( generic x );
    void sort();
    unsigned int size();
    unsigned int max_size();
  
  private:
    unsigned int m_size; ///< Holds the number of elements currently in use
    unsigned int m_max_size; ///< Holds the max number of elements available
    generic m_data[_INITIALDATASIZE]; ///< Holds the elements of the bag
};

#include "bag.hpp"
#endif
