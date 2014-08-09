#ifndef MERGE_HEAP_SORT_H
#define MERGE_HEAP_SORT_H

  const int ARRAYSIZE = 500;
  unsigned int count = 0;

  void drawArray(int array[], int arraySize);
  void adjustMaxHeap(int userArray[], unsigned int arraySize, int node);
  void buildHeap(int userArray[], unsigned int arraySize);
  
  unsigned int heap_sort(int userArray[], unsigned int arraySize);
  unsigned int merge_sort(int userArray[], unsigned int arraySize);
  
  bool isMaxHeap(int userArray[], int arraySize, int startRange, int endRange);
  bool checkMaxHeap(int userArray[], int arraySize, int node);
  bool assert_loop (int A[], int startCheck, int endCheck);

#include "merge_heap_sort.hpp"

#endif