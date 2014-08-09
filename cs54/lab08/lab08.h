/*******************************BEGINNING OF FILE*****************************/
// Name: Gary Steelman
// Class and Section: CS 54, Section D
// Date: 10.17.07
// Purpose: To write the header file for a program that uses bubble sort to
	//sort an array, this includes function declarations, structs, and global
	//variables

#ifndef LAB08_H
#define LAB08_H

#include <ctime>
#include <iostream>

using namespace std;

const int ARRAYSIZE1 = 100000; 
const int ARRAYSIZE2 = 250000;
const int ARRAYSIZE3 = 500000;
const int ARRAYSIZE4 = 1000000;

/* Generates a random integer from 1 to 100 and returns the value
	Pre: None
	Post: Returns a random integer from 1-100 */
int randomInt1_100();

/* Initializes the array with random values from 1-100 
	Pre: Must be passed an array of ARRAYSIZE
	Post: Will return an intitialized array of size ARRAYSIZE */
void initiateArray(int array[], const int arraysize);

/* Sorts the array given using the bubble sort method
	Pre: Must be passed an array of ARRAYSIZE that has been initialized
	Post: Will sort the array via bubble sort */
void bubbleSort(int array[], const int arraysize);

/* Swaps the two given values of the array, part of the bubble sort
	Pre: Must be passed 2 integers
	Post: Swaps the two values by reference */
void swapIndicies(int &x, int &y);

/* Prints out the array to the screen
	Pre: Must be passed an array of ARRAYSIZE
	Post: Prints the values of the array to the screen */
//void printArray(int array[], const int arraysize);

#endif

/**********************************END OF FILE********************************/
