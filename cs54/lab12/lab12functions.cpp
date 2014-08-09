/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 14 Nov 07
//File       : lab12functions.cpp
//Purpose    : To write the funciton implementation for the lab12 project

#include "lab12.h"

//CONSTRUCTORS-----------------------------------------------------------------
//Default constructor for the elevator class
Elevator::Elevator() {
	m_currFloor = 0;
	m_floors = 0;
	m_height = 0;
	cout << "Default constructor reached." << endl;
}

//Full constructor for the elevator class
Elevator::Elevator (int numFloors, double floorHeight) {
	m_floors = numFloors;
	m_height = floorHeight;
	cout << "Full constructor reached." << endl;
}

//FUNCTIONS--------------------------------------------------------------------
//runs the elevator a certain number of floors 
double Elevator::runElevator(const int &d) {
	double c = m_currFloor; //Current floor
	double t = 0; //Time elevator took to run
	double h = m_height; //Height of the elevator
	
	//Range checks the destination floor
	if (d <= m_floors && d >= 0) {
		cout << "The destination floor is within range of the elevator." << endl;
		t = sqrt(h*abs(d - c));
		cout << "The time this journey took is " << t << endl;
	}
	else {
		cout << "The destination floor is not within range of this elevator."
			<< endl;
	}
	
	return t;
}

//Gets the current floor of the elevator
int Elevator::getCurrFloor() const {
		return m_currFloor;
}

//Gets the number of floors the elevator can travel
int Elevator::getFloors() const {
	return m_floors;
}

//Gets the floor height 
double Elevator::getFloorHeight() const {
	return m_height;
}

//sets the number of floors the elevator can run
void Elevator::setFloors(int numFloors) {
	m_floors = numFloors;
	return;
}

//sets the elevator height by the floor height
void Elevator::setFloorHeight(double floorHeight) {
	m_height = floorHeight;
	return;
}

/*********************************END OF FILE*********************************/
