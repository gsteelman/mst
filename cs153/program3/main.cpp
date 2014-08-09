///////////////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @author Gary Steelman, CS153-B
/// @edited 06 Feb 08
/// @brief CppUnit test run file
///////////////////////////////////////////////////////////////////////////////

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main()
{
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry & registry =
  CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest( registry.makeTest() );
  return runner.run( "", false );
}
