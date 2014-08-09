///////////////////////////////////////////////////////////////////////////////
/// @file avl.h
/// @author Gary Steelman, CS153-B
/// @edited 10 Apr 08
/// @brief Avl Tree prototype file
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

#ifndef AVL_H
#define AVL_H
#include "bst.h"

template <class generic>
class Avl : private Bst<generic>
{
  public:
    Avl();
    ~Avl();
    void insert( generic x );
    void remove( generic x );
    generic & search( generic x );
    void clear();
    bool empty();
    unsigned int size();
    int balance( Bsn<generic> * x);
    void rotate (Bsn<generic> * x);
    void update( Bsn<generic> * child);
    void setLDepth( Bsn<generic> * parent);
    void setRDepth( Bsn<generic> * parent);
};

#include "avl.hpp"
#endif
