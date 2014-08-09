// Programmer: Gary Steelman
// Class & Section: CS 54, Section D
// Date: 29 August 2007
// Purpose: This will read two numbers, multiplies them,
//          and displays the results to the screen

#include <iostream>
using namespace std;

int main()
{
  int product;
  int number1;
  int number2;

  // read in first number
  cout << "Please enter the first factor: ";
  cin >> number1;

  // print a blank line
  cout << endl;

  // read in the second number
  cout << "Please enter the second factor: ";
  cin >> number2;

  // print a blank line
  cout << endl;

  // multiply the two numbers
  product = number1 * number2;

  // print the result
  cout << number1 << " * " << number2 << " = " <<  product << endl;

  return 0;
}
