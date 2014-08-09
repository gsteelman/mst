//////////////////////////////////////////////////////////////////////
/// @file library.hpp
/// @author Jeremy Davidson
/// @brief Templated search and sort routines
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn void swap(vector<Generic> & v, unsigned int pos1, unsigned int pos2)
/// @brief -- Swaps the items in pos1 and pos2 in vector v
/// @param vector<Generic> & v -- vector with entries to be swapped
/// @param unsigned int pos1 -- Index of first item to be swapped
/// @param unsigned int pos2 -- Index of second item to be swapped
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void swap(vector<Generic> & v, const unsigned int pos1, const unsigned int pos2) {

  Generic temp;
  
  // Store data in temporary variable
  temp = v[pos1];
  
  // Move data from pos2 to pos1
  v[pos1] = v[pos2];
  
  // Move data from temp to pos2
  v[pos2] = temp;

}

//////////////////////////////////////////////////////////////////////
/// @fn unsigned int remove(vector<Generic> & v, Generic x)
/// @brief -- Searches for x in v and removes it.
/// @param vector<Generic> & v -- vector to be searched
/// @param Generic & x -- The data to look for
/// @return -- Position of x if found or UINT_MAX if not found
//////////////////////////////////////////////////////////////////////
template <class Generic>
unsigned int remove(vector<Generic> & v, const Generic x) {

  // First, look for the data.
  unsigned int pos = search(v, x);

  // If search() returned UINT_MAX, it means the search failed.
  if (pos != UINT_MAX) {

    // Bubble the item to the end of the vector
    for (unsigned int i = pos; i < v.size() - 1; i++) {

      // Do this by swapping the to-be-removed item with the item
      // just after it. 
      swap(v, i, i + 1);

    }

    // After that, pop the item off.
    v.pop_back();

  }

  // Even if we failed, return the position we got from search()
  return pos;

}

//////////////////////////////////////////////////////////////////////
/// @fn unsigned int search(vector<Generic> & v, Generic x)
/// @brief -- Does a sequential search through the vector v for x
/// @pre -- Data exists in v
/// @post -- If x is in v, its position is returned
/// @param vector<Generic> & v -- vector to be searched
/// @param Generic & x -- The data to look for
/// @return -- Position of x if found or UINT_MAX if not found
//////////////////////////////////////////////////////////////////////
template <class Generic>
unsigned int search(const vector<Generic> & v, const Generic x) {
  
  // Traverse entire vector
  for (unsigned int index = 0; index < v.size(); index++) {
  
    // If a match is found, return the index
    if (v[index] == x) {
    
      return index;
      
    }
    
  }
  
  // If no match was found, UINT_MAX is returned, because it's highly
  // unlikely the array size is UINT_MAX
  return UINT_MAX;

}

//////////////////////////////////////////////////////////////////////
/// @fn unsigned int binary_search(vector<Generic> & v, Generic x)
/// @brief -- Performs a binary search on v for x
/// @pre -- vector v must be sorted in smallest-to-largest order
/// @post -- If x is in v, its position is returned
/// @param vector<Generic> & v -- vector to be searched
/// @param Generic & x -- The data to look for
/// @return -- Position of x if found or UINT_MAX if not found
//////////////////////////////////////////////////////////////////////
template <class Generic>
unsigned int binary_search(const vector<Generic> & v, const Generic x) {

  unsigned int min = 0;
  unsigned int max = v.size() - 1;

  // Index begins at the midpoint of the vector
  unsigned int index = (min + max) / 2;
  
  do {
    
    // If a match is found, return index
    if (v[index] == x) {
    
      return index;
    
    // If the value is greater than what you're looking for, it's in the lower
    // half of the bounds, so change the upper bound to be one less than
    // the current index (it's obviously not what you're looking at, so it's
    // safe to go one farther)
    } else if (v[index] > x) {
    
      max = index - 1;
    
    // If it's not equal to, and not greater, it's less than what you're
    // looking for, so move min up
    } else {
    
      min = index + 1;
      
    }
    
    // Update index to be the new midpoint
    index = (min + max) / 2;
    
  // If max and min no longer define legal bounds
  // it means x is not in the vector, so break
  // out of the loop
  } while (min <= max);
  
  return UINT_MAX;

}

