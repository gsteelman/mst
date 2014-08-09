#ifndef MERGE_HEAP_SORT_HPP
#define MERGE_HEAP_SORT_HPP

void drawArray(int array[], int arraySize)
{
  cout << "[ ";

  for (int f = 0; f < arraySize; f++) {
      cout << array[f] << " ";
  }

  cout << "]\n";
}

unsigned int heap_sort(int userArray[], unsigned int arraySize)
{
  //First turn the array into a workable heap
  buildHeap(userArray, arraySize);

  //Now, go through and swap the largest and smallest value,
  //then generate a max heap again, but this time of size - 1!

  for (int p = (arraySize - 1); p >= 1; p--) {

    //A[1..k] is a max-heap, A[k + 1..size] is sorted , and A[1] <= A[k + 1]
    assert(isMaxHeap(userArray, arraySize, 0, (p - 1)) &&
           assert_loop(userArray, p, (arraySize - 1) &&
           userArray[0] <= userArray[p]);

    //Swap the first and last value
    int tempHold = userArray[p];
   
    userArray[p] = userArray[0];
    userArray[0] = tempHold;

    adjustMaxHeap(userArray, p, 0);

    assert(isMaxHeap(userArray, arraySize, 0, (p - 2)) &&
           assert_loop(userArray, (p - 1), (arraySize - 1) &&
           userArray[0] <= userArray[p - 1]);

  }
  
  return arraySize;
}

void adjustMaxHeap(int userArray[], unsigned int arraySize, int node)
{
  int large = (2 * node);
  int tempCount = 0;

  //If the child would be outside the bounds of the array, nothing to be done
  if (large >= arraySize) {
      return;
  }

  //If the right child is larger than the left, set the large to reflect this
  if (large + 1 < arraySize) {
          count++;

      if ((large + 1) < arraySize && userArray[large + 1] > userArray[large]) {
          large++;
      }

      //Now see if the parent should be swapped with the larger child
      count++;

      if (large < arraySize && userArray[node] < userArray[large]) {
          int tempHold;

          tempHold = userArray[node];
          userArray[node] = userArray[large];
          userArray[large] = tempHold;

          //If so, repeat this process to reflect the new position of the parent
          adjustMaxHeap(userArray, arraySize, large);
      }
  }

  //To test that the function worked properly
  assert(testMaxHeap(userArray, arraySize, node));
}

void buildHeap(int userArray[], unsigned int arraySize)
{
  for (int q = ((arraySize - 1) / 2); q >= 0; q--) {
      assert(isMaxHeap(userArray, arraySize, q, (arraySize - 1)));
      adjustMaxHeap(userArray, arraySize, q);
      assert(isMaxHeap(userArray, arraySize, (q - 1), (arraySize - 1)));
  }
  return;
}

unsigned int merge_sort(int userArray[], unsigned int arraySize)
{

  unsigned int numSteps = 0;

  // Base case: No need to sort if there's one or less items in the array
  if (arraySize > 1) {

    int left[ARRAYSIZE / 2]; // Left half of the array
    int right[ARRAYSIZE / 2]; // Right half of the array
   
    // The midpoint of the array
    unsigned int pivot = arraySize / 2;
   
    // Fill the left array with the values below the pivot
    for (int x = 0; x < pivot; x++) {  
      left[x] = userArray[x];
    }
   
    // Fill the right array with the entries at and above the pivot
    for (int z = pivot; z < arraySize; z++) {
      right[z] = userArray[x];
    }
   
    // Split and sort the left and right values
    numSteps += merge_sort(left, pivot);
    numSteps += merge_sort(right, pivot);
   
    // Index of left and right array for comparison sorting
    // Create variables after previous level array are destroyed
    // so unused integers aren't recursively eating memory
    unsigned int left_index = 0;
    unsigned int right_index = 0;
   
    // Empty the array in preparation to accept new values
   
    for (int i = 0; i < arraySize; i++) {
      userArray[i] = NULL;
    }
   
    // Run until both arrays have been placed back into userArray
    for (int f = 0; f < (pivot * 2) - 1; f++) {
      //Invariant
      assert(assert_loop (userArray, 0, (x - 1)));
     
      // If the left array is all used up, but the right isn't, put
      // from the right array onto userArray
      // Prevents the tests from calling for an entry that doesn't exist
      if (left_index >= pivot - 1 && right_index < pivot - 1) {
        userArray[x] = right[right_index];
       
      // Otherwise, if the right array's all used up, but the left isn't
      // push an entry from the left array onto userArray
      } else if (right_index >= pivot - 1 && left_index < pivot - 1) {
        userArray[f] = left[left_index];

      // If both are still available, check to see which is smaller
      // Push the value from the smaller one onto userArray
      } else if (left[left_index] <= right[right_index]) {
        numSteps++;
     
        userArray[f] = left[left_index];
        left_index++;
       
      } else if (right[right_index] < left[left_index]) {
        numSteps++;
     
        userArray[f] = right[right_index];
        right_index++;
      }
     
      //Invariant
      assert(assert_loop (userArray, 0, f));  
    }
  }
  
  return numSteps;
}

bool assert_loop (int A[], int startCheck, int endCheck)
{
  //Check each entry the function is asked to
  for (int i = startCheck; i < endCheck; i++) {
    if (A[i] > A[i + 1]) {
      //If an error is found, return false
      return false;
    }
  }

  //If all is well, return true
  return true;
}

bool isMaxHeap(int userArray[], int arraySize, int startRange, int endRange)
{
  for (int y = endRange; y >= startRange; y--) {
      //If the left child is bigger or there is a right child
      //and the right child is bigger, then this isn't a max heap
      if (userArray[y] < userArray[2 * y] ||
          ((2 * y + 1 <= arraySize) && userArray[y] < userArray[2 * y + 1])) {

          return false;
      }
  }

  return true;
}

bool checkMaxHeap(int userArray[], int arraySize, int node)
{
  //If either child is bigger, return false.
  if (node * 2 < arraySize && userArray[node] < userArray[node * 2]) {
      return false;
      
  } else if (node * 2 + 1 < arraySize && userArray[node] < userArray[node * 2 + 1]) {
      return false;
  }

  return true;
}

#endif