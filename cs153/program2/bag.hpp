///////////////////////////////////////////////////////////////////////////////
/// @file bag.hpp
/// @author Gary Steelman, CS153-B
/// @edited 29 Jan 08
/// @brief Bag class implementation file
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
///   Calls the included "selectSort()" function
/// @pre A Bag object exists
///   The selectSort function is included
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

#ifndef BAG_HPP
#define BAG_HPP

#include <iostream>
#include "selectionsort.h"

using namespace std;

template <class generic>
Bag<generic>::Bag()
{
  m_size = 0;
  m_max_size = _INITIALDATASIZE;
  memset(m_data, NULL, _INITIALDATASIZE);
  
  return;
}

template <class generic>
void Bag<generic>::push_back( generic x )
{
  m_data[m_size] = x;
  m_size+=1;
  
  return;
}

template <class generic>
void Bag<generic>::pop_back()
{
  m_data[m_size - 1] = NULL;
  m_size-=1;
  
  return;
}

template <class generic>
generic& Bag<generic>::operator[]( unsigned int x ) 
{
  return m_data[x];
}

template <class generic>  
unsigned int Bag<generic>::search( generic x ) 
{
  for (int i = 0; i < m_size; i++)
  {
    if (m_data[i] == x)
    {
      return i;
    }
  }
  
  return -1;
}

template <class generic>
void Bag<generic>::sort()
{
  selectSort(m_data, m_max_size);
  
  return;
}

template <class generic>
unsigned int Bag<generic>::size()
{
  return m_size;
}

template <class generic>
unsigned int Bag<generic>::max_size() 
{
  return m_max_size;
}

#endif