//////////////////////////////////////////////////////////////////////
/// @fn void bubble_sort(vector<Generic> & v)
/// @brief -- Bubble-sorts the data in v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void bubble_sort(vector<Generic> & v) {

  bool swapped = false;
  unsigned int unsorted = v.size();
  
  // Traverses the vector v.size() times
  for (int x = 0; x < v.size(); x++) {
  
    // New run, nothing's been swapped yet
    swapped = false;
    
    // Traverse the unsorted portion of the vector
    for (int index = 0; index < unsorted - 1; index++) {
    
      if (v[index] > v[index + 1]) {
      
        swap(v, index, index + 1);
        swapped = true;
        
      }
      
    }
    
    // If no swaps were made this traversal, the vector is sorted
    if (!swapped) {
    
      break;
      
    }
    
    // If it doesn't break, decrement unsorted so the internal
    // loop traverses one less item.
    unsorted--;
       
  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void selection_sort(vector<Generic> & v)
/// @brief -- Performs a selection sort on v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void selection_sort(vector<Generic> & v) {

  // Index of the smallest value in the vector
  unsigned int smallest = 0;
  
  // Index of the position currently being sorted
  unsigned int sorted = 0;
  
  // Traverse the vector v.size() times
  for (int x = 0; x < v.size(); x++) {
  
    // Start at the current index to be sorted and look through the end
    // of the vector
    for (int index = sorted; index < v.size(); index++) {
    
      // If the value at the current index is smaller than the value at the
      // stored "smallest", change the smallest to match index
      if (v[index] < v[smallest]) {
      
        smallest = index;
        
      }
      
    }
    
    // If smallest is farther down the array than the current
    // position being sorted for (or at the current position),
    // it's a valid swap
    if (sorted <= smallest) {
    
      swap(v, sorted, smallest);
    
    }
    
    // Increment sorted to match the new position
    sorted++;
    // Reset smallest to the beginning of the unsorted array
    smallest = sorted;
    
  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void insertion_sort(vector<Generic> & v)
/// @brief -- Performs an insertion sort on v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void insertion_sort(vector<Generic> & v) {

  // Start at position 1 in the vector, and traverse the entire vector once
  for (int index = 1; index < v.size(); index++) {
  
    // Start at the very beginning of the vector and traverse
    // up until index
    for (int left = 0; left < index; left++) {
    
      // If the value at index is smaller than the value to the left of it...
      // Then shift it over to that position and shove everything over to
      // the right
      if (v[index] < v[left]) {
      
        // Which is accomplished by repeatedly swapping the original value
        // with the one to the left of it, until it's at its destination
        for (int swap_index = index; swap_index > left; swap_index--) {
        
          swap(v, swap_index, swap_index - 1);
          
        }
        
      }
      
    }
    
  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void quick_sort(vector<Generic> & v)
/// @brief -- Performs a quick sort on v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void quick_sort(vector<Generic> & v) {

  // Index range storage
  Stack<int> first, last;
  
  // Big and small indexes for comparison
  unsigned int small, big;
  
  // Index of pivot item
  unsigned int pivot;
  
  // Initialize first/last stacks
  first.push(0);
  last.push(v.size());  // One above final index for size
  
  // Begin the loop
  do {
    
    // Pivot in the middle
    pivot = (last.top() + first.top()) / 2;
    
    // Move item at pivot to front of section
    swap(v, first.top(), pivot);
    
    // Initialize big/small to the beginning of the unsorted section
    big = first.top() + 1;
    small = big;
    
    // Sort section
    do {
    
      // Find the first index where the value is greater than the pivot
      // which is now stored in the beginning
      for (; big < last.top(); big++) {
      
        // If big made it all the way to the end... everything was smaller
        // so bring big back to the last element and swap
        if (big >= last.top()) {
        
          big = last.top() - 1;
          swap(v, first.top(), big);

          break;
                
        // Found one that's bigger than the first item
        // (or equal to, to prevent infinite loops)
        } else if (v[big] >= v[first.top()]) {
        
          break;
          
        }
      
      }

      // Find the first index after big that has a value less than the pivot
      // If swapped in the previous routine, nothing will happen
      for (small = big + 1; small <= last.top(); small++) {
      
        // If small made it all the way to the end (and big didn't)... there's nothing
        // smaller than the pivot to swap big with, so pull big back one index, because
        // that's guaranteed to be smaller than the pivot, then swap the pivot with it
        if (small >= last.top()) {
    
          // If big is the last index in the array, an earlier swap was
          // performed, and the following swap is unneeded. The swap
          // itself is erroneous and doesn't affect sorting speed much,
          // but skipping it under these conditions guarantees integrity
          if (!(big == last.top() - 1)) {
            
            big--;
            
            swap(v, first.top(), big);
            
          }
          
          break;
        
        // Found a point that should be below the pivot
        // so exchange it with the one that should be above it
        // and keep moving
        } else if (v[small] < v[first.top()]) {
        
          // Swap small and big
          swap(v, small, big);
          
          // Leave the loop
          break;
          
        }
        
      }
    // Keep swapping until small runs off the end of the defined array
    } while (small < last.top());
    
    // Update the stack:
    // If the pivot ended up at the beginning of the array,
    // the front merely needs to be moved to meet the pivot
    if (big == first.top() + 1) {
    
      first.pop();
      first.push(big);
    
    // If the pivot ended up at the end of the array, the
    // back merely needs to be shifted back to meet the pivot
    } else if (big == last.top() - 1) {
    
      last.pop();
      last.push(big);
    
    // Otherwise, both the front and back need to be updated
    // to define two new segments surrounding the pivot
    } else {
    
      // Store the old array edges
      unsigned int first_temp = first.top();
      unsigned int last_temp = last.top();
      
      // Clear the already sorted index
      first.pop();
      last.pop();
      
      // Restore the original front for the left half
      // and put the end at the pivot
      first.push(first_temp);
      last.push(big);
      
      // Make the front of the right half one beyond the pivot
      // and take the end from the temp variable
      first.push(big + 1);
      last.push(last_temp);
    
    }
    
    // Check the stack for fully sorted sections and remove them
    while ((!first.empty() && !last.empty()) && first.top() >= last.top() - 1) {
    
      first.pop();
      last.pop();
    
    }
  
  // Run until both stacks are empty, meaning it's all sorted
  } while (!first.empty() && !last.empty());

}

//////////////////////////////////////////////////////////////////////
/// @fn void merge_sort(vector<Generic> & v)
/// @brief -- Performs a merge sort on v
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void merge_sort(vector<Generic> & v) {

  Stack<unsigned int> merge_min, merge_max;
  Stack<unsigned int> sort_min, sort_max;
  
  // Initialize the stacks
  merge_min.push(0);  // Beginning of the array
  merge_max.push(v.size() - 1); // End of the array
  
  sort_min.push(0); // Beginning
  sort_max.push(merge_max.top() / 2); // Middle
  
  sort_min.push(sort_max.top() + 1);  // Middle
  sort_max.push(merge_max.top()); // End
  
  do {
  
    // If the top of the sort array can be split, split it
    if (!(sort_max.empty() || sort_min.empty()) &&  // Not empty to avoid exceptions
          sort_max.top() > sort_min.top())      {   // And splittable
    
      // Set the new merge values
      merge_min.push(sort_min.top());
      merge_max.push(sort_max.top());
      
      // Pop the old values
      // The first minimum value stays the same, so no need to pop and repush
      sort_max.pop();
      
      // New max at the midpoint of the old
      sort_max.push((merge_max.top() + merge_min.top()) / 2);
      
      // New min one above the new max and 
      sort_min.push(sort_max.top() + 1);
      sort_max.push(merge_max.top());
    
    // Can the segment be merged?
    } else if ((sort_max.empty() || sort_min.empty())  || // Empty is a valid condition and must be checked first
               (sort_max.top() < merge_min.top()))     {  // If it's all out of things to split in the merge range, the lists
                                                          // are set up and ready to be sorted
      vector<Generic> sorted;
      
      // Index of the left half
      unsigned int left_index = merge_min.top();
      unsigned int left_max = (merge_min.top() + merge_max.top()) / 2;
      
      // Index of the right half
      unsigned int right_index = left_max + 1;
      unsigned int right_max = merge_max.top();
    
      // Loop as many times as there are entries
      for (int x = merge_min.top(); x <= merge_max.top(); x++) {
    
        // If the left side is all used up, but the right isn't, push an entry
        // from the right side onto sorted
        if (left_index > left_max && right_index <= right_max) {
        
          sorted.push_back(v[right_index]);
          right_index++;
          
        // Otherwise, if the right side's all used up, but the left isn't
        // push an entry from the left side onto sorted
        } else if (right_index > right_max && left_index <= left_max) {
        
          sorted.push_back(v[left_index]);
          left_index++;
        
        // If both are still available, check to see which is smaller
        // Push the value from the smaller one onto sorted
        } else if (v[left_index] <= v[right_index]) {
        
          sorted.push_back(v[left_index]);
          left_index++;
          
        } else if (v[right_index] < v[left_index]) {
        
          sorted.push_back(v[right_index]);
          right_index++;
          
        }
      
      }
      
      // Replace the sorted values into v
      for (int x = merge_min.top(); x <= merge_max.top(); x++) {
      
        v[x] = sorted[x - merge_min.top()];
        
      }
      
      // Clean up the merge stacks
      merge_min.pop();
      merge_max.pop();
      
    // If the segment is size one, clean it up, which will enable either a merge
    // or another split next loop
    } else if (sort_max.top() == sort_min.top()) {
    
      while ((!sort_min.empty() && !sort_max.empty()) && (sort_min.top() == sort_max.top())) {
        
        sort_min.pop();
        sort_max.pop();
        
      }
    
    }
      
  } while (!merge_min.empty() && !merge_max.empty());

}

//////////////////////////////////////////////////////////////////////
/// @fn void quick_sort_r(vector<Generic> & v)
/// @brief -- Performs a quick sort on v using the recursive algorithm
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void quick_sort_r(vector<Generic> & v) {
  
  // Base case: No need to sort if the vector has 1 or less elements
  if (v.size() > 1) {
  
    vector<Generic> left;   // Anything less than the pivot value
    vector<Generic> middle; // Anything of the same value as the pivot
    vector<Generic> right;  // Anything greater than the pivot value
    
    // Chooses a pivot in the middle of the vector
    unsigned int pivot = v.size() / 2;
    
    // Sort the values into vectors below, above, and equal to the pivot
    for (unsigned int index = 0; index < v.size(); index++) {
    
      if (v[index] < v[pivot]) {
      
        left.push_back(v[index]);
        
      } else if (v[index] > v[pivot]) {
      
        right.push_back(v[index]);
        
      } else {
      
        middle.push_back(v[index]);
        
      }
      
    }
    
    // Recursively sort the values below and above the pivot
    quick_sort_r(left);
    quick_sort_r(right);
    
    // Empty the vector currently being worked on
    v.clear();
    
    // Replace the sorted lower-valued vector into v
    for (unsigned int x = 0; x < left.size(); x++) {
    
      v.push_back(left[x]);
      
    }
    
    // Replace the mid-valued vector into v
    for (unsigned int x = 0; x < middle.size(); x++) {
    
      v.push_back(middle[x]);
      
    }
    
    // Replace the upper-valued vector into v
    for (unsigned int x = 0; x < right.size(); x++) {
    
      v.push_back(right[x]);
      
    }
    
  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void merge_sort_r(vector<Generic> & v)
/// @brief -- Performs a merge sort on v using the recursive algorithm
/// @param vector<Generic> & v -- vector to be sorted
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void merge_sort_r(vector<Generic> & v) {

  // Base case: No need to sort if there's one or less items in the vector
  if (v.size() > 1) {
  
    vector<Generic> left; // Left half of the vector
    vector<Generic> right; // Right half of the vector
    
    // The midpoint of the vector
    unsigned int pivot = v.size() / 2;
    
    // Fill the left vector with the values below the pivot
    for (int x = 0; x < pivot; x++) {
    
      left.push_back(v[x]);
      
    }
    
    // Fill the right vector with the entries at and above the pivot
    for (int x = pivot; x < v.size(); x++) {
    
      right.push_back(v[x]);
      
    }
    
    // Split and sort the left and right values
    merge_sort_r(left);
    merge_sort_r(right);
    
    // Index of left and right vectors for comparison sorting
    // Create variables after previous level vectors are destroyed
    // so unused integers aren't recursively eating memory
    unsigned int left_index = 0;
    unsigned int right_index = 0;
    
    // Empty the vector in preparation to accept new values
    v.clear();
    
    // Run until both vectors have been placed back into v
    for (int x = 0; x < left.size() + right.size() - 1; x++) {
    
      // If the left vector is all used up, but the right isn't, push an entry
      // from the right vector onto v
      // Prevents the tests from calling for an entry that doesn't exist
      if (left_index >= left.size() - 1 && right_index < right.size() - 1) {
      
        v.push_back(right[right_index]);
        right_index++;
        
      // Otherwise, if the right vector's all used up, but the left isn't
      // push an entry from the left vector onto v
      } else if (right_index >= right.size() - 1 && left_index < left.size() - 1) {
      
        v.push_back(left[left_index]);
        left_index++;
      
      // If both are still available, check to see which is smaller
      // Push the value from the smaller one onto v
      } else if (left[left_index] <= right[right_index]) {
      
        v.push_back(left[left_index]);
        left_index++;
        
      } else if (right[right_index] < left[left_index]) {
      
        v.push_back(right[right_index]);
        right_index++;
        
      }
        
    }
    
  }

}
