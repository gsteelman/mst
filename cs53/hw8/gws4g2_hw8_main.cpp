/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 11 Nov 07
//File       : gws4g2_hw8_main.cpp
//Purpose    : To write the control system for the hw8 project

#include "gws4g2_hw8.h"

int main() {
	srand(time(NULL));
	
	int outputType = 0;
	int inputType = 0;
	int wordsInStream = 0;
	
	ifstream inFile;
	ofstream outFile;
	char fileContents[MAXFILECONTENTSLENGTH];
	
	inputType = getInputType(inFile);
	
	outputType = getOutputType(outFile);
	
	//user selected to read from file
	if (inputType == 1) 
		readFileContents(inFile, fileContents);
	
	//user selected to read from keyboard
	if (inputType == 2)
		readKeyboardContents(fileContents);
	
	wordsInStream = countInputStreamWords(fileContents);
	
	//just send a 0 to start it
	convertEs(fileContents, 0, outFile);
	
	//replace(fileContents, "s ", "es");
	
	//user selected to output to a file
	/*if (outputType == 1)
		toFile(outFile, fileContents);
	
	//user selected to putput to the screen
	if (outputType == 2)
		toScreen(fileContents);*/
	
	inFile.close();
	outFile.close();
	
	return 0;
}

/*********************************END OF FILE*********************************/
