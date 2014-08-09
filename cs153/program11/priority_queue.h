///////////////////////////////////////////////////////////////////////////////
/// @file priority_queue.h
/// @author Gary Steelman, CS153-B
/// @edited 14 Apr 08
/// @brief Priority queue prototype file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Priority_queue()
/// @brief Constructor for the Priority_queue class
/// @pre None.
/// @post Instantiates a Priority_queue
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Priority_queue()
/// @brief Destructor for the Priority_queue class
/// @pre A Priority_queue exists
/// @post Clears the memory related to and destroys the Priority_queue
/// @return None
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push( generic x )
/// @brief Pushes an item into the Priority_queue
/// @pre A Priority_queue exists
/// @post Pushes a new item into the Priority_queue
/// @param generic x is the data to be pushed onto the Priority_queue
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop()
/// @brief Pops the top item off of the Priority_queue
/// @pre A Priority_queue exists
/// @post Pops the top item off of the Priority_queue
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn top()
/// @brief Returns the top value of the Priority_queue
/// @pre A Priority_queue exists
/// @post Returns the top value of the Priority_queue
/// @return Returns the top value of the Priority_queue
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear()
/// @brief Clears the memory used by the Priority_queue and deletes it
/// @pre A Priority_queue exists
/// @post Clears the memory used by the Priority_queue and deletes it
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty()
/// @brief Returns whether or not the Priority_queue is empty
/// @pre A Priority_queue exists
/// @post Returns whether or not the Priority_queue is empty
/// @return true if the Priority_queue is empty, false if the Priority_queue 
///   is not empty
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size()
/// @brief Returns the number of nodes in teh Priority_queue
/// @pre A Priority_queue exists
/// @post Returns the number of nodes in teh Priority_queue
/// @return the number of nodes in teh Priority_queue
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn swap(Bsn<generic> * x, Bsn<generic> * y)
/// @brief Swaps the values at two nodes
/// @pre A Priority_queue with at least 2 nodes exists
/// @post Swaps the values of 2 different nodes
/// @param Bsn<generic> * x is one of the nodes to swap data in
/// @param Bsn<generic> * y is the other node to swap data in
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size()
/// @brief Returns the number of nodes in teh Priority_queue
/// @pre A Priority_queue exists
/// @post Returns the number of nodes in teh Priority_queue
/// @return the number of nodes in teh Priority_queue
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn relocate_m_pop()
/// @brief After the Priority_queue changes, updates the pop pointer location
/// @pre A Priority_queue exists
/// @post After the Priority_queue changes, updates the pop pointer location
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn relocate_m_push()
/// @brief After the Priority_queue changes, updates the push pointer location
/// @pre A Priority_queue exists
/// @post After the Priority_queue changes, updates the push pointer location
/// @return None.
///////////////////////////////////////////////////////////////////////////////

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "bsn.h"
#include "exception.h"

using namespace std;

template <class generic>
class Priority_queue
{
  public:
    Priority_queue();
    ~Priority_queue();
    void push( generic x );
    void pop();
    generic & top();
    void clear();
    bool empty();
    unsigned int size();
    
  protected:
    void swap(Bsn<generic> * x, Bsn<generic> * y);
    
    void relocate_m_pop();
    
    void relocate_m_push();
    
  private:
    //Pointer to the root of the tree
    Bsn<generic> * m_root;
    
    //Pointer to where to next push onto the tree at
    Bsn<generic> * m_push;
    
    //Pointer to where to use when popping the tree
    Bsn<generic> * m_pop;
    
    //The size of the tree
    unsigned int m_size;
};

#include "priority_queue.hpp"
#endif
