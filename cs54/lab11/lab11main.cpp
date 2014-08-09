/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 7 Nov 07
//File       : lab11main.cpp
//Purpose    : To write the main function for the lab11 project

#include "lab11.h"

int main() {
	char tempArray[PHONENUMBERLENGTH + NAMELENGTH];
		memset(tempArray, '\0', NAMELENGTH + PHONENUMBERLENGTH);
	phonebookEntry phonebook[PHONEBOOKENTRIES];
	initializePhonebook(phonebook);
	
	ifstream phonebookIn;
	
	getPhonebookInName(phonebookIn);
	
	readPhonebook(phonebook, phonebookIn, tempArray);
	outputPhonebook(phonebook);
	
	phonebookIn.close();
	
	return 0;
}


	
/*********************************END OF FILE*********************************/
