/* Programmer: Dylan McDonald
   Class & Section: CS 54, Section <n>
   Date: 13 November 2007
   Purpose: To create & test an object oriented elevator */

#include "lab12.h"

/* default constructor sets everbody to 0 */
Elevator::Elevator()
{
  m_currFloor = 0;
  m_safety = 0;
  setFloors(0);
  setFloorHeight(0.0);
}

/* full constructor sets the private variables to the values passed in */
Elevator::Elevator(int numFloors, double floorHeight)
{
  m_currFloor = 0;
  /* calling setFloors() and setFloorHeight() with 0's first makes sure that
     m_floors and m_height can be 0 in case bad values were passed in */
  setFloors(0);
  setFloorHeight(0.0);

  /* now we can try to change the values of m_floors and m_height */
  setFloors(numFloors);
  setFloorHeight(floorHeight);
}

/* accessor for the current floor */
int Elevator::getCurrFloor() const
{
  return m_currFloor;
}

/* accessor for the number of floors */
int Elevator::getFloors() const
{
  return m_floors;
}

/* accessor for the floor height */
double Elevator::getFloorHeight() const
{
  return m_height;
}

/* accessor for the safety factor of the elevator */
double Elevator::getSafety() const 
{
  return m_safety;
}

/* mutator for the number of floors */
void Elevator::setFloors(int numFloors)
{
  if (numFloors >= 0)
    m_floors = numFloors;
}

/* mutator for the floor height */
void Elevator::setFloorHeight(double floorHeight)
{
  if (floorHeight >= 0.0)
    m_height = floorHeight;
}

/* calculates the safety score for the elevator */
void Elevator::safetyScore()
{
  double score = 0;
  
  return;
}

/* returns the number of seconds to move from m_currFloor to destination
   or -1.0 if the destination floor is invalid */
double Elevator::travelTime(int destination)
{
  double airTime = -1.0; /* value to return if destination is invalid */

  /* if the destination is valid, calculate the time */
  if (destination >= 0 && destination <= m_floors)
  {
    airTime = sqrt(m_height * (fabs(destination - m_currFloor)));
    m_currFloor = destination;
  }
  return airTime;
}

/* returns the number of seconds to drop the elevator through the atomosphere
   based on the atomospheric conditions passed in:
   temperature (K)
   pressure (Pa)
   airDrag (unitless)
   crossArea (m^2)
   humidity (unitless)
   mass (kg) */
double Elevator::fallTime(double temperature, double pressure, double airDrag,
                double crossArea, double humidity, double mass) const
{
  /* atomspheric variables */
  double dryPres, saturationPres, wetPres; /* pressures (Pa) */
  double density; /* (kg / m^2) */
  double exponent;

  /* kinematic variables */
  double heightToFall = m_currFloor * m_height;
  double acceleration, airTime = 0.0;
  double currVelocity, currDisplacement = 0.0;
  double prevVelocity = 0.0, prevDisplacement = 0.0;
 
  /* find air pressures */
  exponent = (EXP_COEFF0 * temperature - EXP_COEFF1)
           / (temperature - EXP_COEFF2);
  saturationPres = SAT_CONSTANT * pow(10.0, exponent);
  wetPres = humidity * saturationPres;
  dryPres = pressure - wetPres;

  /* find air density */
  density = dryPres / (DRY_TEMP * temperature)
          + wetPres / (WET_TEMP * temperature);

  /* now watch it fall - wheeee! */
  while (currDisplacement < heightToFall)
  {
    /* calculate our current three */
    acceleration = ((mass * GRAVITY)
                 - (0.5 * airDrag * density * crossArea
                 * prevVelocity * prevVelocity)) / mass;
    currVelocity = prevVelocity + acceleration * TIME_STEP;
    currDisplacement = prevDisplacement + currVelocity * TIME_STEP;

    /* save them as our previous three & advance time */
    prevVelocity = currVelocity;
    prevDisplacement = currDisplacement;
    airTime += TIME_STEP;
  }
  return airTime;
}

/* returns true if value is on the interval [low, high] if halfClosed
   is false; checks the interval (low, high] if halfClosed is true */
bool inRange(double value, double low, double high, bool halfClosed)
{
  if (halfClosed)
    return (value > low && value <= high);
  else
    return (value >= low && value <= high);
}
