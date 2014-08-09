///////////////////////////////////////////////////////////////////////////////
/// @file node.h
/// @author Gary Steelman, CS153-B
/// @edited 20 Feb 08
/// @brief The Node class that will contain two pointers and data
///////////////////////////////////////////////////////////////////////////////

#ifndef NODE_H
#define NODE_H

template <class generic>

struct Node
{
  //Following pointer points to the next link in the list of nodes
  Node<generic> * forward;
  
  //Following pointer points to the previous link in the list of nodes
  Node<generic> * backward;
  
  //Contains the value for this node
  generic data;
};

#endif
