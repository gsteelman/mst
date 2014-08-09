///////////////////////////////////////////////////////////////////////////////
/// @file library.hpp
/// @author Gary Steelman, CS153-B
/// @edited 5 Mar 08
/// @brief Library definition file
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

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>

using namespace std;

template <class generic>
unsigned int search( Vector<generic> & v, generic x )
{
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i] == x)
    {
      return i;
    }
  }
  
  cout << "The searched for value was not found in the Vector." << endl;
  
  return UINT_MAX;
}

template <class generic>
unsigned int binary_search( Vector<generic> & v, generic x )
{
  //Whether or not the value has been found
  bool found = false;
  
  //Sets the upper bound for the Binary search
  unsigned int ubound = v.size();
  
  //Sets the lower bound for the Binary search
  unsigned int lbound = 0;
  
  while (found == false)
  {
    unsigned int startpos = (ubound + lbound) / 2;
    
    if (x > v[startpos])
    {
      lbound = startpos;
      found = false;
    }
    
    else if (x < v[startpos])
    {
      ubound = startpos;
      found = false;
    }
    
    else if (x == v[startpos])
    {
      return startpos;
      found = true;
    }
    
    else
    {
      cout << "The searched for value via Binary Search was not found" << endl;
      break;
    }
  }
  
  return UINT_MAX;
}

template <class generic>
void bubble_sort( Vector<generic> & v )
{
  for (int pass = 0; pass < v.size(); pass++)
  {
    for (int i = v.size(); i > 0; i--)
    {
      if (v[i] <= v[i - 1])
      {
        //Swap the two variables
        //Set a temp to hold the LHS value
        generic temp = v[i - 1];
        
        //Set LHS to RHS
        v[i - 1] = v[i];
        
        //Set RHS to what LHS was
        v[i] = temp;
      }
    }
    
    /*if (check_sorted(v) == true)
    {
      return;
    }*/
  }  

  return;
}

template <class generic>
void selection_sort( Vector<generic> & v )
{
  for (int pass = 0; pass < v.size(); pass++)
  {
    //Create the smallestIndex
    unsigned int smallestIndex = pass;
    
    //Searches for the smallest value other than the first number
    //sets smallestIndex = to that location
    for (int i = pass; i < v.size(); i++)
    {
      if (v[i] <= v[smallestIndex])
      {
        smallestIndex = i;
      }
    }
    
    //Swap the values of smallest and the first
    generic temp = v[pass];
    
    //First = smallest index
    v[pass] = v[smallestIndex];
    
    //smallest index = first
    v[smallestIndex] = temp;
   
  }

  return;
}

template <class generic>
void insertion_sort( Vector<generic> & v )
{
  for (int index = 1; index < v.size(); index++)
  {
    for (int LHSIndex = 0; LHSIndex < index; LHSIndex++)
    {
      if (v[LHSIndex] > v[index])
      {
      //swap v[index] all the way to vlhsindex]
        for (int j = index; j > LHSIndex; j--)
          swap(v, j, j-1);
      }
    }
  }
 
  return;  
}

template <class generic>
void quick_sort( Vector<generic> & v )
{

  unsigned int tempStart1 = 0;
  unsigned int tempStart2 = v.size();
  unsigned int start1 = 0;
  unsigned int start2 = 0;
  
  Stack<unsigned int> F;
  Stack<unsigned int> L;
  
  F.push(0);
  L.push(v.size());
  
  while (F.size() != 0 && L.size() != 0)
    {
    
      //Swaps the first and the middle 
      swap(v,tempStart1,(tempStart2 + tempStart1) / 2);
    
      for (;;)
      {
      
        start1 = tempStart1 + 1;
 
        while (start1 < tempStart2 && v[tempStart1] >= v[start1])
        {
          start1++;
        } 
        
        if (start1 == tempStart2)
        {
          break;
        }
        
        start2 = start1 + 1;
        
        while (start2 < tempStart2  && v[tempStart1] < v[start2])
        {
          start2++;
        }
        
        if (start2 == tempStart2)
        {
          break;
        }
        
        swap(v,start1,start2);
        
      }
      
    tempStart1 = F.top();
    tempStart2 = L.top();
    
    if (v[tempStart1] > v[start1 - 1])
    {
      swap(v, tempStart1, start1 - 1);
    }
    
    if (start1 < tempStart2)
    {
      
      F.pop();
      L.pop();
      
      F.push(tempStart1);
      L.push(start1 - 1);
      F.push(start1);
      L.push(tempStart2);
      
      tempStart1 = F.top();
      tempStart2 = L.top();
    }
    
    else
    {
      L.pop();
      
      L.push(start1 - 1);
    } 
    
    while (tempStart2 - tempStart1 <= 1)
    {
    
      F.pop();
      L.pop();
      
      if (F.size() == 0)
      {
        return;
      }
      
      tempStart2 = L.top();
      tempStart1 = F.top();
      
    }
    
    tempStart1 = F.top();
    tempStart2 = L.top();
   
  }
  
  return;
}

