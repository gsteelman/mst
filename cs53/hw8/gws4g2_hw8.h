/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 11 Nov 07
//File       : gws4g2_hw8.h
//Purpose    : To write the function prototypes and global variables
	//for the hw8 project
	
//Ensures this file is only included one time in the executable
#ifndef GWS4G2_HW8_H
#define GWS4G2_HW8_H

//INCLUDES---------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

//NAMESPACE TYPE---------------------------------------------------------------
using namespace std;

//GLOBAL VARIABLES-------------------------------------------------------------
const int MAXFILENAMELENGTH = 256;
const int MAXFILECONTENTSLENGTH = 10000;
const int MAXWORDSINSTREAM = 10000;
const int MAXWORDLENGTH = 500;

//STRUCTURES-------------------------------------------------------------------
/*struct word {
	char chars[MAXWORDLENGTH];
	int length;
};*/

//FUNCTION PROTOTYPES----------------------------------------------------------
/*prompt user for file or keyboard input
prompt user for file or screen output
get first word, if word is longer than 9 letters, insert thing after 6th char
	if word ends in s, add es to the end
	is -> are, he -> him, she -> her
random integer from 5-15, insert random phrase from file at index of random*/

int getInputType(ifstream &inFile);

int getOutputType(ofstream &outFile);

void readFileContents(ifstream &inFile, char fileContents[]);

void readKeyboardContents(char fileContents[]);

void convertEs(char fileContents[], int start, ofstream &outFile);

//void replace(char quote[], char toReplace[], char replaceWith[]);

int countInputStreamWords(char quote[]);

void toScreen(char fileContents[]);

void toFile(ofstream &outFile, char fileContents[]);

#endif

/*********************************END OF FILE*********************************/
