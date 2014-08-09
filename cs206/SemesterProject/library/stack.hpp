//////////////////////////////////////////////////////////////////////
/// @file stack.h
/// @author Jeremy Davidson
/// @brief Templated stack storage class. 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn Stack()
/// @brief -- Initializes the Stack
/// @pre -- Create a stack, preferably with a data type selected
/// @post -- Your stack is initialized. What's more to say?
//////////////////////////////////////////////////////////////////////
template <class Generic>
Stack<Generic>::Stack() {

  // Does nothing. Default constructor initializes Slist data

}

//////////////////////////////////////////////////////////////////////
/// @fn ~Stack()
/// @brief -- Destructor... frees the memory used by the stack
/// @pre -- Automatic
/// @post -- Automatic
//////////////////////////////////////////////////////////////////////
template <class Generic>
Stack<Generic>::~Stack() {

  Slist<Generic>::clear();

}

//////////////////////////////////////////////////////////////////////
/// @fn void push(Generic x)
/// @brief -- Adds x to the first spot in the stack, shifts the pointers
///           so the chain-style stack is maintained
/// @post -- m_size incremented, and x stored in the stack
/// @param Generic x -- The item to be placed in the stack
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void Stack<Generic>::push(Generic x) {

  Slist<Generic>::push_front(x);

}

//////////////////////////////////////////////////////////////////////
/// @fn void pop()
/// @brief -- Grabs the item at the top of the stack and deletes it
/// @pre -- m_size > 0
/// @post -- m_size decrements by one
//////////////////////////////////////////////////////////////////////
template <class Generic>
void Stack<Generic>::pop() {

  Slist<Generic>::pop_front();

}

//////////////////////////////////////////////////////////////////////
/// @fn Generic & top()
/// @brief -- Returns the item at the top of the stack
/// @pre -- The stack isn't empty
/// @return -- Returns the item at the top of the stack
//////////////////////////////////////////////////////////////////////
template <class Generic>
Generic & Stack<Generic>::top() {

  return Slist<Generic>::front();

}

//////////////////////////////////////////////////////////////////////
/// @fn unsigned int size()
/// @brief -- Returns the number of elements in the stack
/// @pre -- Nothing
/// @post -- Nothing
/// @return -- Returns the number of elements in the stack
//////////////////////////////////////////////////////////////////////
template <class Generic>
unsigned int Stack<Generic>::size() {

  return Slist<Generic>::size();

}

//////////////////////////////////////////////////////////////////////
/// @fn bool empty()
/// @brief -- Returns whether the stack is empty or not
/// @return -- True/false for if the stack is empty
//////////////////////////////////////////////////////////////////////
template <class Generic>
bool Stack<Generic>::empty() {

  return Slist<Generic>::empty();

}
