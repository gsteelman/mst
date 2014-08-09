
#ifndef MAIN_CPP
#define MAIN_CPP

#include <ctime>
#include <iostream>
#include <assert>
#include "merge_heap_sort.h"

int main()
{
  int hBestCase[ARRAYSIZE]; //Won't need to change anything, so only one to pass
  int mBestCase[ARRAYSIZE];
  int hWorstCase[ARRAYSIZE];
  int mWorstCase[ARRAYSIZE];
  int hAvgCase[ARRAYSIZE];
  int mAvgCase[ARRAYSIZE];

  int numSteps;

  srand(time(NULL));

  //Worst case
  for (int i = 0; i < ARRAYSIZE; i++) {
      hWorstCase[i] = i;
      mBestCase[i] = i;
  }

  //Worst case
  for (int j = ARRAYSIZE - 1; j >= 0; j--) {
      hBestCase[(ARRAYSIZE - 1) - j] = j;
  }

  //Average case
  for (int w = 0; w < ARRAYSIZE; w++) {
      hAvgCase[w] = rand() % 50; //To seed average case with random values
  }

  for (int m = 0; m < ARRAYSIZE; m++) {
      mWorstCase[m] = hWorstCase[m];
  }

  for (int d = 0; d < ARRAYSIZE; d++) {
      mAvgCase[d] = hAvgCase[d];
  }

  //Now to sort
  count = 0;

  cout << "----------------------------------\n";
  numSteps = heap_sort(hBestCase, ARRAYSIZE);
  cout << "Heap sort best case: " << count << endl;
  count = 0;
  
  numSteps = heap_sort(hAvgCase, ARRAYSIZE);
  cout << "Heap sort average case: " << count << endl;
  count = 0;
  
  numSteps = heap_sort(hWorstCase, ARRAYSIZE);
  cout << "Heap sort worst case: " << count << endl;
  count = 0;
  
  cout << "----------------------------------\n";
  numSteps = merge_sort(mBestCase, ARRAYSIZE);
  cout << "Merge sort best case: " << numSteps << endl;

  numSteps = merge_sort(mAvgCase, ARRAYSIZE);
  cout << "Merge sort average case: " << numSteps << endl;

  numSteps = merge_sort(mWorstCase, ARRAYSIZE);
  cout << "Merge sort worst case: " << numSteps << endl;

  cout << "----------------------------------\n";

  //cin.get();

  return 0;
   
}

#endif