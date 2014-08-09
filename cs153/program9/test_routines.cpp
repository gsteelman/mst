//////////////////////////////////////////////////////////////////////
/// @file void test_list.cpp
/// @author Gary Steelman
/// @brief Tests for classes
//////////////////////////////////////////////////////////////////////

#include "Test_routines.h"
#include <iostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_routines);

void Test_routines::test_insert() {
  
  Bst<unsigned int> tree;
  
  cout << endl << "----------test_insert----------" << endl;
  
  cout << "Initialization test." << endl;
  CPPUNIT_ASSERT(tree.empty());
  CPPUNIT_ASSERT(tree.size() == 0);
  
  cout << "Inserting one item." << endl;
  tree.insert(rand() % INT_MAX);
  CPPUNIT_ASSERT(tree.size() == 1);
  
  cout << "Inserting 100,000 random items." << endl;
  for (unsigned int x = tree.size(); x < 100000; x++) {
  
    CPPUNIT_ASSERT(tree.size() == x);
    tree.insert(rand() % INT_MAX);
    
  }
  
  cout << "Clearing the tree." << endl;
  tree.clear();
  CPPUNIT_ASSERT(tree.empty());
  CPPUNIT_ASSERT(tree.size() == 0);

}

void Test_routines::test_remove() {
  
  Bst<unsigned int> tree;
  
  cout << endl << "----------test_remove----------" << endl;

  cout << "Initialization test." << endl;
  CPPUNIT_ASSERT(tree.empty());
  CPPUNIT_ASSERT(tree.size() == 0);
  
  cout << "Inserting 100 sequential items." << endl;
  for (unsigned int x = tree.size(); x < 100; x++) {
  
    CPPUNIT_ASSERT(tree.size() == x);
    tree.insert(x);
    
  }
  
  try {
  
    cout << "Removing 27." << endl;
    tree.remove(27);
    CPPUNIT_ASSERT(tree.size() == 99);
    
    cout << "Removing 42." << endl;
    tree.remove(42);
    CPPUNIT_ASSERT(tree.size() == 98);
  
    cout << "Removing 99." << endl;
    tree.remove(99);
    CPPUNIT_ASSERT(tree.size() == 97);
  
    cout << "Removing 0." << endl;
    tree.remove(0);
    CPPUNIT_ASSERT(tree.size() == 96);
    
    cout << "Removing 101." << endl;
    tree.remove(101);
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
  CPPUNIT_ASSERT(tree.size() == 96);
  
  cout << "Removing all." << endl;
  for (unsigned int x = 1; x < 27; x++) {
  
    tree.remove(x);
    CPPUNIT_ASSERT(tree.size() == 96 - x);
    
  }
  for (unsigned int x = 28; x < 42; x++) {
  
    tree.remove(x);
    CPPUNIT_ASSERT(tree.size() == 97 - x);
    
  }
  for (unsigned int x = 43; x < 99; x++) {
  
    tree.remove(x);
    CPPUNIT_ASSERT(tree.size() == 98 - x);
    
  }
  CPPUNIT_ASSERT(tree.size() == 0);
  CPPUNIT_ASSERT(tree.empty());
  
  cout << "Filling tree reverse-sequentially." << endl;
  for (unsigned int x = 100; x > 0; x--) {
  
    CPPUNIT_ASSERT(tree.size() == 100 - x);
    tree.insert(x);
    
  }
  
  cout << "Removing all." << endl;
  for (unsigned int x = 100; x > 75; x--) {
  
    CPPUNIT_ASSERT(tree.size() == x);
    tree.remove(x);
    
  }
  for (unsigned int x = 1; x <= 25; x++) {
  
    CPPUNIT_ASSERT(tree.size() == 76 - x);
    tree.remove(x);
  
  }
  for (unsigned int x = 50; x <= 75; x++) {
  
    CPPUNIT_ASSERT(tree.size() == 100 - x);
    tree.remove(x);
  
  }
  for (unsigned int x = 49; x > 25; x--) {
  
    CPPUNIT_ASSERT(tree.size() == x - 25);
    tree.remove(x);
  
  }
  
  CPPUNIT_ASSERT(tree.size() == 0);
  CPPUNIT_ASSERT(tree.empty());
  
  cout << "Refilling tree non-sequentially." << endl;
  cout << "No exceptions should be thrown during the ";
  cout << "following tests." << endl;
  
  try {
    
    tree.insert(32);
    tree.insert(15);
    tree.insert(60);
    tree.insert(10);
    tree.insert(27);
    tree.insert(44);
    tree.insert(71);
    tree.insert(3);
    tree.insert(13);
    tree.insert(18);
    tree.insert(29);
    tree.insert(37);
    tree.insert(51);
    tree.insert(67);
    tree.insert(79);
    
    cout << "Removing m_root (Test #2)." << endl;
    tree.remove(32);
    CPPUNIT_ASSERT(tree.search(15) == 15);
    CPPUNIT_ASSERT(tree.search(60) == 60);
    CPPUNIT_ASSERT(tree.search(10) == 10);
    CPPUNIT_ASSERT(tree.search(27) == 27);
    CPPUNIT_ASSERT(tree.search(44) == 44);
    CPPUNIT_ASSERT(tree.search(71) == 71);
    CPPUNIT_ASSERT(tree.search(3) == 3);
    CPPUNIT_ASSERT(tree.search(13) == 13);
    CPPUNIT_ASSERT(tree.search(18) == 18);
    CPPUNIT_ASSERT(tree.search(29) == 29);
    CPPUNIT_ASSERT(tree.search(37) == 37);
    CPPUNIT_ASSERT(tree.search(51) == 51);
    CPPUNIT_ASSERT(tree.search(67) == 67);
    CPPUNIT_ASSERT(tree.search(79) == 79);
    
    tree.clear();
    
    tree.insert(32);
    tree.insert(15);
    tree.insert(60);
    tree.insert(10);
    tree.insert(27);
    tree.insert(44);
    tree.insert(71);
    tree.insert(3);
    tree.insert(18);
    tree.insert(29);
    tree.insert(37);
    tree.insert(51);
    tree.insert(67);
    tree.insert(79);
    
    cout << "Removing first left node (Test #3)." << endl;
    tree.remove(15);
    CPPUNIT_ASSERT(tree.search(32) == 32);
    CPPUNIT_ASSERT(tree.search(60) == 60);
    CPPUNIT_ASSERT(tree.search(10) == 10);
    CPPUNIT_ASSERT(tree.search(27) == 27);
    CPPUNIT_ASSERT(tree.search(44) == 44);
    CPPUNIT_ASSERT(tree.search(71) == 71);
    CPPUNIT_ASSERT(tree.search(3) == 3);
    CPPUNIT_ASSERT(tree.search(18) == 18);
    CPPUNIT_ASSERT(tree.search(29) == 29);
    CPPUNIT_ASSERT(tree.search(37) == 37);
    CPPUNIT_ASSERT(tree.search(51) == 51);
    CPPUNIT_ASSERT(tree.search(67) == 67);
    CPPUNIT_ASSERT(tree.search(79) == 79);
    
    tree.clear();
    
    tree.insert(32);
    tree.insert(15);
    tree.insert(60);
    tree.insert(10);
    tree.insert(27);
    tree.insert(44);
    tree.insert(71);
    tree.insert(3);
    tree.insert(13);
    tree.insert(18);
    tree.insert(37);
    tree.insert(51);
    tree.insert(67);
    tree.insert(79);
    
    cout << "Removing m_root with obfuscated path (Test #4)." << endl;
    tree.remove(32);
    CPPUNIT_ASSERT(tree.search(15) == 15);
    CPPUNIT_ASSERT(tree.search(60) == 60);
    CPPUNIT_ASSERT(tree.search(10) == 10);
    CPPUNIT_ASSERT(tree.search(27) == 27);
    CPPUNIT_ASSERT(tree.search(44) == 44);
    CPPUNIT_ASSERT(tree.search(71) == 71);
    CPPUNIT_ASSERT(tree.search(3) == 3);
    CPPUNIT_ASSERT(tree.search(13) == 13);
    CPPUNIT_ASSERT(tree.search(18) == 18);
    CPPUNIT_ASSERT(tree.search(37) == 37);
    CPPUNIT_ASSERT(tree.search(51) == 51);
    CPPUNIT_ASSERT(tree.search(67) == 67);
    CPPUNIT_ASSERT(tree.search(79) == 79);
    
    tree.clear();
    
    tree.insert(32);
    tree.insert(15);
    tree.insert(60);
    tree.insert(10);
    tree.insert(27);
    tree.insert(71);
    tree.insert(3);
    tree.insert(13);
    tree.insert(18);
    tree.insert(29);
    tree.insert(67);
    tree.insert(79);
    
    cout << "Removing first right node with obfuscated path (Test #5)." << endl;
    tree.remove(60);
    CPPUNIT_ASSERT(tree.search(32) == 32);
    CPPUNIT_ASSERT(tree.search(15) == 15);
    CPPUNIT_ASSERT(tree.search(10) == 10);
    CPPUNIT_ASSERT(tree.search(27) == 27);
    CPPUNIT_ASSERT(tree.search(71) == 71);
    CPPUNIT_ASSERT(tree.search(3) == 3);
    CPPUNIT_ASSERT(tree.search(13) == 13);
    CPPUNIT_ASSERT(tree.search(18) == 18);
    CPPUNIT_ASSERT(tree.search(29) == 29);
    CPPUNIT_ASSERT(tree.search(67) == 67);
    CPPUNIT_ASSERT(tree.search(79) == 79);
    
    tree.clear();
    
    tree.insert(32);
    tree.insert(15);
    tree.insert(60);
    tree.insert(10);
    tree.insert(27);
    tree.insert(44);
    tree.insert(71);
    tree.insert(3);
    tree.insert(13);
    tree.insert(18);
    tree.insert(29);
    tree.insert(37);
    tree.insert(51);
    tree.insert(67);
    tree.insert(79);
    
    cout << "Removing bottom node (Test #6)." << endl;
    tree.remove(67);
    CPPUNIT_ASSERT(tree.search(32) == 32);
    CPPUNIT_ASSERT(tree.search(15) == 15);
    CPPUNIT_ASSERT(tree.search(60) == 60);
    CPPUNIT_ASSERT(tree.search(10) == 10);
    CPPUNIT_ASSERT(tree.search(27) == 27);
    CPPUNIT_ASSERT(tree.search(44) == 44);
    CPPUNIT_ASSERT(tree.search(71) == 71);
    CPPUNIT_ASSERT(tree.search(3) == 3);
    CPPUNIT_ASSERT(tree.search(13) == 13);
    CPPUNIT_ASSERT(tree.search(18) == 18);
    CPPUNIT_ASSERT(tree.search(29) == 29);
    CPPUNIT_ASSERT(tree.search(37) == 37);
    CPPUNIT_ASSERT(tree.search(51) == 51);
    CPPUNIT_ASSERT(tree.search(79) == 79);
    
    tree.clear();
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }

}

void Test_routines::test_search() {
  
  Bst<unsigned int> tree;
  
  cout << endl << "----------test_search----------" << endl;
  
  cout << "Inserting 100 sequential items." << endl;
  for (unsigned int x = tree.size(); x < 100; x++) {
  
    tree.insert(x);
    CPPUNIT_ASSERT(tree.search(x) == x);
    
  }
  
  cout << "Searching for random items within the tree." << endl;
  for (unsigned int x = 0; x < 10; x++) {
  
    unsigned int y = rand() % 100;
    CPPUNIT_ASSERT(tree.search(y) == y);
    
  }
  
  cout << "Searching for non-existent items." << endl;
  try {
  
    CPPUNIT_ASSERT(tree.search(1000) != 1000);
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }

}
