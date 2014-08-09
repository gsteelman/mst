//////////////////////////////////////////////////////////////////////
/// @file void test_routines.cpp
/// @author Gary Steelman, CS153-B
/// @brief Tests for classes
//////////////////////////////////////////////////////////////////////

#include "Test_routines.h"
#include <iostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_routines);

void Test_routines::test_push() {
  
  Priority_queue<int> tree;
  
  cout << endl << "----------test_push----------" << endl;
  
  cout << "Initialization test." << endl;
  CPPUNIT_ASSERT(tree.empty());
  CPPUNIT_ASSERT(tree.size() == 0);
  
  cout << "Pushing one item." << endl;
  tree.push(0);
  CPPUNIT_ASSERT(tree.size() == 1);
  
  cout <<  endl;
  
  cout << "Pushing 10 sequential items." << endl;
  for (int x = tree.size(); x < 10; x++) {
  
    CPPUNIT_ASSERT(tree.size() == x);
    tree.push(x);
    
  }
  
  cout << endl;
  
  try {
  
    cout << "Clearing the tree." << endl;
    tree.clear();
    CPPUNIT_ASSERT(tree.empty());
    CPPUNIT_ASSERT(tree.size() == 0);
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
}

void Test_routines::test_pop() {
  
  Priority_queue<int> tree;
  
  cout << endl << "----------test_pop----------" << endl;

  cout << "Initialization test." << endl;
  CPPUNIT_ASSERT(tree.empty());
  CPPUNIT_ASSERT(tree.size() == 0);
  
  cout << "Pushing 10 sequential items." << endl;
  for (int x = tree.size(); x < 10; x++) {
  
    CPPUNIT_ASSERT(tree.size() == x);
    tree.push(x);
    CPPUNIT_ASSERT(tree.top() == x);
    
  }
  
  cout << "Popping all." << endl;
  for (int x = tree.size(); x > 0; x--) {
  
    CPPUNIT_ASSERT(tree.top() == tree.size() - 1);
    tree.pop();
  
  }
  
  cout << "Filling tree reverse-sequentially." << endl;
  for (int x = 10; x > 0; x--) {
  
    CPPUNIT_ASSERT(tree.size() == 10 - x);
    tree.push(x);
    CPPUNIT_ASSERT(tree.top() == 10);
    
  }
  
  cout << "Popping all." << endl;
  for (int x = tree.size(); x > 0; x--) {
  
    CPPUNIT_ASSERT(tree.top() == tree.size());
    tree.pop();
  
  }
  
  tree.clear();

}
