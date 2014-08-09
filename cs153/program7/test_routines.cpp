//////////////////////////////////////////////////////////////////////
/// @file void test_list.cpp
/// @author Jeremy Davidson -- CS 153 Section 1B
/// @brief Tests for a list class
//////////////////////////////////////////////////////////////////////

#include "Test_routines.h"
#include <iostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_routines);

void Test_routines::test_search() {
  
  cout << endl << "----------test_search----------" << endl;
  
  Vector<int> v;
  
  cout << "Testing search: Filling the vector to 10,000 elements." << endl;
  for (int x = v.size(); x < 10000; x++) {

    v.push_back(x);
    CPPUNIT_ASSERT(search(v, x) == x);
    
  }

}

void Test_routines::test_binary_search() {
  
  cout << endl << "----------test_binary_search----------" << endl;
  
  Vector<int> v;
  
  cout << "Testing search: Filling the vector to 10,000 elements." << endl;
  for (int x = v.size(); x < 10000; x++) {

    v.push_back(x);
    CPPUNIT_ASSERT(binary_search(v, x) == x);
    
  }

}

void Test_routines::test_bubble_sort() {
  
  cout << endl << "----------test_bubble_sort----------" << endl;
  
  Vector<int> v;
  
  double start = 0;
  double length = 0;
  
  cout << "Filling the vector to 10,000 random elements." << endl;
  for (int x = v.size(); x < 10000; x++) {

    v.push_back(rand() % INT_MAX);
    
  }
  
  start = (double)clock() / CLOCKS_PER_SEC;
  
  bubble_sort(v);
  
  length = (double)clock() / CLOCKS_PER_SEC - start;
  
  cout << "bubble_sort took " << (int)(length * 1000) << "ms to complete" << endl;
  
  CPPUNIT_ASSERT(isSorted(v));

}

void Test_routines::test_selection_sort() {
  
  cout << endl << "----------test_selection_sort----------" << endl;
  
  Vector<int> v;
  
  double start = 0;
  double length = 0;
  
  cout << "Filling the vector to 10,000 random elements." << endl;
  for (int x = v.size(); x < 10000; x++) {

    v.push_back(rand() % INT_MAX);
    
  }
  
  start = (double)clock() / CLOCKS_PER_SEC;
  
  selection_sort(v);
  
  length = (double)clock() / CLOCKS_PER_SEC - start;
  
  cout << "selection_sort took " << (int)(length * 1000) << "ms to complete" << endl;
  
  CPPUNIT_ASSERT(isSorted(v));

}

void Test_routines::test_insertion_sort() {
  
  cout << endl << "----------test_insertion_sort----------" << endl;
  
  Vector<int> v;
  
  double start = 0;
  double length = 0;
  
  cout << "Filling the vector to 10,000 random elements." << endl;
  for (int x = v.size(); x < 10000; x++) {

    v.push_back(rand() % INT_MAX);
  }
  start = (double)clock() / CLOCKS_PER_SEC;
  
  try {
  
    insertion_sort(v);
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
  length = (double)clock() / CLOCKS_PER_SEC - start;
  
  cout << "insertion_sort took " << (int)(length * 1000) << "ms to complete" << endl;
  
  CPPUNIT_ASSERT(isSorted(v));
  
}

void Test_routines::test_quick_sort() {
  
  cout << endl << "----------test_quick_sort----------" << endl;
  
  Vector<int> v;
  
  double start = 0;
  double length = 0;
  
  cout << "Filling the vector to 10,000 random elements." << endl;
  for (int x = v.size(); x < 10000; x++) {

    v.push_back(rand() % INT_MAX);
    
  }
  
  start = (double)clock() / CLOCKS_PER_SEC;
  
  try {
  
    quick_sort(v);
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
  length = (double)clock() / CLOCKS_PER_SEC - start;
  
  cout << "quick_sort took " << (int)(length * 1000) << "ms to complete" << endl;
  
  CPPUNIT_ASSERT(isSorted(v));

}

void Test_routines::test_merge_sort() {
  
  cout << endl << "----------test_merge_sort----------" << endl;
  
  Vector<int> v;
  
  double start = 0;
  double length = 0;
  
  cout << "Filling the vector to 10,000 random elements." << endl;
  for (int x = v.size(); x < 10000; x++) {

    v.push_back(rand() % INT_MAX);
    
  }
  
  start = (double)clock() / CLOCKS_PER_SEC;
  
  try {
  
  merge_sort(v);
  
    } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
  length = (double)clock() / CLOCKS_PER_SEC - start;
  
  cout << "merge_sort took " << (int)(length * 1000) << "ms to complete" << endl;
  
  CPPUNIT_ASSERT(isSorted(v));

}

template <class generic>
bool isSorted(Vector<generic> & v) {

  for (int x = 0; x < v.size() - 1; x++) {
  
    if (v[x] > v[x + 1]) {
    
      cout << "Unsorted at index: " << x << endl;
      cout << "Failed items: " << v[x] << " & " << v[x + 1] << endl;
      return false;
      
    }
    
  }
  
  return true;

}
