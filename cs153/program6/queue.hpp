///////////////////////////////////////////////////////////////////////////////
/// @file queue.hpp
/// @author Gary Steelman, CS153-B
/// @edited 27 Feb 08
/// @brief Header file for the Queue class
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Queue()
/// @brief Constructor for a Queue class
/// @pre None.
/// @post Instantiates a Queue class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Queue()
/// @brief Destructor for a Queue class
/// @pre A Queue class exists
/// @post Clears the memory for the Queue class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_front()
/// @brief Pops the front of the Queue off
/// @pre A Queue class exists
/// @post Removes the first element from the Queue
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_back( generic x )
/// @brief Pushes the passed parameter onto the back of the Queue
/// @pre x and the Queue it is being pushed onto are of the same datatype
/// @post The Queue now has the passed parameter behind every other node
/// @param x is the value to be pushed onto the back of the Queue
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn front()
/// @brief Returns the front value of the Queue
/// @pre A Queue class exists
/// @post Returns the front value of the Queue
/// @return The front value in the Queue
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn back()
/// @brief Returns the back value of the Queue
/// @pre A Queue class exists
/// @post Returns the back value of the Queue
/// @return The back value in the Queue
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size()
/// @brief Returns the current size of the Queue
/// @pre A Queue class exists
/// @post Returns the current size of the Queue
/// @return Returns the current size of the Queue
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear()
/// @brief Empties the Queue
/// @pre A Queue class exists
/// @post Empties the Queue
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty()
/// @brief Returns whether or not the Queue is empty
/// @pre A Queue class exists
/// @post Returns whether or not the Queue is empty
/// @return True if the Queue is empty, false if otherwise
///////////////////////////////////////////////////////////////////////////////

#ifndef QUEUE_HPP
#define QUEUE_HPP

template <class generic>
Queue<generic>::Queue()
{
  //Unnecessary since all relevant variables are instantiated via
  //The parent class
}

template <class generic>
Queue<generic>::~Queue()
{
  List<generic>::clear();
}

template <class generic>
bool Queue<generic>::empty()
{
  List<generic>::empty();
}

template <class generic>
unsigned int Queue<generic>::size()
{
  List<generic>::size();
}

template <class generic>
generic & Queue<generic>::front()
{
  List<generic>::front();
}

template <class generic>
generic & Queue<generic>::back()
{
  List<generic>::back();
}

template <class generic>
void Queue<generic>::push( generic x )
{
  List<generic>::push_back(x);
  
  return;
}

template <class generic>
void Queue<generic>::pop()
{
  List<generic>::pop_front();
  
  return;
}

#endif
