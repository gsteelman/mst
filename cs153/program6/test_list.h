//////////////////////////////////////////////////////////////////////
/// @file test_list.h
/// @author Jeremy Davidson -- CS 153 Section 1B
/// @brief Tests for a list class
//////////////////////////////////////////////////////////////////////

#ifndef TEST_LIST_H
#define TEST_LIST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>
#include "list.h"
#include "exception.h"

class Test_list : public CPPUNIT_NS::TestFixture {

  private:
  
    CPPUNIT_TEST_SUITE(Test_list);
      CPPUNIT_TEST(test_push_front);
      CPPUNIT_TEST(test_pop_front);
      CPPUNIT_TEST(test_clear);
      CPPUNIT_TEST(test_remove);
      CPPUNIT_TEST(test_push_back);
      CPPUNIT_TEST(test_remove_back);
    CPPUNIT_TEST_SUITE_END();
    
  protected:
  
    void test_push_front();
    void test_pop_front();
    void test_clear();
    void test_remove();
    void test_push_back();
    void test_remove_back();
  
};

#endif
