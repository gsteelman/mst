//////////////////////////////////////////////////////////////////////
/// @file library.h
/// @author Jeremy Davidson
/// @brief Templated search and sort routines
//////////////////////////////////////////////////////////////////////
/// @fn void swap(vector<Generic> & v, unsigned int pos1, unsigned int pos2)
/// @brief -- Swaps the items in pos1 and pos2 in vector v
/// @param vector<Generic> & v -- vector with entries to be swapped
/// @param unsigned int pos1 -- Index of first item to be swapped
/// @param unsigned int pos2 -- Index of second item to be swapped
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn unsigned int remove(vector<Generic> & v, Generic x)
/// @brief -- Searches for x in v and removes it.
/// @param vector<Generic> & v -- vector to be searched
/// @param Generic & x -- The data to look for
/// @return -- Position of x if found or UINT_MAX if not found
//////////////////////////////////////////////////////////////////////
/// @fn unsigned int search(vector<Generic> & v, Generic x)
/// @brief -- Does a sequential search through the vector v for x
/// @pre -- Data exists in v
/// @post -- If x is in v, its position is returned
/// @param vector<Generic> & v -- vector to be searched
/// @param Generic & x -- The data to look for
/// @return -- Position of x if found or UINT_MAX if not found
//////////////////////////////////////////////////////////////////////
/// @fn unsigned int binary_search(vector<Generic> & v, Generic x)
/// @brief -- Performs a binary search on v for x
/// @pre -- vector v must be sorted in smallest-to-largest order
/// @post -- If x is in v, its position is returned
/// @param vector<Generic> & v -- vector to be searched
/// @param Generic & x -- The data to look for
/// @return -- Position of x if found or UINT_MAX if not found
//////////////////////////////////////////////////////////////////////
/// @fn void bubble_sort(vector<Generic> & v)
/// @brief -- Bubble-sorts the data in v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn void selection_sort(vector<Generic> & v)
/// @brief -- Performs a selection sort on v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn void insertion_sort(vector<Generic> & v)
/// @brief -- Performs an insertion sort on v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn void quick_sort(vector<Generic> & v)
/// @brief -- Performs a quick sort on v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn void merge_sort(vector<Generic> & v)
/// @brief -- Performs a merge sort on v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn void quick_sort_r(vector<Generic> & v)
/// @brief -- Performs a quick sort on v using the recursive algorith
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn void merge_sort_r(vector<Generic> & v)
/// @brief -- Performs a merge sort on v using the recursive algorithm
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////

#ifndef LIBRARY_H
#define LIBRARY_H

//////////////////////////////////////////////////////////////////////
/// @note -- This was originally designed for a custom vector class.
///       However, because the class was essentially broken, and
///       couldn't function as well as the std::vector, it has
///       been modified for std::vector use.
///
///       Jeremy Davidson
//////////////////////////////////////////////////////////////////////

#include <vector>
using std::vector;

#include "exception.h"
#include "stack.h"

template <class Generic>
void swap(vector<Generic> & v, const unsigned int pos1, const unsigned int pos2);

template <class Generic>
unsigned int remove(vector<Generic> & v, const Generic x);

template <class Generic>
unsigned int search(const vector<Generic> & v, const Generic x);

template <class Generic>
unsigned int binary_search(const vector<Generic> & v, const Generic x);

template <class Generic>
void bubble_sort(vector<Generic> & v);

template <class Generic>
void selection_sort(vector<Generic> & v);

template <class Generic>
void insertion_sort(vector<Generic> & v);

template <class Generic>
void quick_sort(vector<Generic> & v);

template <class Generic>
void merge_sort(vector<Generic> & v);

// Recursive quicksort
template <class Generic>
void quick_sort_r(vector<Generic> & v);

// Recursive mergesort
template <class Generic>
void merge_sort_r(vector<Generic> & v);

#include "library.hpp"
#endif
