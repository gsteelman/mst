/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 14 Nov 07
//File       : lab12main.cpp
//Purpose    : To write the control system for the lab12 project

#include "lab12.h"

int main() {

	//Creates an elevator aerosmith using the default constructor
	Elevator aerosmith;
	
	//Creates an elevator unsafe using the full constructor
	Elevator unsafe(42, 1.5);
	
	int floors;
	cout << "Please enter the number of floors to operate the elevator: ";
	cin >> floors;
	aerosmith.setFloors(floors);
	unsafe.setFloors(floors);
	
	int destinationFloor = 0;
	cout << "Please enter the destination floor for this elevator: ";
	cin >> destinationFloor;
	aerosmith.runElevator(destinationFloor);
	unsafe.runElevator(destinationFloor);
	
	return 0;
}

/*********************************END OF FILE*********************************/
