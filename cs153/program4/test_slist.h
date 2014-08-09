//////////////////////////////////////////////////////////////////////
/// @file test_slist.h
/// @author Gary Steelman, CS153-B
/// @brief Tests for a slist class
//////////////////////////////////////////////////////////////////////

#ifndef TEST_SLIST_H
#define TEST_SLIST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>
#include "slist.h"
#include "exception.h"

class Test_slist : public CPPUNIT_NS::TestFixture {

  private:
  
    CPPUNIT_TEST_SUITE(Test_slist);
      CPPUNIT_TEST(test_push_front);
      CPPUNIT_TEST(test_pop_front);
      CPPUNIT_TEST(test_clear);
      CPPUNIT_TEST(test_remove);
    CPPUNIT_TEST_SUITE_END();
    
  protected:
  
    void test_push_front();
    void test_pop_front();
    void test_clear();
    void test_remove();
  
};
#endif
