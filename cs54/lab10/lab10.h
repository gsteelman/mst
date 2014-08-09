/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/24/07
//File: lab10.h
//Purpose: To write the function prototypes for the lab10 project 

#ifndef LAB10_H
#define LAB10_H

#include <iostream>
#include <fstream>

using namespace std;

//FUNCTION PROTOTYPES----------------------------------------------------------
//Gets the values from the input stream and puts them in to an array
void getIntValues(int array[], const int arraylength, ifstream  &inFile);
//prints the values of an array to the screen in (i, value of index i)
void toScreen(const int array[], const int arraylength);
//Adds the values per instruction
void addValues(const int array1[], int array2[], const int arraylength1, const int arraylength2);
//Subtracts the values per instruction
void subtractValues(const int array1[], int array2[], const int arraylength1, const int arraylength2);
//Initializes the arrays to zero
void initializeArray(int array[], const int arraylength);

//GLOBAL VARIABLES-------------------------------------------------------------
const int MAXFILENAMELENGTH = 256;
const int NUMINTSINFILE = 6;
const int NUMINTSAFTERADDITION = 3;
const int NUMINTSAFTERSUBTRACTION = 3;

#endif

/**********************************END OF FILE********************************/
