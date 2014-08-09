/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/24/07
//File: lab09functions.cpp
//Purpose: To write functions in the lab09 project

#include "lab09.h"

//Welcomes the user
void welcome() {
	cout << "Welcome to the Price Institute Grading Program" << endl;
}

//Gets the student name and stores it into an array
void getStudentName(char studentName[]) {
	cout << "Please enter the student's name: ";
	cin >> studentName;
	return;
}

//Converts the studentName array to all upper case letters
void convertToUpper(char studentName[]) {
	for (int i = 0; i < strlen(studentName) && i < ARRAYSIZE; i++) {
		studentName[i] = toupper(studentName[i]);
	}
	return;
}

//Computes and returns the fallgren score of the student
double fallgren(const char studentName[]) {
	double fallgrenScore = 0;
	int numChars = 0;
	char fallgrenScoreCalc[ARRAYSIZE];
	for (int i = 0; i < strlen(studentName) && i < ARRAYSIZE; i++)
		fallgrenScoreCalc[i] = studentName[i];
	for (int i = 0; i < strlen(studentName) && i < ARRAYSIZE; i++) {
		fallgrenScoreCalc[i] -= ASCIICONV;
		fallgrenScore += (fallgrenScoreCalc[i] * (i + 1));
		numChars+=1;
	}
	fallgrenScore /= (numChars * NUMLETTERSINALPHABET);
	return fallgrenScore;
}

//Outputs the fallgren score
void outputFallgrenScore(double fallgrenScore) {
	cout << "The student's fallgren score is: " << fallgrenScore * 100 << "%" << endl;
	return;
}

//Computes and returns the mues score of the student
double mues(char studentName[], double fallgrenScore) {
	double muesScore = 0;
	double vowelCounter = 0;
	double multiplier = 0;
	for (int i = 0; i < strlen(studentName) && i < ARRAYSIZE; i++) {
		if (studentName[i] == 'A' || studentName[i] == 'E' || studentName[i] == 'I' || studentName[i] == 'O' ||studentName[i] == 'U')
			vowelCounter += 1;
	}
	multiplier = (((static_cast<double>(strlen(studentName))) - vowelCounter) / static_cast<double>(strlen(studentName)));
	muesScore = fallgrenScore * multiplier;
	return muesScore;
}

//Outputs the mues score
void outputMuesScore(double muesScore) {
	cout << "The student's mues score is: " << muesScore * 100<< "%" << endl;
	return;
}

//Computes the holdener score of the student
double holdener(char studentName[]) {
	double holdenerScore = 0;
	char holdenerScoreCalc[ARRAYSIZE];
	double holdenerScoreInternal = 1;
	for (int i = 0; i < strlen(studentName) && i < ARRAYSIZE; i++)
		holdenerScoreCalc[i] = studentName[i];
	for (int i = 0; i < strlen(studentName) && i < ARRAYSIZE; i++) {
		holdenerScoreCalc[i] -= ASCIICONV;
		holdenerScoreInternal *= holdenerScoreCalc[i];
	}
	holdenerScore = pow(holdenerScoreInternal,(1/static_cast<double>(strlen(holdenerScoreCalc))));
	return holdenerScore;
}

//Outputs the holdener score
void outputHoldenerScore(double holdenerScore) {
	cout << "The student's holdener score is: " << holdenerScore * 100 << "%" << endl;
	return;
}

//Says goodbye to the user
void goodbye() {
	cout << "Thank you for using the Price Institute Grading Program" << endl;
	return;
}

/**********************************END OF FILE********************************/
