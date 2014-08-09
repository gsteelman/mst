/* Programmer: Dylan McDonald
   Class & Section: CS 54, Section <n>
   Date: 2 October 2007
   Purpose: Make sure the user passed Algebra II */

#include <cmath>
#include <iostream>
using namespace std;

int main()
{
  double answer, argument;

  /* ask the user what they want to square root */
  cout << "What number do you want to square root? ";
  cin >> argument;

  /* show the user how smart we are */
  answer = sqrt(argument);
  cout << "sqrt(" << argument << ") = " << answer << endl;
  return 0;
}
