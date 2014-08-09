///////////////////////////////////////////////////////////////////////////////
/// @file bst.h
/// @author Gary Steelman, CS153-B
/// @edited 7 Apr 08
/// @brief Binary Search Tree implementation file
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

#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include "exception.h"

using namespace std;

//-----------------------------------------------------------------------------
template <class generic>
Bst<generic>::Bst()
{
  m_root = NULL;
  m_size = 0;
}

//-----------------------------------------------------------------------------
template <class generic>
Bst<generic>::~Bst()
{
  clear();
}

//-----------------------------------------------------------------------------
template <class generic>
void Bst<generic>::insert( generic x )
{
  p_insert(x);
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
void Bst<generic>::remove( generic x)
{
  p_remove(x);
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
generic & Bst<generic>::search( generic x )
{
  Bsn<generic> * temp = p_search(x);
  
  if (*(temp->data) != x)
  {
    throw Exception(1, "Trying to search for an item that does not exist in the tree.");
  }
  
  return *(temp->data);
}

//-----------------------------------------------------------------------------
template <class generic>
void Bst<generic>::clear()
{
  Bsn<generic> * temp1 = m_root;
  Bsn<generic> * temp2;
  
  if (temp1 != NULL)
  {
    do
    {
      while (temp1->l != NULL || temp1->r != NULL)
      {
        if (temp1->l != NULL)
        { 
          temp1 = temp1->l;
        }
        
        else
        {
          temp1 = temp1->r;
        }
      }
    
      temp2 = temp1->p;
      
      if (temp1 == temp2->l)
      {
        temp2->l = NULL;
      }
      
      else
      {
        temp2->r = NULL;
      }
      
      delete temp1->data;
      delete temp1;
      
      m_size--;
      
      temp1 = temp2;
      
    } while (m_root->l != NULL || m_root->r != NULL);
    
    delete m_root->data;
    delete m_root;
    m_root = NULL;
    m_size = 0;
  }
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
bool Bst<generic>::empty()
{
  if (m_root == NULL)
  {
    return true;
  }
  
  return false;
}

//-----------------------------------------------------------------------------
template <class generic>
unsigned int Bst<generic>::size()
{
  return m_size;
}

//-----------------------------------------------------------------------------
template <class generic>
Bsn<generic> * Bst<generic>::p_insert( generic x )
{ 
  //The following code DOES NOT handle duplicate entries into a tree
  //Therefore this tree is good for AVL tree balancing techniques
  
  Bsn<generic> * temp1 = NULL;
  Bsn<generic> * temp2 = new Bsn<generic>;
  
  if (m_root == NULL)
  {
    m_root = temp2;
    temp2->p = NULL;
  }
  
  else
  {
    temp1 = p_search(x);
    
    if (temp1->l == NULL && x < *(temp1->data))
    {
      temp1->l = temp2;
    }
    
    else
    {
      temp1->r = temp2;
    }
    
    temp2->p = temp1;
  }
  
  temp2->l = NULL;
  temp2->r = NULL;
  
  temp2->ld = 0;
  temp2->rd = 0;
  
  temp2->data = new generic;
  *(temp2->data) = x;
  
  m_size++;
  
  return temp2;
  
  /*
  //The following code DOES handle duplicate entries into a tree
  //DO NOT use it to create an AVL-compatible tree
  
  //Create a new node to work with
  Bsn<generic> * new_node = new Bsn<generic>;
  
  //Create a temp for finding where to insert the new node
  Bsn<generic> * temp = m_root;
  
  //Initialize the new node
  new_node->data = new generic;
  *new_node->data = x;
  new_node->r = NULL;
  new_node->l = NULL;
  new_node->ld = 0; //For AVL traversal
  new_node->rd = 0; //For AVL traversal
  
  //If the tree is empty, append the new node to the root
  if (empty())
  {
    //Point m_root to the new node and point the node back
    m_root = new_node;
    
    //Increment size by 1
    m_size++;
    
    return m_root;
  }
  
  //The tree is not empty and thus we must search for the spot to put the 
  //New node
  else
  { 
    //Infintely loop until we insert the item into the correct place
    do
    {
      //x < current node, it needs to move left
      if (x < *temp->data)
      {
        //No other node to the left
        if (temp->l == NULL)
        {
          //Set temp left to the new node
          temp->l = new_node;
          
          //Set the new node parent to temp
          new_node->p = temp;
          
          //Increment size
          m_size++;
          
          //Return the pointer to the new node
          return new_node;
        }
        
        //Other node to the left, keep it moving left
        else
        {
          temp = temp->l;
        }
        
      }
      
      //x >= current node, it needs to move right
      else
      {
        //No other node to the right
        if (temp->r == NULL)
        {
          //Set temp right to the new node
          temp->r = new_node;
          
          //Set the new node parent to temp
          new_node->p = temp;
          
          //Increment size
          m_size++;
          
          //Return the pointer to the new node
          return new_node;
        }
        
        //Other node to the right, keep it moving right
        else
        {
          temp = temp->r;
        }
      }
    } while (true);
  }*/
}

//-----------------------------------------------------------------------------
template <class generic>
Bsn<generic> * Bst<generic>::p_remove( generic x )
{
  Bsn<generic> * temp1 = p_search(x);
  Bsn<generic> * temp2 = NULL;
  
  if (*(temp1->data) == x)
  {
    temp2 = temp1;
    
    if (temp2->l != NULL)
    {
      temp2 = temp2->l;
      
      while (temp2->r != NULL)
      {
        temp2 = temp2->r;
      }
      
      swap(temp1, temp2);
    }
    
    temp2 = kill(temp2);
  }
  
  return temp2;
}

//-----------------------------------------------------------------------------
template <class generic>
Bsn<generic> * Bst<generic>::p_search( generic x )
{
  Bsn<generic> * temp = m_root;
  
  if (temp == NULL)
  {
    throw( Exception(1, "Trying to search for an item that does not exist in the tree."));
  }
  
  while ((temp->l != NULL && x < *(temp->data)) || temp->r != NULL && *(temp->data) < x)
  {
    if (temp->l != NULL && x < *(temp->data))
    {
      temp = temp->l;
    }
    
    else
    {
      temp = temp->r;
    }
  }
  
  return temp;
}

//-----------------------------------------------------------------------------
template <class generic>
void Bst<generic>::swap(Bsn<generic> *x, Bsn<generic> *y)
{
  generic * temp = x->data;
  x->data = y->data;
  y->data = temp;
  
  return;
}

//-----------------------------------------------------------------------------
template <class generic>
Bsn<generic> * Bst<generic>::kill( Bsn<generic> *x)
{
    Bsn<generic> * temp1 = x;
    Bsn<generic> * temp2;

    if( x == m_root )
    {
        if( x->r == NULL )
        {
            m_root = NULL;
        }
        else
        {
            m_root = m_root->r;
            m_root->p = NULL;
        }
    }
    else
    {
        temp1 = temp1->p;

        if( x->l != NULL || x->r != NULL )
        {
            if( x->l == NULL && x->r != NULL )
            {
				if( temp1->l == x )
				{
					temp1->l = x->r;
					temp1->l->p = temp1;
				}
				else
				{
					temp1->r = x->r;
					temp1->r->p = temp1;
				}
            }
            else if( x->l != NULL && x->r == NULL )
            {
				if( temp1->l == x )
				{
					temp1->l = x->l;
					temp1->l->p = temp1;
				}
				else
				{
					temp1->r = x->l;
					temp1->r->p = temp1;
				}
            }
        }
        else
        {
            if( temp1->l == x )
			{
				temp1->l = NULL;
			}
			else
			{
				temp1->r = NULL;
			}
        }
    }

	temp2 = x->p;
    delete x->data;
    delete x;
    m_size--;

	return temp2;
}

#endif
