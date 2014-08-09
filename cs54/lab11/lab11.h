/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 7 Nov 07
//File       : lab11.h
//Purpose    : To write the function prototypes, global variables, and the 
	//structures

#ifndef LAB11_H
#define LAB11_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

//GLOBAL VARIABLES-------------------------------------------------------------
const int PHONEBOOKENTRIES = 6;
const int MAXFILENAMELENGTH = 256;
const int PHONENUMBERLENGTH = 20;
const int NAMELENGTH = 32;

//STRUCTURES-------------------------------------------------------------------
struct phonebookEntry {
	char m_phoneNumber[20]; //Phone number here
	char m_name[32]; //First and last name here
};

//FUNCTION PROTOTYPES----------------------------------------------------------
void initializePhonebook(phonebookEntry phonebook[]);
void getPhonebookInName(ifstream &phonebookIn);
void readPhonebook(phonebookEntry phonebook[], ifstream &phonebookIn, char tempArray[]);
void outputPhonebook(phonebookEntry phonebook[]);

#endif
	
/*********************************END OF FILE*********************************/
