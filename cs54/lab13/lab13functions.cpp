/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 28 Nov 07
//File       : lab13functions.cpp
//Purpose    : To write the funciton implementation for the lab13 project

#include "lab13.h"

//CONSTRUCTORS-----------------------------------------------------------------
//Default constructor for the elevator class
Elevator::Elevator() {
	m_currFloor = 0;
	m_floors = 0;
	m_height = 0;
	//cout << "Default constructor reached." << endl;
}

//Full constructor for the elevator class
Elevator::Elevator (int numFloors, double floorHeight) {
	m_floors = numFloors;
	m_height = floorHeight;
	//cout << "Full constructor reached." << endl;
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

//Overloaded < operator for comparing the safety score of 2 elevators
bool Elevator::operator<(const Elevator &e) {
  bool lessThan = false;
  if (m_safety < e.m_safety)
    lessThan = true;
  return lessThan;
}

//Overloaded ! operator for randomizing the number of floors and the floor
  //height for the set of operators
void Elevator::operator!() {
  double numFloors = 0;
  double floorHeight = 0;
  numFloors = randDouble(lBoundFloors, uBoundFloors);
  floorHeight = randDouble(lBoundHeight, uBoundHeight);
  m_floors = numFloors;
  m_height = floorHeight;
  //cout << "m_height: " << m_height << "; m_floors: " << m_floors << endl;
  return;
}

//Returns the safety score
double Elevator::getSafety() const {
  return m_safety;
}

//Calculates the safety score
void Elevator::safetyScore()
{
  double score = 0;
  
  if (m_height == 0 || m_floors == 0) 
    score = 0;
  else {
  score = ((m_height + m_floors) * fabs(m_height - m_floors)) / 
    (pow(m_height, 3.0) * pow(m_floors, 4.0));
  }
  
  m_safety = score;
  return;
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

/* returns a random number on the interval [low, high) */
double randDouble(double low, double high)
{
  double temp;

/* swap low & high around if the user makes no sense */
  if (low > high)
  {
    temp = low;
    low = high;
    high = temp;
  }

  /* calculate the random number & return it */
  temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0))
       * (high - low) + low;
  return temp;
}

/*********************************END OF FILE*********************************/
