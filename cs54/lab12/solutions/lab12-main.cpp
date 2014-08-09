/* Programmer: Dylan McDonald
   Class & Section: CS 54, Section <n>
   Date: 13 November 2007
   Purpose: To create & test an object oriented elevator */

#include "lab12.h"

int main()
{
  int destination, numFloors;
  double temperature, pressure, airDrag, crossArea, humidity, mass, height;
  Elevator TJNorth;

  /* get the number of floors */
  do
  {
    cout << "How many floors are in the building? ";
    cin >> numFloors;
  } while (numFloors < 0);

  /* get the floor height */
  do
  {
    cout << "What is the height of each floor? ";
    cin >> height;
  } while (!inRange(height, 0.0, INFTY));

  /* get the destination floor */
  do
  {
    cout << "What floor would you like to go to? ";
    cin >> destination;
  } while (destination < 0 || destination > numFloors);
  
  /* get the temperature */
  do
  {
    cout << "What is the temperature (K)? ";
    cin >> temperature;
  } while (!inRange(temperature, 183.0, 331.0));
  
  /* get the atomospheric pressure */
  do
  {
    cout << "What is the barometric pressure (Pa)? ";
    cin >> pressure;
  } while (!inRange(pressure, 87000.0, 108380.0));

  /* get air drag constant */
  do
  {
    cout << "What is the air drag constant? ";
    cin >> airDrag;
  } while (!inRange(airDrag, 0.0, 2.5, true));
  
  /* get the cross sectional area */
  do
  {
    cout << "What is the cross sectional area (m^2)? ";
    cin >> crossArea;
  } while (!inRange(crossArea, 0.0, INFTY, true));

  /* get the relative humidity */
  do
  {
    cout << "What is the relative humidity? ";
    cin >> humidity;
  } while (!inRange(humidity, 0.0, 1.0));
  
  /* get the mass */
  do
  {
    cout << "What is the mass of the elevator & passengers (kg)? ";
    cin >> mass;
  } while (!inRange(mass, 0.0, INFTY, true));
  
  /* build the elevator */
  TJNorth.setFloors(numFloors);
  TJNorth.setFloorHeight(height);
  
  /* run the elevator */
  cout << "Going from floor " << TJNorth.getCurrFloor() << " to floor ";
  cout << destination << " takes " << TJNorth.travelTime(destination)
       << " seconds." << endl;

  /* drop the elevator :) */
  cout << "Dropping the elevator from floor " << TJNorth.getCurrFloor()
       << " takes " << TJNorth.fallTime(temperature, pressure, airDrag,
                                        crossArea, humidity, mass)
       << " seconds to kill everybody on board." << endl;
       
  cout << "The safety score is " << TJNorth.safetyScore() << endl;
  return 0;
}
