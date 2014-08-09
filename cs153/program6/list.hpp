///////////////////////////////////////////////////////////////////////////////
/// @file list.hpp
/// @author Gary Steelman, CS153-B
/// @edited 20 Feb 08
/// @brief list class implementation file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn List()
/// @brief Constructor for a List class
/// @pre None.
/// @post Instantiates a List class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~List()
/// @brief Destructor for a List class
/// @pre A List class exists
/// @post Clears the memory for the List class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_front( generic x )
/// @brief Pushes the passed parameter onto the front of the list
/// @pre x and the List it is being pushed onto are of the same datatype
/// @post The list now has the passed parameter in front of every other node
/// @param x is the value to be pushed onto the front of the List
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_front()
/// @brief Pops the front of the list off
/// @pre A List class exists
/// @post Removes the first element from the list
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_back( generic x )
/// @brief Pushes the passed parameter onto the back of the list
/// @pre x and the List it is being pushed onto are of the same datatype
/// @post The list now has the passed parameter behind every other node
/// @param x is the value to be pushed onto the back of the List
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_back()
/// @brief Pops the back of the list off
/// @pre A List class exists
/// @post Removes the last element from the list
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn remove( generic x )
/// @brief Removes the passed value from the list
/// @pre x and the List it is being pushed onto are of the same datatype
/// @post Removes the passed value from the list
/// @param x is the value to be removed from the list
/// @note This will only remove the first instance of the passed value from the
///   list
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn front()
/// @brief Returns the front value of the list
/// @pre A List class exists
/// @post Returns the front value of the list
/// @return The front value in the list
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn back()
/// @brief Returns the back value of the list
/// @pre A List class exists
/// @post Returns the back value of the list
/// @return The back value in the list
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size()
/// @brief Returns the current size of the list
/// @pre A List class exists
/// @post Returns the current size of the list
/// @return Returns the current size of the list
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear()
/// @brief Empties the list
/// @pre A List class exists
/// @post Empties the list
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty()
/// @brief Returns whether or not the List is empty
/// @pre A List class exists
/// @post Returns whether or not the List is empty
/// @return True if the list is empty, false if otherwise
///////////////////////////////////////////////////////////////////////////////

/*
Code-Description
1-Trying to pop from an empty list
2-Trying to remove from an empty list
3-Trying to access the front of an empty list
4-Trying to access the back of an empty list
*/

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "exception.h"

using namespace std;

template <class generic>
List<generic>::List()
{
  m_size = 0;
  
  //Point both head and tail to null
  m_front = NULL;
  m_back = NULL;
}

//-----------------------------------------------------------------------------

template <class generic>
List<generic>::~List()
{
  //Just calls the clear function
  clear();
}

//-----------------------------------------------------------------------------

template <class generic>
void List<generic>::push_front( generic x )
{
  //List is empty
  if (m_front == NULL)
  {
    //Point head to a new spot
    m_front = new Node<generic>;
    
    //Fill the spot
    m_front->data = x;
    
    //Point head forward to null
    m_front->forward = NULL;
    
    //Point head backward to null
    m_front->backward = NULL;
    
    //Point tail to head
    m_back = m_front;
    
    //Increment size
    m_size+=1;
  }
  
  //List is not empty
  else
  {
    //Create a temp
    Node<generic> * temp = m_front;
    
    //Point head to a new spot
    m_front = new Node<generic>;
    
    //Fill the spot
    m_front->data = x;
    
    //Point head to where temp was holding
    m_front->forward = temp;
    
    //Point head backward to null
    m_front->backward = NULL;
    
    //Point temp's spot back to head
    temp->backward = m_front;
    
    //Increment size
    m_size+=1;
  }
}

//-----------------------------------------------------------------------------

template <class generic>
void List<generic>::pop_front()
{
  //There are no nodes in the List
  if (m_front == NULL)
  {
    throw( Exception(1,"Trying to pop from an empty List."));
    throw( Exception(3,"Trying to access the front of an empty List."));
  }
  
  //There is only one node in the List
  else if (m_front->forward == NULL)
  {
    //Just delete the only node in the list if it's the only one
    delete m_front;
    
    //Then set head and tail to null
    m_front = NULL;
    m_back = NULL;
    
    //Decrement size
    m_size-=1;
  }
  
  //There is more than one node in the List
  else
  {
    //Create a temp
    Node<generic> * temp = m_front; 
    
    //Set head to one spot past itself
    m_front = m_front->forward;
    
    //Delete temp's placeheld spot
    delete temp;
    
    //Point head backward to null
    m_front->backward = NULL;
    
    //Decrement size
    m_size-=1;
  }
}

//-----------------------------------------------------------------------------
  
