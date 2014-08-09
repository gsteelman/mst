/*******************************BEGINNING OF FILE*****************************/
// Name: Gary Steelman
// Class and Section: CS 54, Section D
// Date: 10.17.07
// Purpose: To write the functions for a program that uses bubble sort to
	//sort an array

#include "lab08.h"
	
/* Generates a random integer from 1 to 100 and returns the value
	Pre: None
	Post: Returns a random integoer from 1-100 */
int randomInt1_100() {
	int randNum = (rand() % 100) + 1;
	return randNum;
}

/* Initializes the array with random values from 1-100 
	Pre: Must be passed an array of ARRAYSIZE
	Post: Will return an intitialized array of size ARRAYSIZE */
void initiateArray(int array[], const int arraysize) {
	for (int i = 0; i < arraysize; i++) {
		array[i] = randomInt1_100();
	}
	
	return;
}

/* Sorts the array given using the bubble sort method
	Pre: Must be passed an array of ARRAYSIZE that has been initialized
	Post: Will sort the array via bubble sort */
void bubbleSort(int array[], const int arraysize) {
	for (int i = 0; i < arraysize; i++) {
		for (int j = 0; j < arraysize; j++) {
			if (array[j] > array[j + 1])
			{
				swapIndicies(array[j], array[j + 1]);
			}
		}
	}
	return;
}

/* Swaps the two given values of the array, part of the bubble sort
	Pre: Must be passed 2 integers
	Post: Swaps the two values by reference */
void swapIndicies(int &x, int &y) {
	int temp = x;
	x = y;
	y = temp;
	return;
}

/* Prints out the array to the screen
	Pre: Must be passed an array of ARRAYSIZE
	Post: Prints the values of the array to the screen */
void printArray(int array[], const int arraysize) {
	for(int i = 0; i < arraysize; i++)
		cout << array[i] << ", ";
	cout << endl;
	return;
}

/**********************************END OF FILE********************************/
