///////////////////////////////////////////////////////////////////////////////
/// @file snode.h
/// @author Gary Steelman, CS153-B
/// @edited 13 Feb 08
/// @brief Snode class prototype file
///////////////////////////////////////////////////////////////////////////////

#ifndef SNODE_H
#define SNODE_H

using namespace std;

template <class generic>
struct Snode
{
  //Following pointer points to the next item in the list
  Snode<generic> * forward;
  
  //Following variable contains the value of this node in the list                          
  generic data; 
};

#endif
