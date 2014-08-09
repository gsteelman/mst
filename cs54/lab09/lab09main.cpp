/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/24/07
//File: lab09main.cpp
//Purpose: To write the main function for use in the lab09 project

#include "lab09.h"

int main() {
	char studentName[ARRAYSIZE];
		//Initializes the studentName array to zeroes
		for (int i = 0; i < ARRAYSIZE; i++) { studentName[i] = 0; }
	double fallgrenScore = 0;
	double muesScore = 0;
	double holdenerScore = 0;
	
	welcome();
	
	getStudentName(studentName);
	
	convertToUpper(studentName);
	
	fallgrenScore = fallgren(studentName);
	
	outputFallgrenScore(fallgrenScore);
	
	muesScore = mues(studentName, fallgrenScore);
	
	outputMuesScore(muesScore);
	
	holdenerScore = holdener(studentName);
	
	outputHoldenerScore(holdenerScore);
	
	goodbye();
	
	return 0;
}

/**********************************END OF FILE********************************/
