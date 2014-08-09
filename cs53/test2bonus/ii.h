//pre : n is the size of the passed array v[], elements in v[] have been initialized
//post: findMin returns the smallest element of v[]
#ifndef ii_h
#define ii_h

#include <iostream>

using namespace std;

struct userType {
	int numberType;
	char characterType;
};

template < typename T >
T findMin(T v[], const int n)
{
  T min = 0;
  for (int i=0; i < n; i++)
  {
    if(v[i] < min)
    {
      min = v[i];
    }
  }
  return min;
}

#endif
