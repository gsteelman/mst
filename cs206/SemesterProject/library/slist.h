//////////////////////////////////////////////////////////////////////
/// @file slist.h
/// @author Jeremy Davidson
/// @brief Templated slist storage class. 
//////////////////////////////////////////////////////////////////////
/// @class Slist
/// @brief Provides simple, templated storage for any datatype,
///        with standard push/pop functionality.
//////////////////////////////////////////////////////////////////////
/// @fn Slist()
/// @brief -- Initializes the Slist
/// @pre -- Create a slist, preferably with a data type selected
/// @post -- Your slist is initialized. What's more to say?
//////////////////////////////////////////////////////////////////////
/// @fn ~Slist()
/// @brief -- Destructor... frees the memory the pointer is pointing at
/// @pre -- Automatic
/// @post -- Automatic
//////////////////////////////////////////////////////////////////////
/// @fn void push_front(Generic x)
/// @brief -- Adds x to the first spot in the slist, shifts the pointers
///           so the chain-style list is maintained
/// @post -- m_size incremented, and x stored in the slist
/// @param Generic x -- The item to be placed in the slist
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn void pop_front()
/// @brief -- Grabs the item at the front of the slist and deletes it
/// @pre -- m_size > 0
/// @post -- m_size decrements by one
//////////////////////////////////////////////////////////////////////
/// @fn void remove(Generic x)
/// @brief -- Searches for the first item in the list that matches x
///           and deletes it
/// @pre -- The list isn't empty, and x exists within the list
/// @post -- The item x is removed
/// @param Generic x -- The item to be removed from the list
//////////////////////////////////////////////////////////////////////
/// @fn Generic & front()
/// @brief -- Returns the item at the front of the list
/// @pre -- The list isn't empty
/// @return -- Returns the item at the front of the list
//////////////////////////////////////////////////////////////////////
/// @fn void clear()
/// @brief -- Empties all the data in the array and resets it to size 1
/// @pre -- None
/// @post -- All the data is gone
//////////////////////////////////////////////////////////////////////
/// @fn unsigned int size()
/// @brief -- Returns the number of elements in the slist
/// @pre -- Nothing
/// @post -- Nothing
/// @return -- Returns the number of elements in the slist
//////////////////////////////////////////////////////////////////////
/// @fn bool empty()
/// @brief -- Returns whether the list is empty or not
/// @return -- True/false for if the list is empty
//////////////////////////////////////////////////////////////////////

#ifndef SLIST_H
#define SLIST_H

#include "exception.h"
#include "snode.h"

template <class Generic>
class Slist {

  public:
  
    Slist();
    ~Slist();

    void          push_front(Generic x);
    void          pop_front();
    void          remove(Generic x);
    
    Generic &     front();

    void          clear();
    unsigned int  size();
    bool          empty();
    
  private:
  
    // Fairly simple: Stores how many objects are in the slist
    unsigned int m_size;
    
    Snode<Generic> * m_front;
    
};

#include "slist.hpp"
#endif
