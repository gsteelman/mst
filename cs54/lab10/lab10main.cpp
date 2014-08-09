/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/24/07
//File: lab10main.cpp
//Purpose: To write the main function for the lab10 project 

#include "lab10.h"

int main() {
	//Declares all of the arrays that are to be used
	char inFileName[MAXFILENAMELENGTH];
	char outFileName[MAXFILENAMELENGTH];
	int fileContents[NUMINTSINFILE];
	int addedContents[NUMINTSAFTERADDITION];
	int subtractedContents[NUMINTSAFTERSUBTRACTION];
	
	//Initializes the arrays to 0s
	initializeArray(addedContents, NUMINTSAFTERADDITION);
	initializeArray(fileContents, NUMINTSINFILE);
	initializeArray(subtractedContents, NUMINTSAFTERSUBTRACTION);
	
	//Declares the file streams to be used
	ifstream inFile;
	ofstream outFile;
	
	//Gets the input file name
	cout << "Please enter the file name to open: ";
	cin >> inFileName;
	
	//Gets the output file name
	cout << "Please enter the file name to write to: ";
	cin >> outFileName;
	
	//Reads in the values from the input file name to the input values array
	inFile.open(inFileName);
	if (!inFile.fail()) {
		cout << "Input file found." << endl;
		getIntValues(fileContents, NUMINTSINFILE, inFile);
		toScreen(fileContents, NUMINTSINFILE);
	}
	else {
		cout << "Input file not found. Ending program." << endl;
		return 1;
	}
	
	//Adds the values per instruction into another array
	addValues(fileContents, addedContents, NUMINTSINFILE, NUMINTSAFTERADDITION);
	
	//Subtracts the values per instruction into another array
	subtractValues(fileContents, subtractedContents, NUMINTSINFILE, NUMINTSAFTERSUBTRACTION);
	
	//Outputs the added and subtracted values to the output file name
	outFile.open(outFileName);
	if (!outFile.fail()) {
		cout << "Output file found." << endl;
		
		toScreen(addedContents, NUMINTSAFTERADDITION);
		toScreen(subtractedContents, NUMINTSAFTERSUBTRACTION);
		
		outFile << "Added values: " << endl;
		for (int i = 0; i < NUMINTSAFTERADDITION; i++) {
			outFile << addedContents[i] << " ";
		}
		outFile << "\nSubtracted values: " << endl;
		for (int i = 0; i < NUMINTSAFTERSUBTRACTION; i++) {
			outFile << subtractedContents[i] << " ";
		}
	}
	else {
		cout << "Output file not found. Ending program." << endl;
		return 1;
	}
	
	//Closes the file streams as to clean up system
	inFile.close();
	outFile.close();
	return 0;
}

/**********************************END OF FILE********************************/