template <class generic>
void List<generic>::push_back( generic x )
{
 if (m_back == NULL)
  {
    //Point tail to a new spot
    m_back = new Node<generic>;
    
    //Fill the spot
    m_back->data = x;
    
    //Point tail backward to null
    m_back->backward = NULL;
    
    //Point head to tail
    m_front = m_back;
    
    //Point head forward to null
    m_front->forward = NULL;
    
    //Increment size
    m_size+=1;
  }
  
  //List is not empty
  else
  {
    //Create a temp
    Node<generic> * temp = m_back;
    
    //Point tail to a new spot
    m_back = new Node<generic>;
    
    //Fill the spot
    m_back->data = x;
    
    //Point temp forward to tail
    temp->forward = m_back;
    
    //Point tail backward to temp
    m_back->backward = temp;
    
    //Point tail's forward to null
    m_back->forward = NULL;
    
    //Increment size
    m_size+=1;
  }
}

//-----------------------------------------------------------------------------

template <class generic>
void List<generic>::pop_back()
{
  //There are no nodes in the List
  if (m_back == NULL)
  {
    throw( Exception(1,"Trying to pop from an empty List."));
    throw( Exception(4,"Trying to access the back of an empty List."));
  }
  
  //There is only one node in the List
  else if (m_back->backward == NULL)
  {
    //Just delete the only node in the list if it's the only one
    delete m_back;
    
    //Then set head and tail to null
    m_back = NULL;
    m_front = NULL;
    
    //Decrement size
    m_size-=1;
  }
  
  //There is more than one node in the List
  else
  {
    //Create a temp
    Node<generic> * temp = m_back;
    
    //Point tail back one past where it was
    m_back = m_back->backward;
    
    //Delete temp
    delete temp;
    
    //Set tail forward to null
    m_back->forward = NULL;
    
    //Decrement size
    m_size-=1;
  }
}

//-----------------------------------------------------------------------------

template <class generic>
void List<generic>::remove( generic x )
{
  //List is empty
  if (m_front == NULL)
  {
    throw( Exception(2,"Trying to remove from an empty List."));
  }
  
  //First and only elemnt in the list is the one we are looking for
  else if (m_front->forward == NULL && m_front->data == x)
  {
    delete m_front;
    m_back = NULL;
    m_front = NULL;
    
    //Decrement size
    m_size-=1;
  }
  
  //Not the only element in the list and it is the first one we are wanting
  else if (m_front->forward != NULL && m_front->data == x)
  {
    pop_front();
  }
  
  //Not the only element in the list, last one in the list is what we want
  else if (m_back->backward != NULL && m_back->data == x)
  {
    pop_back();
  }
  
  //If not any of the above
  else
  {  
    //Create a temp for indexing through the list
    Node<generic> * temp = m_front; 
    
    //Do a loop through to see if the value is even in the list, if not, throw
    //exception and quit out of function, otherwise, we now have the location
    //of where the value we are looking for is
    while (temp->forward != NULL && temp->forward->data != x)
    {
      temp = temp->forward;
    }
    
    //Check to see if the loop broke due to null
    if (temp->forward == NULL)
    {
      //throw( Exception(5,"Trying to remove value from a list when the value is not in the list."));
      //return;
    }
    
    //Else, the loop broke due to x existing
    else
    {
      //Create a new temp2 that is two spots past temp
      Node<generic> * temp2 = temp->forward->forward;
      
      //Delete the spot between the 2 temps
      delete temp->forward;
      
      //Join temp forward to temp2
      temp->forward = temp2;
      
      //Join temp2 backward to temp
      temp2->backward = temp;
      
      //Decrement size
      m_size-=1;
    }
  }
}

//-----------------------------------------------------------------------------

template <class generic>
generic & List<generic>::front()
{
  if (empty() == true)
  {
    throw (Exception(3,"Trying to access the front of an empty List."));
  }
  
  else
  {
    return m_front->data;
  }
}

//-----------------------------------------------------------------------------

template <class generic>
generic & List<generic>::back()
{
  if (empty() == true)
  {
    throw (Exception(4,"Trying to access the back of an empty List."));
  }

  else
  {
    return m_back->data;
  }
}

//-----------------------------------------------------------------------------

template <class generic>
unsigned int List<generic>::size()
{
  return m_size;
}

//-----------------------------------------------------------------------------

template <class generic>
void List<generic>::clear()
{
  while (size() > 0)
  {
    pop_front();
  }
}

//-----------------------------------------------------------------------------

template <class generic>
bool List<generic>::empty()
{
  if (m_front == NULL || m_back == NULL)
  {
    return true;
  }
  
  else
  {
    return false;
  }
}

#endif
