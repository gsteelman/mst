///////////////////////////////////////////////////////////////////////////////
/// @file library.h
/// @author Gary Steelman, CS153-B
/// @edited 4 Mar 08
/// @brief Library prototyping file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn search( Vector<generic> & v, generic x )
/// @brief Linearly searches the vector for the passed value
/// @pre A Vector exists, x is of same datatype as v
/// @post Returns the value of the index at which the passed value is found
/// @param v is the Vector to be searched
/// @param x is the value to search the Vector for
/// @return the index at which the passed value is found
/// @note Returns index of only the first instance of the passed value
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn binary_search( Vector<generic> & v, generic x )
/// @brief Binary searches the vector for the passed value
/// @pre A Vector exists, x is of same datatype as v, and the vector is sorted
///      from least to greatest already
/// @post Returns the value of the index at which the passed value is found
/// @param v is the Vector to be searched
/// @param x is the value to search the Vector for
/// @return the index at which the passed value is found
/// @note Returns index of only the first instance of the passed value
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bubble_sort( Vector<generic> & v )
/// @brief Sorts the passed Vector
/// @pre A Vector exists
/// @post Sorts the Vector from least to greatest
/// @param v is the Vector to be sorted
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn selection_sort( Vector<generic> & v )
/// @brief Sorts the passed Vector
/// @pre A Vector exists
/// @post Sorts the Vector from least to greatest
/// @param v is the Vector to be sorted
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn insertion_sort( Vector<generic> & v )
/// @brief Sorts the passed Vector
/// @pre A Vector exists
/// @post Sorts the Vector from least to greatest
/// @param v is the Vector to be sorted
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn quick_sort( Vector<generic> & v )
/// @brief Sorts the passed Vector
/// @pre A Vector exists
/// @post Sorts the Vector from least to greatest
/// @param v is the Vector to be sorted
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn merge_sort( Vector<generic> & v )
/// @brief Sorts the passed Vector
/// @pre A Vector exists
/// @post Sorts the Vector from least to greatest
/// @param v is the Vector to be sorted
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn swap( Vector<generic> &v, unsigned int swapFrom, unsigned int swapTo )
/// @brief Swaps the two values in the given positions in the vector
/// @pre A Vector exists
/// @post Swaps the values in the given positions in the vector
/// @param v is the vector
/// @param swapFrom is the position to move the value from
/// @param swapTo is the destination index for the swapFrom
/// @return None.
///////////////////////////////////////////////////////////////////////////////

#ifndef LIBRARY_H
#define LIBRARY_H

#include "exception.h"
#include "vector.h"
#include "stack.h"

template <class generic>
unsigned int search( Vector<generic> & v, generic x );

template <class generic>
unsigned int binary_search( Vector<generic> & v, generic x );

template <class generic>
void bubble_sort( Vector<generic> & v );

template <class generic>
void selection_sort( Vector<generic> & v );

template <class generic>
void insertion_sort( Vector<generic> & v );

template <class generic>
void quick_sort( Vector<generic> & v );

template <class generic>
void merge_sort( Vector<generic> & v );

template <class generic>
bool check_sorted( Vector<generic> &v );

template <class generic>
void swap( Vector<generic> &v, unsigned int x, unsigned int y );

#include "library.hpp"

#endif
