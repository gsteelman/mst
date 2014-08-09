/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 28 Nov 07
//File       : lab13main.cpp
//Purpose    : To write the control system for the lab13 project

#include "lab13.h"

int main() {
  //Seeds the random number generator
  srand(time(NULL));
  
  Elevator eleArray[numElevators];
  
  //Randomizes the elevator safety and floors using the overloaded !
  for (int i = 0; i < numElevators; i++)
    !eleArray[i];
   
	//Creates an elevator aerosmith using the default constructor
	Elevator aerosmith;
	
	//Creates an elevator unsafe using the full constructor
	Elevator unsafe(42, 1.5);
	
  //Gets and sets the number of floors for the elevators
	int floors;
	cout << "Please enter the number of floors to operate the elevator: ";
	cin >> floors;
	aerosmith.setFloors(floors);
	unsafe.setFloors(floors);
  
  //Gets and sets the height of each floor for the elevators
  int floorHeight;
  cout << "Please enter the height of each floor: ";
  cin >> floorHeight;
  aerosmith.setFloorHeight(floorHeight);
  unsafe.setFloorHeight(floorHeight);
  
	//Gets and sets the destination floor for each elevator
	int destinationFloor = 0;
	cout << "Please enter the destination floor for this elevator: ";
	cin >> destinationFloor;
	aerosmith.runElevator(destinationFloor);
	unsafe.runElevator(destinationFloor);
  
  //Calculates the safety score for the elevator
  aerosmith.safetyScore();
  unsafe.safetyScore();
  for (int i = 0; i < numElevators; i++)
    eleArray[i].safetyScore();
  
  cout << "The safety score is " << aerosmith.getSafety() << endl;
  cout << "The safety score is " << unsafe.getSafety() << endl;
  
  if (aerosmith < unsafe)
    cout << "Unsafe more safe than aerosmith!" << endl;
  else
    cout << "aerosmith safer than unsafe" <<endl;
	
  bubbleSort(eleArray, numElevators);
  
  cout << "Safest elevator's safety score: " << eleArray[0].getSafety() << endl;
  
	return 0;
}

/*********************************END OF FILE*********************************/
