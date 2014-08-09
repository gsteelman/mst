//////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @author Jeremy Davidson -- CS 153 Section 1B
/// @brief Calls tests to analyze the functionality of the list class
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include "stack.h"
#include "exception.h"
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;

int main() {

  srand(time(NULL));

  CppUnit::TextUi::TestRunner runner;
  
  CppUnit::TestFactoryRegistry & registry =
      CppUnit::TestFactoryRegistry::getRegistry();
  
  runner.addTest( registry.makeTest() );
  
  return runner.run( "", false );

}
