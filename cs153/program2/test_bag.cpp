///////////////////////////////////////////////////////////////////////////////
/// @file test_bag.cpp
/// @author Gary Steelman, CS153-B
/// @edited 29 Jan 08
/// @brief Implementation file for the tests to run on the Bag class
///////////////////////////////////////////////////////////////////////////////

#include "test_bag.h"
#include "selectionsort.h"

CPPUNIT_TEST_SUITE_REGISTRATION( test_bag );

void test_bag::test_push_back()
{
  Bag<int> b;
  
  cout << endl << "test_push_back: Constructor check" << endl;
  CPPUNIT_ASSERT( b.size() == 0 );
  
  cout << "test_push_back: Push one item into the bag" << endl;
  b.push_back( 3 );
  CPPUNIT_ASSERT( b[0] == 3 );
  CPPUNIT_ASSERT( b.size() == 1 );
  
  cout << "test_push_back: Push multiple items into the bag" << endl;
  
  for( int i = b.size(); i < b.max_size(); i++ )
  {
    b.push_back( i );
    CPPUNIT_ASSERT( b[i] == i );
    CPPUNIT_ASSERT( b.size() == i+1 );
  }
  
  return;
}

void test_bag::test_pop_back()
{
  Bag<int> b;
  
  cout << endl << "test_pop_back: Constructor check" <<  endl;
  CPPUNIT_ASSERT( b.size() == 0 );
  
  b.push_back( 3 );
  b.push_back( 4 );
  
  cout << "test_pop_back: Pull one item off the bag" << endl;
  b.pop_back();
  CPPUNIT_ASSERT( b[1] == NULL );
  CPPUNIT_ASSERT( b[0] == 3 );
  
  return;
}

void test_bag::test_search()
{
  Bag<int> b;
  
  cout << endl << "test_search: Constructor check" << endl;
  CPPUNIT_ASSERT( b.size() == 0);
  
  cout << "test_search: Searching for character 3" << endl;
  b.push_back( 3 ); //0
  b.push_back( 4 ); //1
  b.push_back( 5 ); //2
  CPPUNIT_ASSERT (b.search(5) == 2);
  
  return;
}

void test_bag::test_sort()
{
  Bag<int> b;
  
  int k = 20;
  
  cout << endl << "test_sort: Constructor check" << endl;
  CPPUNIT_ASSERT( b.size() == 0);
  
  for (int i = 0; i < b.max_size(); i++)
  {
    b[i] = k;
    k--;
  }
  
  b[7] = 35;
  
  for (int i = 0; i < b.max_size(); i++)
  {
    cout << "0:" << b[i] << ", ";
  }
  
  cout << endl;
  
  cout << "test_sort: Sorting the data within..." << endl;
  b.sort();
  
  for (int i = 0; i < b.max_size(); i++)
  {
    cout << "0:" << b[i] << ", ";
  }
  
  for (int i = 1; i < _INITIALDATASIZE + 1; i++)
  {
    CPPUNIT_ASSERT( b[i - 1] <= b[i]);
  }
  
  return;
}
