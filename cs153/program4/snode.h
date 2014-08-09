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
  Snode<generic> * forward; ///The pointer of the node that points to the next 
                            ///item in the list
  generic data; ///Contains the actual value of the node
};

#endif
