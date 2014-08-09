///////////////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @author Gary Steelman, CS153-B
/// @brief Main function containing a Hello World program for a QT4 application
///////////////////////////////////////////////////////////////////////////////

#include <QApplication>
#include <QLabel>
int main( int argc, char *argv[] )
{
  QApplication app( argc, argv );
  
  QLabel * label = new QLabel( "Hello Qt!" );
  
  label->show();
  
  return app.exec();
}
