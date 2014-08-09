///////////////////////////////////////////////////////////////////////////////
/// @file exception.hpp
/// @author Gary Steelman, CS153-B
/// @edited 06 Feb 08
/// @brief Test functions for the vector class
///////////////////////////////////////////////////////////////////////////////

#ifndef TEST_VECTOR_CPP
#define TEST_VECTOR_CPP

#include "test_vector.h"
#include <iostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_vector);

void Test_vector::test_push_back() {

  Vector<int> b;
  int count = 1;
  
  cout << "Testing push_back: Constructor check." << endl;
  CPPUNIT_ASSERT(b.size() == 0);
  
  cout << "Testing push_back: Push one item into the vector." << endl;
  b.push_back(74);
  CPPUNIT_ASSERT(b[0] == 74);
  CPPUNIT_ASSERT(b.size() == 1);
  
  if (b.size() > count) {
  
    count *= 2;
    cout << "Testing push_back: max_size doubling." << endl;
    CPPUNIT_ASSERT(b.max_size() == count);
    
  }
  
  cout << "Testing push_back: Fill the vector to 100,000 elements." << endl;
  for (int x = b.size() + 1; x <= 100000; x++) {

    b.push_back(x);
    CPPUNIT_ASSERT(b[x - 1] == x);
    CPPUNIT_ASSERT(b.size() == x);
    if (b.size() == count) {
    
      count *= 2;
      CPPUNIT_ASSERT(b.max_size() == count);
      
    }
    
  }
  
  try {
  
    int a = -1;
    cout << "Testing operator[]: Negative entry." << endl;
    b[a];
    b[b.max_size() + 1];
    
  } catch (Exception & e) {
      
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }

}

void Test_vector::test_pop_back() {

  Vector<int> b;
  int count = 1;
  
  cout << endl << "Filling vector to 100,000 elements." << endl;
  for (int x = 0; x < 100000; x++) {
  
    b.push_back(x);
    if (b.size() > count) {
    
      count *= 2;
      CPPUNIT_ASSERT(b.max_size() == count);
      
    }
    
  }
  
  cout << "Testing pop_back: Removing one item." << endl;
  b.pop_back();
  CPPUNIT_ASSERT(b.size() == 99999);
  
  cout << "Testing pop_back: Removing all items." << endl;
  cout << "Testing pop_back: max_size halving." << endl;
  for (int x = b.size(); x > 0; x--) {
  
    b.pop_back();
    CPPUNIT_ASSERT(b.size() == x - 1);
    
    for (int i = 0; i < b.size() / 1000; i++) {
    
      CPPUNIT_ASSERT(b[i] == i);
      
    }
    if (b.size() == count / 4 || b.size() == 0) {
    
      count /= 2;
      CPPUNIT_ASSERT(b.max_size() == count);
      
    }
    
  }
  
  CPPUNIT_ASSERT(b.size() == 0);
  
  try {
  
    cout << "Testing pop_back: Removing nonexistent items." << endl;
    b.pop_back();
    CPPUNIT_ASSERT(b.size() == 0);
    
  } catch (Exception & e) {
      
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }

}

void Test_vector::test_clear() {
  
  Vector<int> b;
  
  cout << endl << "Testing push_back: Constructor check." << endl;
  CPPUNIT_ASSERT(b.size() == 0);
  
  cout << "Testing push_back: Fill the vector to 100,000 elements." << endl;
  for (int x = b.size() + 1; x <= 100000; x++) {

    b.push_back(x);
    CPPUNIT_ASSERT(b[x - 1] == x);
    CPPUNIT_ASSERT(b.size() == x);
    
  }
  
  cout << "Testing clear: Emptying the vector." << endl;
  b.clear();
  CPPUNIT_ASSERT(b.size() == 0);
  CPPUNIT_ASSERT(b.max_size() == 1);

}

#endif
