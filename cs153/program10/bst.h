///////////////////////////////////////////////////////////////////////////////
/// @file bst.h
/// @author Gary Steelman, CS153-B
/// @edited 7 Apr 08
/// @brief Binary Search Tree prototype file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Bst()
/// @brief Constructor for the Binary Search Tree
/// @pre None.
/// @post Creates a new Binary Search Treem, initializes the root node to NULL
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Bst()
/// @brief Destructor for the Binary Search Tree
/// @pre A Binary Search Tree exists
/// @post Clears the memory used by the tree
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn insert( generic x )
/// @brief Calls p_insert
/// @pre A Binary Search Tree exists
/// @post Returns a pointer to where the added node is located
/// @param generic x is the data to be added into the tree
/// @return Pointer to where the added node is located
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn remove ( generic x )
/// @brief Calls p_remove
/// @pre A Binary Searach Tree exists
/// @post Returns a pointer to the parent of the removed node
/// @param generic x is the data to be removed from the tree
/// @return Pointer to the parent of the removed node
/// @note Removes only the first instance of the passed parameter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn generic & search( generic x )
/// @brief Calls p_search
/// @pre A Binary Search Tree exists
/// @post Returns a pointer to the location of the passed data if found in the 
///   tree
/// @param generic x is the data to be searched for in the tree
/// @return Pointer to the location of the data found in the tree
/// @note If the data is not found, nothing happens
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear()
/// @brief Clears the memory for the Binary Search Tree
/// @pre A Binary Search Tree exists
/// @post Clears the memory used by the tree
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty()
/// @brief Returns whether or not the tree is empty
/// @pre A Binary Searach Tree exists
/// @post Returns whether or not the tree is empty
/// @return true if the tree is empty, false if the tree is not empty
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size()
/// @brief Returns the number of elements in the tree
/// @pre A Binary Searach Tree exists
/// @post Returns the number of elements in the tree
/// @return The number of elements in the tree
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn p_insert( generic x )
/// @brief Inserts a the passed parameter into the tree
/// @pre A Binary Search Tree exists
/// @pre < operator is defined for passed data type
/// @pre > operator is defined for passed data type
/// @pre == opeartor is defined for passed data type
/// @pre = operator is defined for passed data type
/// @post Inserts the passed parameter into the tree
/// @param generic x is the data to be added into the tree
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn p_remove ( generic x )
/// @brief Removes the passed data from the tree
/// @pre A Binary Searach Tree exists
/// @pre < operator is defined for passed data type
/// @pre > operator is defined for passed data type
/// @pre == opeartor is defined for passed data type
/// @pre = operator is defined for passed data type
/// @post Removes the passed data from the tree
/// @param generic x is the data to be removed from the tree
/// @return None.
/// @note Removes only the first instance of the passed parameter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn p_search( generic x )
/// @brief Searches for the passed data in the tree
/// @pre A Binary Search Tree exists
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
/// @fn kill(Bsn<generic * x)
/// @brief Kills a node off of the tree
/// @pre A Binary Search Tree with at least one element exists
/// @post Deletes the specified node from the tree
/// @param Bsn<generic> * x is a pointer to the location of the node to remove
///   from the tree
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn swap(Bsn<generic> * x, Bsn<generic> * y)
/// @brief Swaps the values at two nodes
/// @pre A Binary Search Tree with at least 2 nodes exists
/// @post Swaps the values of 2 different nodes
/// @param Bsn<generic> * x is one of the nodes to swap data in
/// @param Bsn<generic> * y is the other node to swap data in
/// @return None.
///////////////////////////////////////////////////////////////////////////////

#ifndef BST_H
#define BST_H
#include "bsn.h"
#include "exception.h"

using namespace std;

template <class generic>
class Bst
{
  public:
    Bst();
    ~Bst();
    void insert( generic x );
    void remove( generic x );
    generic & search( generic x );
    void clear();
    bool empty();
    unsigned int size();
    
  protected:
    Bsn<generic> * m_root;
    
    Bsn<generic> * kill(Bsn<generic> * x);

    void swap(Bsn<generic> * x, Bsn<generic> * y);
    
    // returns a pointer to the new node
    Bsn<generic> * p_insert( generic x );

    // returns a pointer to the parent of the deleted node
    Bsn<generic> * p_remove( generic x );

    // returns a pointer to where x is found
    Bsn<generic> * p_search( generic x );
    
  private:
    // the number of elements in the tree
    unsigned int m_size;
};

#include "bst.hpp"
#endif
