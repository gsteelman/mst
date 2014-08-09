/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 14 Nov 07
//File       : lab12.h
//Purpose    : To write the function prototypes, structures, and declare 
	//global variables for the lab12 project

#ifndef lab12
#define lab12

#include <iostream>
#include <cmath>

using namespace std;

//STRUCTURES-------------------------------------------------------------------

//GLOBAL VARIABLES-------------------------------------------------------------

//FUNCTION PROTOTYPES----------------------------------------------------------

//CLASSES----------------------------------------------------------------------
class Elevator
{
public:
	Elevator();
	Elevator(int numFloors, double floorHeight);
	
	int getCurrFloor() const;
	int getFloors() const;
	double getFloorHeight() const;
	double runElevator(const int &d);
	void setFloors(int numFloors);
	void setFloorHeight(double floorHeight);

private:
	int m_currFloor;
	int m_floors;
	double m_height;
};

#endif
	
/*********************************END OF FILE*********************************/
