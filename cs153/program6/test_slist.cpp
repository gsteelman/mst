//////////////////////////////////////////////////////////////////////
/// @file void test_slist.cpp
/// @author Gary Steelman, CS153-B
/// @brief Tests for a slist class
//////////////////////////////////////////////////////////////////////

#include "test_slist.h"
#include <iostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_slist);

void Test_slist::test_push_front() {
  
  cout << endl << "----------test_push_front----------" << endl;

  Slist<int> b;
  
  cout << "Testing push_front: Constructor check." << endl;
  CPPUNIT_ASSERT(b.size() == 0);
  
  cout << "Testing push_front: Push one item into the slist." << endl;
  b.push_front(74);
  CPPUNIT_ASSERT(b.front() == 74);
  CPPUNIT_ASSERT(b.size() == 1);
  CPPUNIT_ASSERT(!b.empty());
  
  cout << "Testing push_front: Fill the slist to 100,000 elements." << endl;
  for (int x = b.size() + 1; x <= 100000; x++) {

    b.push_front(x);
    CPPUNIT_ASSERT(b.front() == x);
    CPPUNIT_ASSERT(b.size() == x);
    CPPUNIT_ASSERT(!b.empty());
    
  }

}

void Test_slist::test_pop_front() {
  
  cout << endl << "----------test_pop_front----------" << endl;

  Slist<int> b;
  
  cout << "Filling slist to 100,000 elements." << endl;
  for (int x = 0; x < 100000; x++) {
  
    b.push_front(x);
    
  }
  
  cout << "Testing pop_front: Removing one item." << endl;
  b.pop_front();
  CPPUNIT_ASSERT(b.size() == 99999);
  
  cout << "Testing pop_front: Removing all items." << endl;
  for (int x = b.size() - 1; x >= 0; x--) {
    CPPUNIT_ASSERT(b.front() == x);
    b.pop_front();
    CPPUNIT_ASSERT(b.size() == x);
        
  }
  
  CPPUNIT_ASSERT(b.size() == 0);
  
  try {
  
    cout << "Testing pop_front: Removing nonexistent items." << endl;
    b.pop_front();
    CPPUNIT_ASSERT(b.size() == 0);
    
  } catch (Exception & e) {
      
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
  try {
  
    cout << "Testing front: Calling front with no items in list." << endl;
    b.front();
    
  } catch (Exception & e) {
      
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }

}

void Test_slist::test_clear() {
  
  cout << endl << "----------test_clear----------" << endl;
  
  Slist<int> b;
  
  cout << "Testing push_front: Constructor check." << endl;
  CPPUNIT_ASSERT(b.size() == 0);
  
  cout << "Testing push_front: Fill the slist to 100,000 elements." << endl;
  for (int x = b.size() + 1; x <= 100000; x++) {

    b.push_front(x);
    CPPUNIT_ASSERT(b.front() == x);
    CPPUNIT_ASSERT(b.size() == x);
    CPPUNIT_ASSERT(!b.empty());
    
  }
  
  cout << "Testing clear: Emptying the slist." << endl;
  b.clear();
  CPPUNIT_ASSERT(b.size() == 0);

}

void Test_slist::test_remove() {
  
  cout << endl << "----------test_remove----------" << endl;
  
  Slist<int> b;
  int count = 0;
  
  cout << "Testing push_front: Constructor check." << endl;
  CPPUNIT_ASSERT(b.size() == 0);
  
  cout << "Testing push_front: Fill the slist to 100,000 elements." << endl;
  for (int x = b.size() + 1; x <= 100000; x++) {

    b.push_front(x);
    CPPUNIT_ASSERT(b.front() == x);
    CPPUNIT_ASSERT(b.size() == x);
    CPPUNIT_ASSERT(!b.empty());
    
  }
  
  cout << "Testing remove: Removing the first item in the list." << endl;
  b.remove(b.front());
  CPPUNIT_ASSERT(b.front() == 99999);
  
  try {
  
    cout << "Testing remove: Removing a nonexistent item." << endl;
    b.remove(b.size() + 1);
  
  } catch (Exception & e) {
      
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
  cout << "Testing remove: Removing four arbitrary entries (I promise)." << endl;
  b.remove(1000);
  b.remove(5000);
  b.remove(10000);
  b.remove(50000);
  
  try {
  
    cout << "Testing remove: Removing items until empty." << endl;
    
    while (!b.empty()) {
    
      b.remove(b.front());
      
    }
    
    CPPUNIT_ASSERT(b.empty());
    CPPUNIT_ASSERT(b.size() == 0);
    
  } catch (Exception & e) {
      
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
  
  
  try {
  
    cout << "Testing remove: Removing item from an empty list." << endl;
    b.remove(0);
  
  } catch (Exception & e) {
      
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }

}
