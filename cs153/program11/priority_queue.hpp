///////////////////////////////////////////////////////////////////////////////
/// @file priority_queue.hpp
/// @author Gary Steelman, CS153-B
/// @edited 14 Apr 08
/// @brief Priority queue implementation file
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

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

using namespace std;

#include <iostream>

//-----------------------------------------------------------------------------
template <class generic>
Priority_queue<generic>::Priority_queue()
{
  m_root = NULL;
  m_push = NULL;
  m_pop = NULL;
  m_size = 0;
}

//-----------------------------------------------------------------------------
template <class generic>
Priority_queue<generic>::~Priority_queue()
{
  clear();
}

//-----------------------------------------------------------------------------
template <class generic>
void Priority_queue<generic>::push( generic x )
{
  //Case 1:
  if (m_root == NULL)
  {
    //Make a new node for the top of the heap
    m_root = new Bsn<generic>;
    m_root->data = new generic;

    //Fill in m_root's data
    *(m_root->data) = x;
    
    //Set m_root's children
    m_root->l = NULL;
    m_root->r = NULL;
    
    //Set m_root's parent
    m_root->p = NULL;
    
    //Set m_push and m_pop to where they need to start at
    m_push = m_root;
    m_pop = m_root;

    //Increment size
    m_size++;
  }
  
  //Case 2:
  else if (m_push->l == NULL && m_push->r == NULL)
  {
    //Make a new node for the insertion spot in the heap
    m_push->l = new Bsn<generic>;
    m_push->l->data = new generic;
    
    //Fill in the new data
    *(m_push->l->data) = x;
    
    //Set the children of the left node
    m_push->l->l = NULL;
    m_push->l->r = NULL;
    
    
    //Set the parent of the left node
    m_push->l->p = m_push;
    
    //Create a temp for searching through the heap to make sure it is a max heap
    Bsn<generic> * temp = m_push->l;
    
    //While the parent has a lower priority, swap the values of the current node
    //and it's parent as to maintain heap infrastructure
    while (temp->p != NULL && *(temp->p->data) < *(temp->data))
    {
      //Swap the values of temp and it's parent
      swap(temp, temp->p);
      
      //Now move temp up a spot such that we can test the next level up
      temp = temp->p;
    }
    
    m_pop = m_push;
    
    //Increment size
    m_size++;
  }
  
  //Case 3:
  else if (m_push->l != NULL && m_push->r == NULL)
  {

    //Make a new node for the insertion spot in the heap
    m_push->r = new Bsn<generic>;
    m_push->r->data = new generic;
    
    //Fill in the new data
    *(m_push->r->data) = x;
    
    //Set the children of the right node
    m_push->r->l = NULL;
    m_push->r->r = NULL;
    
    //Set the parent of the left node
    m_push->r->p = m_push;
    
    //Create a temp for searching through the heap to make sure it is a max heap
    Bsn<generic> * temp = m_push->r;

    //While the parent has a lower priority, swap the values of the current node
    //and it's parent as to maintain heap infrastructure
    while (temp->p != NULL && *(temp->p->data) < *(temp->data))
    {
      //Swap the values of temp and it's parent
      swap(temp, temp->p);
      
      //Now move temp up a spot such that we can test the next level up
      temp = temp->p;
    }
    
    m_pop = m_push;
    
    //And now we need to relocation push
    relocate_m_push();

    //Increment size
    m_size++;
  }
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
void Priority_queue<generic>::pop()
{
  //Case 1:
  if (m_root == NULL)
  {
    throw( Exception( 1, "1-Trying to pop from an empty queue." ));
  }
  
  //Case 2: [if m_root is the only remaining node]
  else if (m_pop->l == NULL && m_pop->r == NULL)
  {
    //Clear out m_root
    delete m_root->data;
    delete m_root;
    
    //Set m_root to null along with other pointers
    m_root = NULL;
    m_push = NULL;
    m_pop = NULL;
    
    //Decrement size
    m_size--;
  }
  
  //Case 3: [if both children exist]
  else if (m_pop->l != NULL & m_pop->r != NULL)
  {
    //swap the right child with the root's value
    swap( m_pop->r, m_root);
    
    //Kill off the right child
    delete m_pop->r->data;
    delete m_pop->r;
    m_pop->r = NULL;
    
    //Create a temp to move through the heap trickling down the new value to its spot
    Bsn<generic> * temp = m_root;

    //Trickle down the top node now until it is in its place
    //Swap it with whichever of its children is greater, if there is one
    
    do
    {
      //If left child exists and has higher priority
      if ( (temp->l != NULL && temp->r != NULL) && (*temp->l->data > *temp->r->data ) )
      {
        //Trickle left
        swap( temp, temp->l);
        
        //Now set temp to it's left child to continue trickling
        temp = temp->l;
      }

      //If the right child exists and has higher priority
      else if ( (temp->r != NULL && temp->l != NULL) && (*temp->r->data > * temp->l->data) )
      {
        //Trickle right
        swap (temp, temp->r);
        
        //Now set temp to it's right child to continue trickling
        temp = temp->r;
      }
      
      //If there is only the left child and it has higher priority
      else if ( (temp->r == NULL && temp->l != NULL) && (*temp->l->data > *temp->data) )
      {
        //Swap to the left and break out of the loop
        swap( temp, temp->l);
        break;
      }

    } while ( (temp->l != NULL && (*temp->data < *temp->l->data)) 
           || (temp->r != NULL && (*temp->data < *temp->r->data)) );
    
      
    m_push = m_pop;
    
    //Decrement size
    m_size--;
  }
  
  //Case 4: [if only the left child exists]
  else if (m_pop->l != NULL && m_pop->r == NULL)
  {

    //Swap the left child with the root's value
    swap ( m_pop->l, m_root);

    //Kill off the left child
    delete m_pop->l->data;
    delete m_pop->l;
    m_pop->l = NULL;
    
    
    //Create a temp to move thorugh the heap trickling down the new value to its spot
    Bsn<generic> * temp = m_root;
    
    //Trickle down the top node now until it is in its place
    //Swap it with whichever of its children is greater, if there is one
    do
    {
      //If left child exists and has higher priority
      if ( (temp->l != NULL && temp->r != NULL) && (*temp->l->data > *temp->r->data) )
      {
        //Trickle left
        swap( temp, temp->l);
        
        //Now set temp to it's left child to continue trickling
        temp = temp->l;
      }

      //If the right child exists and has higher priority
      else if ( (temp->r != NULL && temp->l != NULL) && (*temp->r->data > * temp->l->data) )
      {
        //Trickle right
        swap (temp, temp->r);
        
        //Now set temp to it's right child to continue trickling
        temp = temp->r;
      }
    } while ( (temp->l != NULL && (*temp->data < *temp->l->data)) 
           || (temp->r != NULL && (*temp->data < *temp->r->data)) );
          
    //And now we need to relocate pop
    relocate_m_pop();
    
    //Decrement size
    m_size--;
  }
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
generic & Priority_queue<generic>::top()
{
  if (m_root == NULL)
  {
    throw( Exception ( 2, "2-Trying to check the top of an empty queue." ));
  }
  
  else
  {
    return *(m_root->data);
  }
}

//-----------------------------------------------------------------------------
template <class generic>
void Priority_queue<generic>::clear()
{
  Bsn<generic> * temp1 = m_root;
  Bsn<generic> * temp2;

  if( m_root != NULL )
  {
    do
    {
      while( temp1->l != NULL || temp1->r != NULL )
      {
        if( temp1->l != NULL )
        {
            temp1 = temp1->l;
        }
        
        else
        {
            temp1 = temp1->r;
        }
      }
      
      if(temp1 != m_root) 
      {
        temp2 = temp1->p;

        if( temp2->l == temp1 )
        {
            temp2->l = NULL;
        }
        
        else
        {
            temp2->r = NULL;
        }

        delete temp1->data;
        delete temp1;
        temp1 = temp2;
      }
      
    } while( m_root->l != NULL || m_root->r != NULL );

  delete m_root->data;
  delete m_root;
  m_root = NULL;
  m_size = 0;
  }
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
bool Priority_queue<generic>::empty()
{
  if (m_root == NULL)
  {
    return true;
  }
  
  return false;
}

//-----------------------------------------------------------------------------
template <class generic>
unsigned int Priority_queue<generic>::size()
{
  return m_size;
}

//-----------------------------------------------------------------------------
template <class generic>
void Priority_queue<generic>::swap(Bsn<generic> * x, Bsn<generic> * y)
{
  generic * temp = x->data;
  x->data = y->data;
  y->data = temp;
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
void Priority_queue<generic>::relocate_m_pop()
{
  //Create an image of the m_pop to tell where we just came from
  Bsn<generic> * m_pop_trace = NULL;

  //m_push needs to circumspect NAO
  do
  {
    m_pop_trace = m_pop;
    if (m_pop->p != NULL)
    {
      m_pop = m_pop->p;
    }
  } while ((m_pop->p != NULL) && (m_pop->l == m_pop_trace));
  
  //We're at the top coming up from a just emptied row, need to move all the way
  //down to the right
  if (m_root->l != NULL && (m_root->l == m_pop_trace))
  {
    while (m_pop->r->r != NULL)
    {
      m_pop = m_pop->r;
    }
    
    return;
  }
  
  //However, if we're not at the top then continue as normal left one
  if (m_pop->l != NULL)
  {
    m_pop = m_pop->l;
  }
  
  if (m_pop == m_root && m_root->l == NULL && m_root->r == NULL)
  {
    m_push = m_root;
    return;
  }
  
  //Now move all the way down to the right
  while (m_pop->r->r != NULL)
  {
    m_pop = m_pop->r;
  }
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
void Priority_queue<generic>::relocate_m_push()
{
  //Create an image of the m_push to tell where we just came from
  Bsn<generic> * m_push_trace = m_push->r;

  //While we keep moving push up from the right if we can
  while ((m_push->p != NULL) && (m_push->r == m_push_trace))
  {
    m_push_trace = m_push;
    m_push = m_push->p;
  }
  
  //We're at the top coming up from a completely filled heap and need to move
  //All the way down tot he left
  if (m_root->r == m_push_trace)
  {
    while (m_push->l != NULL)
    {
      m_push = m_push->l;
    }
    
    //And bring m_pop along for the ride
    m_pop = m_push;
    
    return;
  }
  
  //However, if we're not at the top, then continue as normal
  m_push = m_push->r;
  
  //Now move all the way down to the left
  while (m_push->l != NULL)
  {
    m_push = m_push->l;
  }
  
  return;
}

#endif
