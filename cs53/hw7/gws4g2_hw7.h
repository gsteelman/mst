/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/22/07
//File: gws4g2_hw7.h
//Purpose: To declare functions and global variables/constants for use
	//in the hw7 project

//Ensures this file is only included one time----------------------------------
#ifndef gws4g2_hw7_hINCLUDED
#define gws4g2_hw7_hINCLUDED

//INCLUDES---------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

//STRUCTURES-------------------------------------------------------------------
struct segment {
	double m_stephyp; //each individual segment total distance component
	double m_stepx; //each individual segment x component
	double m_stepy; //each individual segment y component
	double m_degrees; //the degree measure to walk toward in each segment
	double m_radians; //the radian conversion to walk toward in each segment
};

//FUNCTION PROTOTYPES----------------------------------------------------------

/* Generates the parts of each step
Pre: An initialized step struct and the random number generator seeded
Post: Generates values for each part of a step */
void generateSegment(segment &seg);

/* Calculates the longest walk taken of all walks
Pre: Initialized variables
Post: Returns the value of the larger of 2 variables */
double calcLongest(const double x, const double y, double currLong);

/* Calculates the shortest walk taken of all walks
Pre: initialized variables with currShort starting with a large value
Post: Returns the value of the smaller of 2 variables */
double calcShortest(const double x, const double y, double currShort);

/* Calculates the average walk based on the input of all x distances and y
	distances
Pre: Variables are initialized
Post: Returns the average value of passed variables */
double calcAverageWalk(const double x, const double y);

/* Calculates the median of the passed array
Pre: Array is sorted
Post: If the array is of an even number of entries, the middle 2 values are
	averaged and returned, otherwise the real median is returned */
double calcMedian(const double array[], const int arraysize);

//OVERLOADED OPERATORS---------------------------------------------------------

//TEMPLATED FUNCTIONS----------------------------------------------------------
/* Templated bubbleSort function will sort primitive data types with no 
overloading of operators.
Pre: Operator > is defined for passed type, C < than length of array passed
Post: Sorts passed array from least to greatest  */
template<typename T, typename C>
void bubbleSort(T array[], const C arraysize) {
	T temp = 0;
	T x = 0;
	T y = 0;
	for (int i = 0; i < arraysize; i++) {
		for (int j = 0; j < arraysize; j++) {
			if (array[j] > array[j + 1])
			{	
				x = array[j];
				y = array[j + 1];
				temp = x;
				x = y;
				y = temp;
			}
		}
	}
	return;
}

//GLOBAL CONSTANTS-------------------------------------------------------------
const int DEGREESRANGE = 359;
const int DEGREESINACIRCLE = 360;
const int WALKSTOTAKE = 100;
const int SEGMENTSEACHWALK = 50;
const int MAXSEGMENTLENGTH = 20;
const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148;
const double RADIANSINACIRCLE = 2 * PI;
const double REALLYBIGNUMBER = 50000000;

//GLOBAL VARIABLES-------------------------------------------------------------

//Ends the if beginning on line 9----------------------------------------------
#endif

/**********************************END OF FILE********************************/
