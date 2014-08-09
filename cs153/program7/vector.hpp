///////////////////////////////////////////////////////////////////////////////
/// @file vector.hpp
/// @author Gary Steelman, CS153-B
/// @edited 4 Mar 08
/// @brief Vector class function implementation file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector
/// @brief Constructor for the Vector class
/// @pre None
/// @post Creates a Vector class object
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Vector
/// @brief Destructor for the Vector class
/// @pre Deletes the pointer member of the Vector class when the vector is
///   destroyed
/// @post None
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_back
/// @brief Adds an item to the end of the Vector
/// @pre A Vector object exists, x is of same datatype as the Bag
/// @post Adds the passed parameter to the end of the bag 
/// @param x passed parameter will be added to the end of the bag
/// @return Nothing.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_back
/// @brief Removes the last element in the Vector
/// @pre A Vector object exists
/// @post Removes the last element in the Vector 
/// @return Nothing.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear
/// @brief Resets the data for a Vector to the Constructor data 
/// @pre A Vector object exists
/// @post Resets the data for a vector the constructor data
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn operator[]
/// @brief Adds functionality to refer to the Vector class like an array
/// @pre A vector object exists
/// @post Allows vector v[index] to be remapped to the m_data pointer
/// @param x passed parameter will refer to the m_data pointer location
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size
/// @brief Gets the current size of the memory usage
/// @pre A vector object exists
/// @post Returns the size of the memory in use
/// @return Returns the size of the memory in use (unsigned int)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn max_size
/// @brief Gets the max size of the current memory usable
/// @pre A vector object exists
/// @post Returns the max size of the current memory usable
/// @return Returns the max size of the current memory usable
///////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "exception.h"

using namespace std;

template <class generic>
Vector<generic>::Vector() 
{
  m_size = 0;
  m_max_size = 1;
  m_data = new generic[m_max_size];
}

template <class generic>
generic& Vector<generic>::operator[]( unsigned int x ) 
{
  if (x < 0) 
  {
    throw( Exception(2, "You have tried to access an element outside the range of this vector.") );
  }
  
  else if (x > m_max_size)
  {
    throw( Exception(2, "You have tried to access an element outside the range of this vector.") );
  }
  
  else 
  {
  return m_data[x];
  }
}

template <class generic>
void Vector<generic>::push_back( generic x )
{
  if( m_size < m_max_size )
  {
    m_data[m_size] = x;
    m_size++;
  }
  
  else
  {
    generic * temp = m_data;
    m_max_size *= 2;
    m_data = new generic[m_max_size];
    
    for( int i = 0; i < m_size; i++ )
    {
      m_data[i] = temp[i];
    }
  
    delete [] temp;
    
    m_data[m_size] = x;
    m_size++;
  }
  
  return;
}

template <class generic>
void Vector<generic>::pop_back()
{
  if (m_size == 0)
  {
    throw( Exception(1, "You have tried to pop an empty vector.") );
  }
  
  m_size--;
  
  if ((m_size) <= (m_max_size * .25))
  {
    m_max_size /= 2;
    generic * temp = m_data;
    m_data = new generic[m_max_size];
    
    for( int i = 0; i < m_size; i++)
    {
      m_data[i] = temp[i];
    }
    
    delete [] temp;
  }
}

template <class generic>
Vector<generic>::~Vector()
{
  delete [] m_data;
}

template <class generic>
void Vector<generic>::clear()
{
  m_size = 0;
  m_max_size = 1;
  delete [] m_data;
  m_data = new generic[m_max_size];
}

template <class generic>
unsigned int Vector<generic>::size()
{
  return m_size;
}
    
template <class generic>
unsigned int Vector<generic>::max_size()
{
  return m_max_size;
}

#endif
