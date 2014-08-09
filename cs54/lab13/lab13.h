/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 28 Nov 07
//File       : lab13.h
//Purpose    : To write the function prototypes, structures, and declare 
	//global variables for the lab13 project

#ifndef lab13
#define lab13

#include <iostream>
#include <cmath>
#include <cfloat>

using namespace std;

//STRUCTURES-------------------------------------------------------------------

//GLOBAL VARIABLES-------------------------------------------------------------
const int numElevators = 50;
const double lBoundHeight = 0;
const double uBoundHeight = 4.2;
const double lBoundFloors = 0;
const double uBoundFloors = 420;

//FUNCTION PROTOTYPES----------------------------------------------------------
double randDouble(double low, double high);

//TEMPLATED FUNCTIONS----------------------------------------------------------
/* takes in an input array & size and bubble sorts it */
template<class T>
void bubbleSort(T inputArray[], unsigned int size)
{
  unsigned int i;
  bool swapped = false;
  T temp;

  do
  {
    /* assume we haven't swapped anything before bubbling */
    swapped = false;

    /* bubble through the array */
    for (i = 0; i < size - 1; i++)
    {
      /* bubble the larger element up */
      if (inputArray[i] < inputArray[i + 1])
      {
        swapped = true;
        temp = inputArray[i];
        inputArray[i] = inputArray[i + 1];
        inputArray[i + 1] = temp;
      }
    }
  } while (swapped);
}

//CLASSES----------------------------------------------------------------------
class Elevator
{
public:
	Elevator();
	Elevator(int numFloors, double floorHeight);
	
  bool operator<(const Elevator &e);
  void operator!();
  
	int getCurrFloor() const;
	int getFloors() const;
	double getFloorHeight() const;
  double getSafety() const;
  void safetyScore();
	double runElevator(const int &d);
	void setFloors(int numFloors);
	void setFloorHeight(double floorHeight);

private:
	int m_currFloor;
	int m_floors;
  double m_safety;
	double m_height;
};

#endif
	
/*********************************END OF FILE*********************************/
