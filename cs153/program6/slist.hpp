///////////////////////////////////////////////////////////////////////////////
/// @file slist.hpp
/// @author Gary Steelman, CS153-B
/// @edited 13 Feb 08
/// @brief Slist class implementation file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Slist
/// @brief the constructor for the Slist
/// @pre None.
/// @post creates an slist object
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Slist
/// @brief the destructor for the Slist
/// @pre None.
/// @post destroys an slist object
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_front
/// @brief an Slist object exists
/// @pre x is of the same datatype as the list
/// @post adds the passed x to the front of the slist
/// @param x the object to be added to the slist's front
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_front
/// @brief removes the first object in the slist
/// @pre An slist object of at least size 1 exists
/// @post removes the first object in the slist
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn remove
/// @brief removes the first instance of the passed value from the list
/// @pre an slist exists with the passed value in the list, x is of the same
///   datatype as the slist
/// @post removes the first instance of the passed value from the list
/// @param x the value to be removed from the slist
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn front
/// @brief returns the value of the first item in the slist
/// @pre an slist exists of at least size 1
/// @post returns the value of the first item in the slist
/// @return the value of the first item in the slist
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear
/// @brief clears out the list
/// @pre an slist object exists
/// @post deletes all values in the slist
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size
/// @brief returns the size of the list currently
/// @pre an slist exists
/// @post returns the size of the list currently
/// @return returns the size of the list currently
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty
/// @brief returns whether or not the list is empty
/// @pre an slist exists
/// @post returns whether or not the list is empty
/// @return whether or not the list is empty
///////////////////////////////////////////////////////////////////////////////

#ifndef SLIST_HPP
#define SLIST_HPP

#include <iostream>
#include "exception.h"

using namespace std;

template <class generic>
Slist<generic>::Slist() 
{
  m_size = 0;
  m_front = NULL;
}

template <class generic>
Slist<generic>::~Slist()
{
  clear();
}

template <class generic>
void Slist<generic>::push_front( generic x )
{
  //List is empty
  if (m_front == NULL)
  {
    m_front = new Snode<generic>;
    m_front->data = x;
    m_front->forward = NULL;
    m_size+=1;
  }
  
  //List is not empty
  else
  {
    Snode<generic> * temp = m_front;
    m_front = new Snode<generic>;
    m_front->data = x;
    m_front->forward = temp;
    m_size+=1;
  }

  return;
}

template <class generic>
void Slist<generic>::pop_front()
{
  //If the list is empty
  if (m_front == NULL)
  {
    throw( Exception(1, "Trying to pop from an empty list"));
  }
  
  //There is only one element in the list
  else if (m_front->forward == NULL)
  {
    delete m_front;
    m_front = NULL;
    m_size = 0;
  }
  
  //There is more than just 1 element in the list
  else 
  {
    Snode<generic> * temp = m_front;
    m_front = m_front->forward;
    delete temp;
    m_size-=1;
  }
  
  return;
}

template <class generic>
void Slist<generic>::remove( generic x )
{  
  //Empty list
  if (m_front == NULL)
  {
    throw( Exception(2, "Trying to remove from an empty list"));
  }
  
  //First element in list is the searched for element and the only element
  else if (m_front->forward == NULL && m_front->data == x) 
  {
    delete m_front;
    m_front = NULL;
    m_size = 0;
  }
  
  //First element in list, followed by something other than NULL
  else if (m_front->forward != NULL && m_front->data == x)
  {
    Snode<generic> * temp = m_front;
    m_front = m_front->forward;
    delete temp;
    m_size-=1;
  }
  
  //Not an empty list, not the first element in the list
  else 
  {
    //Create a temp for searching in the list
    Snode<generic> * temp = m_front;
    
    //Keep searching, moving along temp until the list ends up like:
    // ... TEMP, x, ...[not null]
    while (temp->forward->forward != NULL && temp->forward->data != x)
    {
      temp = temp->forward;
    }
    
    //x is the last element in the list
    if (temp->forward->forward == NULL && temp->forward->data == x)
    {
      delete m_front->forward;
      m_front->forward = NULL;
      m_size-=1;
    }
    
    //x is not in the list
    else if (temp->forward->forward == NULL && temp->forward->data != x)
    {
      cout << "The item was not in the list." << endl;
    }
    
    //x is not the last element in the list but is in the list
    else
    {
      Snode<generic> * temp2 = temp->forward->forward;
      delete temp->forward;
      temp->forward = temp2;
      
      m_size-=1;
    }
  }
  
  return;
}

template <class generic>
void Slist<generic>::clear()
{
  while (m_front != NULL) 
  {
    pop_front(); 
  }
  
  return;
}

template <class generic>
unsigned int Slist<generic>::size()
{
  return m_size;
}

template <class generic>
generic & Slist<generic>::front()
{
  if (m_front == NULL)
  {
    throw( Exception(3, "Trying to access the front of an empty list"));
  }
  else
  {
    return m_front->data;
  }
}

template <class generic>
bool Slist<generic>::empty()
{
  if (m_front == NULL)
  {
    return true;
  }
  
  else
  {
    return false;
  }
}


#endif
