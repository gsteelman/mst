///////////////////////////////////////////////////////////////////////////////
/// @file bsn.h
/// @author Gary Steelman, CS153-B
/// @edited 1 Apr 08
/// @brief Binary Search Tree node (container) file
///////////////////////////////////////////////////////////////////////////////

#ifndef BSN_H
#define BSN_H

using namespace std;

template <class generic>
struct Bsn
{
  Bsn * p;          // points to the parent
  Bsn * l;          // points to the left child
  Bsn * r;          // points to the right child
  generic * data;   // points to the data
  unsigned int ld;  // initialize this to 0 for now
  unsigned int rd;  // initialize this to 0 for now
};

#endif
