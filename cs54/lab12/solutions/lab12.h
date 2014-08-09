/* Programmer: Dylan McDonald
   Class & Section: CS 54, Section <n>
   Date: 13 November 2007
   Purpose: To create & test an object oriented elevator */

#ifndef LAB12_H
#define LAB12_H

#include <cfloat>
#include <cmath>
#include <iostream>
using namespace std;

/* well known constants (some better known than others) */
const double EXP_COEFF0 = 7.5;
const double EXP_COEFF1 = 2048.625;
const double EXP_COEFF2 = 35.85;
const double DRY_TEMP = 287.05;
const double WET_TEMP = 461.495;
const double SAT_CONSTANT = 610.78;
const double GRAVITY = 9.80665;
const double TIME_STEP = 1.0e-6;
const double INFTY = DBL_MAX; /* largest possible double (from cfloat) */

class Elevator
{
public:
  /* constructors */
  Elevator();
  Elevator(int numFloors, double floorHeight);

  /* accessor/mutator functions */
  int getCurrFloor() const;
  int getFloors() const;
  double getFloorHeight() const;
  double getSafety() const;
  void safetyScore();
  void setFloors(int numFloors);
  void setFloorHeight(double floorHeight);

  /* Part II & III functions */
  double travelTime(int destination);
  double fallTime(double temperature, double pressure, double airDrag,
                  double crossArea, double humidity, double mass) const;

private:
  int m_currFloor;
  int m_floors;
  double m_height;
  double m_safety;
};

/* helper function for range checking */
bool inRange(double value, double low, double high, bool halfClosed = false);

#endif
