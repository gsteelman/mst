/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/24/07
//File: lab09.h
//Purpose: To declare functions and global variables/constants for use
	//in the lab09 project

#ifndef LAB09
#define LAB09

#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

//FUNCTION PROTOTYPES----------------------------------------------------------
//Welcomes the user
void welcome();

//Gets the student name and stores it into an array
void getStudentName(char studentName[]);

//Converts the studentName array to all upper case letters
void convertToUpper(char studentName[]);

//Computes and returns the fallgren score of the student
double fallgren(const char studentName[]);

//Outputs the fallgren score
void outputFallgrenScore(double fallgrenScore);

//Computes and returns the mues score of the student
double mues(char studentName[], double fallgrenScore);

//Outputs the mues score
void outputMuesScore(double muesScore);

//Computes the holdener score of the student
double holdener(char studentName[]);

//Outputs the holdener score
void outputHoldenerScore(double holdenerScore);

//Says goodbye to the user
void goodbye();

//GLOBAL VARIABLES-------------------------------------------------------------
const int ARRAYSIZE = 42;
const int ASCIICONV = 64;
const int NUMLETTERSINALPHABET = 26;

#endif
	
/**********************************END OF FILE********************************/
