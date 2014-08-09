//////////////////////////////////////////////////////////////////////
/// @file stack.h
/// @author Jeremy Davidson
/// @brief Templated stack storage class. 
//////////////////////////////////////////////////////////////////////
/// @class Stack
/// @brief Provides simple, templated storage for any datatype,
///        with standard push/pop functionality.
//////////////////////////////////////////////////////////////////////
/// @fn Stack()
/// @brief -- Initializes the Stack
/// @pre -- Create a stack, preferably with a data type selected
/// @post -- Your stack is initialized. What's more to say?
//////////////////////////////////////////////////////////////////////
/// @fn ~Stack()
/// @brief -- Destructor... frees the memory used by the stack
/// @pre -- Automatic
/// @post -- Automatic
//////////////////////////////////////////////////////////////////////
/// @fn void push(Generic x)
/// @brief -- Adds x to the first spot in the stack, shifts the pointers
///           so the chain-style stack is maintained
/// @post -- m_size incremented, and x stored in the stack
/// @param Generic x -- The item to be placed in the stack
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
/// @fn void pop()
/// @brief -- Grabs the item at the top of the stack and deletes it
/// @pre -- m_size > 0
/// @post -- m_size decrements by one
//////////////////////////////////////////////////////////////////////
/// @fn Generic & top()
/// @brief -- Returns the item at the top of the stack
/// @pre -- The stack isn't empty
/// @return -- Returns the item at the top of the stack
//////////////////////////////////////////////////////////////////////
/// @fn unsigned int size()
/// @brief -- Returns the number of elements in the stack
/// @pre -- Nothing
/// @post -- Nothing
/// @return -- Returns the number of elements in the stack
//////////////////////////////////////////////////////////////////////
/// @fn bool empty()
/// @brief -- Returns whether the stack is empty or not
/// @return -- True/false for if the stack is empty
//////////////////////////////////////////////////////////////////////

#ifndef STACK_H
#define STACK_H

#include "slist.h"

template <class Generic>
class Stack : private Slist<Generic> {

  public:

    Stack();
    ~Stack();

    void          push(Generic x);
    void          pop();

    Generic &     top();

    unsigned int  size();
    bool          empty();
  
};

#include "stack.hpp"
#endif
