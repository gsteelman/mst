///////////////////////////////////////////////////////////////////////////////
/// @file test_bag.h
/// @author Gary Steelman, CS153-B
/// @edited 29 Jan 08
/// @brief Header file that calls CppUnit tests
///////////////////////////////////////////////////////////////////////////////

#ifndef TEST_BAG_H
#define TEST_BAG_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>
#include "bag.h"
#include "selectionsort.h"

class test_bag : public CPPUNIT_NS::TestFixture
{
  private:
    CPPUNIT_TEST_SUITE( test_bag );
    CPPUNIT_TEST( test_push_back );
    CPPUNIT_TEST( test_pop_back );
    CPPUNIT_TEST( test_search );
    CPPUNIT_TEST( test_sort );
    CPPUNIT_TEST_SUITE_END();
    
  protected:
    void test_push_back();
    void test_pop_back();
    void test_search();
    void test_sort();
};

#endif
