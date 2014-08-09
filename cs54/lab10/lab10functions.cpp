/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/24/07
//File: lab10.h
//Purpose: To write the functions for the lab10 project

#include "lab10.h"

//Gets the values from the input stream and puts them in to an array
void getIntValues(int array[], const int arraylength, ifstream  &inFile) {
	for (int i = 0; i < arraylength; i++) {
		inFile >> array[i];
	}
	return;
}

//Initializes the arrays to zero
void initializeArray(int array[], const int arraylength) {
	for (int i = 0; i < arraylength; i++)
		array[i] = 0;
}

//prints the values of an array to the screen in (i, value of index i)
void toScreen(const int array[], const int arraylength) {
	cout << "Values from array (i,value of i): " << endl;
	for (int i = 0; i < arraylength; i++) {
		cout << "(" << i << "," << array[i] << ")" << endl;
	}
	return;
}

//Adds the values per instruction
void addValues(const int array1[], int array2[], const int arraylength1, const int arraylength2) {
	for (int i = 0; i <  arraylength2; i++) {
		array2[i] = array1[i] + array1[i + 3];
	}
	return;
}

//Subtracts the values per instruction
void subtractValues(const int array1[], int array2[], const int arraylength1, const int arraylength2) {
	for (int i = 0; i <  arraylength2; i++) {
		array2[i] = array1[i] - array1[i + 3];
	}
	return;
}

/**********************************END OF FILE********************************/
