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
#include "bst.h"
#include "exception.h"

class Test_routines : public CPPUNIT_NS::TestFixture {

  private:
  
    CPPUNIT_TEST_SUITE(Test_routines);
      CPPUNIT_TEST(test_insert);
      CPPUNIT_TEST(test_remove);
      CPPUNIT_TEST(test_search);
    CPPUNIT_TEST_SUITE_END();
    
  protected:
  
    void test_insert();
    void test_remove();
    void test_search();
  
};

#endif
