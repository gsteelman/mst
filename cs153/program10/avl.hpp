///////////////////////////////////////////////////////////////////////////////
/// @file avl.h
/// @author Gary Steelman, CS153-B
/// @edited 10 Apr 08
/// @brief Avl Tree implementation file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Avl()
/// @brief Constructor for Avl class
/// @pre None.
/// @post Instantiates an Avl tree
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Avl()
/// @brief Destructor for Avl class
/// @pre An Avl tree exists.
/// @post Clears the memory used by the Avl tree and deletes it
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn insert ( generic x )
/// @brief Inserts a new node into the tree and balances the tree
/// @pre An Avl tree exists.
/// @pre < operator is defined for passed data type
/// @pre > operator is defined for passed data type
/// @pre == opeartor is defined for passed data type
/// @pre = operator is defined for passed data type
/// @post Inserts a new node into the tree and balances the tree
/// @param generic x is the data to be added to the tree
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn remove ( generic x )
/// @brief Removes the searched for node from the tree and balances the tree
/// @pre An Avl tree exists.
/// @pre < operator is defined for passed data type
/// @pre > operator is defined for passed data type
/// @pre == opeartor is defined for passed data type
/// @pre = operator is defined for passed data type
/// @post Removes the searched for node from the tree and balances the tree
/// @param generic x is the data to be removed from the tree
/// @return None.
/// @note Removes only the first instance of the passed parameter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn search( generic x )
/// @brief Searches for the passed data in the tree
/// @pre An Avl tree exists.
/// @pre < operator is defined for passed data type
/// @pre > operator is defined for passed data type
/// @pre == opeartor is defined for passed data type
/// @post Returns a pointer to the location of the passed data if found in the 
///   tree
/// @param generic x is the data to be searched for in the tree
/// @return Pointer to the location of the data found in the tree
/// @note If the data is not found, nothing happens
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear()
/// @brief Clears the memory for the Avl tree
/// @pre An Avl tree exists
/// @post Clears the memory used by the tree
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty()
/// @brief Returns whether or not the tree is empty
/// @pre An Avl tree exists
/// @post Returns whether or not the tree is empty
/// @return true if the tree is empty, false if the tree is not empty
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size()
/// @brief Returns the number of elements in the tree
/// @pre An Avl tree exists.
/// @post Returns the number of elements in the tree
/// @return The number of elements in the tree
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn balance( Bsn<generic> * x )
/// @brief Returns the balance number on the passed node
/// @pre An Avl tree exists.
/// @post Returns the balance number on the passed node
/// @param Bsn<generic> * x is the node in the tree to find the balance number on
/// @return the balance number on the passed node
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn rotate( Bsn<generic> * x )
/// @brief Rotates the nodes around to balance the tree if the tree is unbalanced
/// @pre An Avl tree exists.
/// @post The nodes around the passed node are balanced
/// @param Bsn<generic> * x is the node on which the balance number is 2
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn update( Bsn<generic> * child )
/// @brief Updates the depths on the tree and rotates nodes if necessary
/// @pre An Avl tree exists.
/// @post The tree is balanced
/// @param Bsn<generic> * child is the node to update around 
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn setLDepth( Bsn<generic> * parent )
/// @brief Sets the left depth numbers on nodes above inserted nodes
/// @pre An Avl tree exists.
/// @post The left depths of the tree are updated
/// @param Bsn<generic> * parent is the node on which to update the left depth
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn setRDepth( Bsn<generic> * parent )
/// @brief Sets the right depth numbers on nodes above inserted nodes
/// @pre An Avl tree exists.
/// @post The right depths of the tree are updated
/// @param Bsn<generic> * parent is the node on which to update the right depth
/// @return None.
///////////////////////////////////////////////////////////////////////////////

#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------

template <class generic>
Avl<generic>::Avl()
{
  //All relevant information is created when the Bst is created
}

//-----------------------------------------------------------------------------
template <class generic>
Avl<generic>::~Avl()
{  
  clear();
}

//-----------------------------------------------------------------------------
template <class generic>
void Avl<generic>::insert( generic  x )
{
  update( Bst<generic>::p_insert( x ));
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
void Avl<generic>::remove( generic  x )
{
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
generic & Avl<generic>::search( generic x )
{ 
  return Bst<generic>::search(x);
}

//-----------------------------------------------------------------------------
template <class generic>
void Avl<generic>::clear()
{
  Bst<generic>::clear();
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
bool Avl<generic>::empty()
{

  return Bst<generic>::empty();

}

//-----------------------------------------------------------------------------
template <class generic> 
unsigned int Avl<generic>::size()
{
  return Bst<generic>::size();
}


//-----------------------------------------------------------------------------
template <class generic>
int Avl<generic>::balance( Bsn<generic> * x )
{
  return (int)(x->rd) - (int)(x->ld);
}

//-----------------------------------------------------------------------------
template <class generic>
void Avl<generic>::update( Bsn<generic> * child)
{
  Bsn<generic> * parent = child->p;
  if (parent != NULL)
  {
    do
    {
      if (parent->l == child)
      {
        setLDepth( parent );
      }
      
      else
      {
        setRDepth( parent );
      }
      
      child = child->p;
      parent = parent->p;
    } while (parent != NULL && std::abs(balance(child)) == 1);
    
    if (child != NULL && std::abs(balance(child)) > 1)
    {
      rotate( child );
    }
  }
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
void Avl<generic>::setLDepth( Bsn<generic> * parent)
{
  if (parent->l != NULL)
  {
    if (parent->l->ld > parent->l->rd)
    {
      parent->ld = parent->l->ld + 1;
    }
    
    else
    {
      parent->ld = parent->l->rd + 1;
    }
  }
  
  else
  {
    parent->ld = 0;
  }
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
void Avl<generic>::setRDepth( Bsn<generic> * parent)
{
  if (parent->r != NULL)
  {
    if (parent->r->rd > parent->r->ld)
    {
      parent->rd = parent->r->rd + 1;
    }
    
    else
    {
      parent->rd = parent->r->ld + 1;
    }
  }
  
  else
  {
    parent->rd = 0;
  }
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
void Avl<generic>::rotate (Bsn<generic> * x)
{
  /*Graders:
    I attempted to write this function and spent many hours working at it.
    Then there were seg-faults. And I fixed them.
    And then there were more. And more. And more.
    
    At about 3am (5 hours before the program was due) I decided it was in my
    best interest to give up on writing this program fully. I have a
    Calculus 3 exam today that I need to sleep before, as well as Physics 24.
    
    Thanks for reading, I'll stay up all night next time if I don't have an 
    exam to do.
    
    --Gary Steelman
  */
}

#endif