template <class generic>
void merge_sort( Vector<generic> & v )
{
  Stack<generic> Mn;
  Stack<generic> Mx;
  Stack<generic> Sn;
  Stack<generic> Sx;
  
  //For comparisons of broken down segments later on
  Vector<generic> tempVector;
  
  unsigned int min = 0;
  unsigned int halfway = 0;
  unsigned int max = 0;
  int leftPosition = 0;
  int leftMax = 0;
  int rightPosition = 0;
  int rightMax = 0;
  
  Sn.push(0);
  Sx.push(v.size() - 1);
  
  while(Sn.size() != 0)
  {
    //Push two elements onto the stacks for bounds
    Mn.push(Sn.top());
    Mx.push(Sx.top());
    
    //Since we pushed them onto the other stacks, remove them here
    Sn.pop();
    Sx.pop();
    
    //Now cut the vector in half and push new bounds onto the stacks
    halfway = (Mn.top() + Mx.top()) / 2;
    
    Sn.push(Mn.top());
    Sx.push(halfway);
    
    Sn.push(halfway + 1);
    Sx.push(Mx.top());
    
    //Make sure that the vector section we are wanting to check isn't of length
    //One, if it is, pop that bounds check off the vector
    
    while(Sn.size() != 0 && Sn.top() - Sx.top() == 0)
    {
      Sn.pop();
      Sx.pop();
    }
    
  }
  
  //Now that the Vector is broken down, build it back up while sorting
  
  while (Mn.size() != 0)
  {
    //Sets the index and the max number
    halfway = (Mn.top() + Mx.top()) / 2;
    
    leftPosition = Mn.top();
    leftMax = halfway;
    
    rightPosition = halfway + 1;
    rightMax = Mx.top();
    
    for (int i = 0; i <= (Mx.top() - Mn.top()); i++)
    {
      //If left < right, push left into temp vector, index++
      //If left == right, push left into temp vector, index++
      //If left is empty, dump all to the right
      
      if (leftMax < leftPosition)
      {
        for (int j = rightPosition; j <= rightMax; j++)
        {
          tempVector.push_back(v[rightPosition]);
          
          rightPosition++;
        }
        
        break;
      }
      
      else if (rightMax < rightPosition)
      {
        for (int j = leftPosition; j <= leftMax; j++)
        {
          tempVector.push_back(v[leftPosition]);
          
          leftPosition++;
        }
        
        break;
      }
      
      else if (v[leftPosition] <= v[rightPosition])
      {
        tempVector.push_back(v[leftPosition]);
        
        leftPosition++;
      }
      
      else if (v[rightPosition] < v[leftPosition])
      {
        tempVector.push_back(v[rightPosition]);
        
        rightPosition++;
      }
    }
    
    //Now put the swapped values back into v
    for (int i = Mn.top(); i <= Mx.top(); i++)
    {
      v[i] = tempVector[i - Mn.top()];
    }
    
    //Remove the top values from the stacks for indexing again
    Mn.pop();
    Mx.pop();
    
    //Clear the temp vector for use again
    tempVector.clear();
    
  }
  
  return;
}

template <class generic>
void swap( Vector<generic> &v, unsigned int swapFrom, unsigned int swapTo )
{
  generic temp = v[swapTo];
  v[swapTo] = v[swapFrom];
  v[swapFrom] = temp;
  return;
}


#endif
