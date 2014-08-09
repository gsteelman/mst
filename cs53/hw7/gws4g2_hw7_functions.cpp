/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/22/07
//File: gws4g2_hw7_functions.cpp
//Purpose: To write functions for use in the hw7 project

#include "gws4g2_hw7.h"
#include "selectsort.h"

/* Generates the parts of each step
Pre: An initialized step struct and the random number generator seeded
Post: Generates values for each part of a step */
void generateSegment(segment &seg) {
	seg.m_stephyp = rand() % MAXSEGMENTLENGTH;
	seg.m_degrees = rand() % DEGREESRANGE;
	seg.m_radians = seg.m_degrees / DEGREESINACIRCLE * RADIANSINACIRCLE;
	seg.m_stepx = seg.m_stephyp * cos(seg.m_radians);
	seg.m_stepy = seg.m_stephyp * sin(seg.m_radians); 
	return;
}	
/* Calculates the longest walk taken of all walks
Pre: Initialized variables
Post: Returns the value of the larger of 2 variables */
double calcLongest(const double x, const double y, double currLong) {
	double length = 0;
	length = sqrt(pow(x,2) + pow(y,2));
	if (length > currLong) { currLong = length; }
	return currLong;
}

/* Calculates the shortest walk taken of all walks
Pre: initialized variables with currShort starting with a large value
Post: Returns the value of the smaller of 2 variables */
double calcShortest(const double x, const double y, double currShort) {
	double length = 0;
	length = sqrt(pow(x,2) + pow(y,2));
	if (length < currShort) { currShort = length; }
	return currShort;
}

/* Calculates the average walk based on the input of all x distances and y
	distances
Pre: Variables are initialized
Post: Returns the average value of passed variables */
double calcAverageWalk(const double x, const double y) {
	double length = 0;
	length = sqrt(pow(x,2) + pow(y,2));
	length /= WALKSTOTAKE;
	return length;
}

/* Calculates the median of the passed array
Pre: Array is sorted
Post: If the array is of an even number of entries, the middle 2 values are
	averaged and returned, otherwise the real median is returned */
double calcMedian(const double array[], const int arraysize) {
	double median = 0;
	int lbound = 0;
	int ubound = 0;
	if (arraysize % 2 == 0) { 
		lbound = static_cast<int>(arraysize/2); 
		ubound = static_cast<int>((arraysize/2)+1); 
	}
	median = (array[lbound] + array[ubound]) / 2;
	
	if (arraysize % 2 == 1) { median = (array[(arraysize/2)]); }
	return median;
}

/**********************************END OF FILE********************************/
