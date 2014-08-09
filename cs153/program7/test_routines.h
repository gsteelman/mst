//////////////////////////////////////////////////////////////////////
/// @file test_routines.h
/// @author Jeremy Davidson -- CS 153 Section 1B
/// @brief Tests for classes
//////////////////////////////////////////////////////////////////////

#ifndef TEST_ROUTINES_H
#define TEST_ROUTINES_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>
#include <ctime>
#include <cstdlib>
#include "library.h"
#include "exception.h"

class Test_routines : public CPPUNIT_NS::TestFixture {

  private:
  
    CPPUNIT_TEST_SUITE(Test_routines);
      //<Ok!>
      CPPUNIT_TEST(test_search);
      CPPUNIT_TEST(test_binary_search);
      CPPUNIT_TEST(test_bubble_sort);
      CPPUNIT_TEST(test_selection_sort);
      CPPUNIT_TEST(test_insertion_sort);
      CPPUNIT_TEST(test_quick_sort);
      CPPUNIT_TEST(test_merge_sort);
      //</Ok!>
    CPPUNIT_TEST_SUITE_END();
    
  protected:
  
    void test_search();
    void test_binary_search();
    void test_bubble_sort();
    void test_selection_sort();
    void test_insertion_sort();
    void test_quick_sort();
    void test_merge_sort();
  
};

template <class generic>
bool isSorted(Vector<generic> & v);

#endif
