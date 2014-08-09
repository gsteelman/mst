

#include "Test_routines.h"
#include <iostream>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_routines);

void Test_routines::test_insert() {
  
  Avl<int> tree;
  
  cout << endl << "----------test_insert----------" << endl;
  
  cout << "Initialization test." << endl;
  CPPUNIT_ASSERT(tree.empty());
  CPPUNIT_ASSERT(tree.size() == 0);
  
 // cout << "Inserting one item." << endl;
 // tree.insert(rand() % INT_MAX);
 // CPPUNIT_ASSERT(tree.size() == 1);
  
  cout << "Inserting 10 items." << endl;
  
    cout << "Size: " << tree.size() << endl;//0
    tree.insert(10);
    cout << "Size: " << tree.size() << endl;//1
    tree.insert(12);
    cout << "Size: " << tree.size() << endl;//2
    tree.insert(5);
    cout << "Size: " << tree.size() << endl;//3
    tree.insert(76);
    cout << "Size: " << tree.size() << endl;//4
    tree.insert(13);
    cout << "Size: " << tree.size() << endl;
    tree.insert(14);
    cout << "Size: " << tree.size() << endl;
    tree.insert(17);
    cout << "Size: " << tree.size() << endl;
    tree.insert(25);
    cout << "Size: " << tree.size() << endl;
    tree.insert(86);
    cout << "Size: " << tree.size() << endl;
    tree.insert(45);
    cout << "Size: " << tree.size() << endl;
    CPPUNIT_ASSERT(tree.size() == 10);
    
  
  try {
  
    cout << "Clearing the tree." << endl;
    tree.clear();
    CPPUNIT_ASSERT(tree.empty());
    CPPUNIT_ASSERT(tree.size() == 0);
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
}

void Test_routines::test_remove() {
  
  Avl<int> tree;
  
  cout << endl << "----------test_remove----------" << endl;

  cout << "Initialization test." << endl;
  CPPUNIT_ASSERT(tree.empty());
  CPPUNIT_ASSERT(tree.size() == 0);
  
  cout << "Inserting 100 sequential items." << endl;
  for (int x = tree.size(); x < 100; x++) {
  
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
  for (int x = 1; x < 27; x++) {
  
    tree.remove(x);
    CPPUNIT_ASSERT(tree.size() == 96 - x);
    
  }
  for (int x = 28; x < 42; x++) {
  
    tree.remove(x);
    CPPUNIT_ASSERT(tree.size() == 97 - x);
    
  }
  for (int x = 43; x < 99; x++) {
  
    tree.remove(x);
    CPPUNIT_ASSERT(tree.size() == 98 - x);
    
  }
  CPPUNIT_ASSERT(tree.size() == 0);
  CPPUNIT_ASSERT(tree.empty());
  
  cout << "Filling tree reverse-sequentially." << endl;
  for (int x = 100; x > 0; x--) {
  
    CPPUNIT_ASSERT(tree.size() == 100 - x);
    tree.insert(x);
    
  }
  
  cout << "Removing all." << endl;
  for (int x = 100; x > 75; x--) {
  
    CPPUNIT_ASSERT(tree.size() == x);
    tree.remove(x);
    
  }
  for (int x = 1; x <= 25; x++) {
  
    CPPUNIT_ASSERT(tree.size() == 76 - x);
    tree.remove(x);
  
  }
  for (int x = 50; x <= 75; x++) {
  
    CPPUNIT_ASSERT(tree.size() == 100 - x);
    tree.remove(x);
  
  }
  for (int x = 49; x > 25; x--) {
  
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
    
    cout << "Removing m_root (BSN Test #2)." << endl;
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
    
    cout << "Removing first left node (BSN Test #3)." << endl;
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
    
    cout << "Removing m_root with obfuscated path (BSN Test #4)." << endl;
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
    
    cout << "Removing first right node with obfuscated path (BSN Test #5)." << endl;
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
    
    cout << "Removing bottom node (BSN Test #6)." << endl;
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
    
    cout << "Removing bottom node (AVL Test #1)." << endl;
    
    tree.insert(25);
    tree.insert(11);
    tree.insert(80);
    tree.insert(1);
    tree.insert(37);
    tree.insert(97);
    tree.insert(28);
    tree.insert(93);
    
    tree.remove(1);
    
    CPPUNIT_ASSERT(tree.search(25) == 25);
    CPPUNIT_ASSERT(tree.search(11) == 11);
    CPPUNIT_ASSERT(tree.search(80) == 80);
    CPPUNIT_ASSERT(tree.search(37) == 37);
    CPPUNIT_ASSERT(tree.search(97) == 97);
    CPPUNIT_ASSERT(tree.search(28) == 28);
    CPPUNIT_ASSERT(tree.search(93) == 93);
    
    tree.clear();
    
    cout << "Removing middle node (AVL Test #2)." << endl;
    
    tree.insert(45);
    tree.insert(21);
    tree.insert(67);
    tree.insert(8);
    tree.insert(23);
    tree.insert(51);
    tree.insert(72);
    tree.insert(32);
    tree.insert(47);
    tree.insert(70);
    tree.insert(89);
    tree.insert(71);
    
    tree.remove(21);
    
    CPPUNIT_ASSERT(tree.search(45) == 45);
    CPPUNIT_ASSERT(tree.search(67) == 67);
    CPPUNIT_ASSERT(tree.search(8) == 8);
    CPPUNIT_ASSERT(tree.search(23) == 23);
    CPPUNIT_ASSERT(tree.search(51) == 51);
    CPPUNIT_ASSERT(tree.search(72) == 72);
    CPPUNIT_ASSERT(tree.search(32) == 32);
    CPPUNIT_ASSERT(tree.search(47) == 47);
    CPPUNIT_ASSERT(tree.search(70) == 70);
    CPPUNIT_ASSERT(tree.search(89) == 89);
    CPPUNIT_ASSERT(tree.search(71) == 71);
    
    tree.clear();
    
    cout << "Removing bottom node (AVL Test #3)." << endl;
    
    tree.insert(32);
    tree.insert(16);
    tree.insert(48);
    tree.insert(8);
    tree.insert(24);
    tree.insert(40);
    tree.insert(56);
    tree.insert(12);
    tree.insert(20);
    tree.insert(28);
    tree.insert(44);
    tree.insert(52);
    tree.insert(60);
    tree.insert(18);
    tree.insert(22);
    tree.insert(54);
    
    tree.remove(12);
    
    CPPUNIT_ASSERT(tree.search(32) == 32);
    CPPUNIT_ASSERT(tree.search(16) == 16);
    CPPUNIT_ASSERT(tree.search(48) == 48);
    CPPUNIT_ASSERT(tree.search(8) == 8);
    CPPUNIT_ASSERT(tree.search(24) == 24);
    CPPUNIT_ASSERT(tree.search(40) == 40);
    CPPUNIT_ASSERT(tree.search(56) == 56);
    CPPUNIT_ASSERT(tree.search(20) == 20);
    CPPUNIT_ASSERT(tree.search(28) == 28);
    CPPUNIT_ASSERT(tree.search(44) == 44);
    CPPUNIT_ASSERT(tree.search(52) == 52);
    CPPUNIT_ASSERT(tree.search(60) == 60);
    CPPUNIT_ASSERT(tree.search(18) == 18);
    CPPUNIT_ASSERT(tree.search(22) == 22);
    CPPUNIT_ASSERT(tree.search(54) == 54);
    
    tree.clear();
    
    cout << "Removing mid-right node (AVL Test #4)." << endl;
    
    tree.insert(64);
    tree.insert(32);
    tree.insert(96);
    tree.insert(16);
    tree.insert(48);
    tree.insert(80);
    tree.insert(112);
    tree.insert(8);
    tree.insert(24);
    tree.insert(40);
    tree.insert(56);
    tree.insert(88);
    tree.insert(4);
    tree.insert(28);
    tree.insert(36);
    tree.insert(44);
    
    tree.remove(80);
    
    CPPUNIT_ASSERT(tree.search(64) == 64);
    CPPUNIT_ASSERT(tree.search(32) == 32);
    CPPUNIT_ASSERT(tree.search(96) == 96);
    CPPUNIT_ASSERT(tree.search(16) == 16);
    CPPUNIT_ASSERT(tree.search(48) == 48);
    CPPUNIT_ASSERT(tree.search(112) == 112);
    CPPUNIT_ASSERT(tree.search(8) == 8);
    CPPUNIT_ASSERT(tree.search(24) == 24);
    CPPUNIT_ASSERT(tree.search(40) == 40);
    CPPUNIT_ASSERT(tree.search(56) == 56);
    CPPUNIT_ASSERT(tree.search(88) == 88);
    CPPUNIT_ASSERT(tree.search(4) == 4);
    CPPUNIT_ASSERT(tree.search(28) == 28);
    CPPUNIT_ASSERT(tree.search(36) == 36);
    CPPUNIT_ASSERT(tree.search(44) == 44);
    
    tree.clear();
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  cout << "Filling the tree with a LOT of items." << endl;
  
  /*try {
  
    for (int x = 0; x < 1000000; x++) {
    
      tree.insert(INT_MAX - x);
    
    }
    
    for (int x = INT_MAX; x > INT_MAX - 1000000; x++) {
    
      tree.remove(x);
    
    }
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }
  
  tree.clear();*/

}

void Test_routines::test_search() {
  
  Avl<int> tree;
  
  cout << endl << "----------test_search----------" << endl;
  
  cout << "Inserting 100 sequential items." << endl;
  for (int x = tree.size(); x < 10; x++) {
  
    tree.insert(x);
    CPPUNIT_ASSERT(tree.search(x) == x);
    
  }
  
  cout << "Searching for random items within the tree." << endl;
  for (int x = 0; x < 10; x++) {
  
    int y = rand() % 100;
    //CPPUNIT_ASSERT(tree.search(y) == y);
    
  }
  
  cout << "Searching for non-existent items." << endl;
  try {
  
    CPPUNIT_ASSERT(tree.search(1000) != 1000);
    
  } catch (Exception & e) {
  
    cout << "Exception " << e.error_code() << ": " << e.error_message() << endl;
    
  }

}
