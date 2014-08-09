//Gary Steelman
//CS 54-D
//9.5.07
//Takes the input of time, initial velocity, and initial x position from the
//user and computes the final x position and then outputs that to the user.
//Also calculates the final velocity and outputs

#include <iostream>

using namespace std;

int main()
{
  double xf = 0;
  double vf = 0;
  double t = 0;
  double v0 = 0;
  double x0 = 0;

  cout << "This program will ask for the length of the time the object was " <<
    "\nin free fall, the initial velocity of the object and the initial x " <<
    "\nposition of the object." << endl;

  cout << "How long was the object in the air? ";
    cin >> t;

  cout << "What was the initial velocity of the object? ";
    cin >> v0;

  cout << "What was the intiial x position of the object? ";
    cin >> x0;

  xf = (4.9 * t * t) + (v0 * t) + x0;

  cout << "The final x position of the object is: " << xf << endl;

  vf = (9.8 * t) + v0;
  
  cout << "The final velocity of the object is: " << vf << endl;
  
  return 0;
} 
