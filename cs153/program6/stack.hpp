///////////////////////////////////////////////////////////////////////////////
/// @file stack.hpp
/// @author Gary Steelman, CS153-B
/// @edited 27 Feb 08
/// @brief Stack class header file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Stack()
/// @brief Instantiates a Stack
/// @pre None.
/// @post Starts a stack, using the Slist functionality
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Stack()
/// @brief destructor for the stack class
/// @pre A stack object exists
/// @post Clears the stack
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push( generic x)
/// @brief Pushes the passed value onto the top of the stack
/// @pre A Stack object exists
/// @post Pushes the passed value onto the top of the stack
/// @param x the value to be added to the stack
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop()
/// @brief Pops the top value off of the stack
/// @pre A Stack object exists
/// @post Pops the top vlaue off of the stack
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn top()
/// @brief Returns the top value on the stack
/// @pre A Stack object exists
/// @post Returns the top value on the stack
/// @return the top value on the stack
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size()
/// @brief Returns the current size of the stack
/// @pre A Stack object exists
/// @post Returns the current size of the stack
/// @return the current size of the stack
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty
/// @brief Returns whether or not the stack is empty
/// @pre A Stack object exists
/// @post Returns whether or not hte stack is empty
/// @return whether or not the stack is empty
///////////////////////////////////////////////////////////////////////////////

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template <class generic>
Stack<generic>::Stack()
{
  //Unnecessary since all relevant variables are instantiated via
  //The parent class
}

template <class generic>
Stack<generic>::~Stack()
{
  Slist<generic>::clear();
}

template <class generic>
void Stack<generic>::push( generic x )
{
  Slist<generic>::push_front(x);
  
  return;
}

template <class generic>
void Stack<generic>::pop()
{
  Slist<generic>::pop_front();
  
  return;
}

template <class generic>
generic & Stack<generic>::top()
{
  Slist<generic>::front();
}

template <class generic>
unsigned int Stack<generic>::size()
{
  Slist<generic>::size();
}

template <class generic>
bool Stack<generic>::empty()
{
  Slist<generic>::empty();
}
    
#endif
