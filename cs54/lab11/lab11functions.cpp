/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 7 Nov 07
//File       : lab11functions.cpp
//Purpose    : To implement the fucntions for the lab11 project

#include "lab11.h"

void initializePhonebook(phonebookEntry phonebook[]) {
	for (int i = 0; i < PHONEBOOKENTRIES; i++) {
		memset(phonebook[i].m_name, '\0', 32);
		memset(phonebook[i].m_phoneNumber, '\0', 20);
	}
	return;
}

void getPhonebookInName(ifstream &phonebookIn) {
	char phonebookInName[MAXFILENAMELENGTH];
	memset(phonebookInName, '\0', MAXFILENAMELENGTH);
	do {
		cout << "Please enter the name of the file to open: ";
		cin >> phonebookInName;
		phonebookIn.open(phonebookInName);
		if (!phonebookIn.fail()) 
			cout << "Input file found." << endl;
		else 
			cout << "Input file not found. Try again." << endl;
	} while (phonebookIn.fail());
	return;
}
	
void readPhonebook(phonebookEntry phonebook[], ifstream &phonebookIn, char tempArray[]) {
	for (int i = 0; i < PHONEBOOKENTRIES; i++) {
		//gets the phone number for each entry, when its done, breaks
		int k = 0;
		for (int j = 0; j < (PHONENUMBERLENGTH + NAMELENGTH); j++) {
			phonebookIn.get(tempArray[j]);
			//if currently read character is a digit, adds to phonenumber
			if (tempArray[j] == '\n') {
				break;
			}
			if (isdigit(tempArray[j])) {
				phonebook[i].m_phoneNumber[j] = tempArray[j];
			}
			//if the currently read digit is not a number, adds to name
			else {
				phonebook[i].m_name[k] = tempArray[j];
				k+=1;
			}	
		}
		memset(tempArray, '\0', PHONENUMBERLENGTH + NAMELENGTH);		
	}
	return;
}

void outputPhonebook(phonebookEntry phonebook[]) {
	cout << "Phonebook: " << endl;
	for (int i = 0; i < PHONEBOOKENTRIES; i++) {
		cout << i + 1 << ": " << phonebook[i].m_name << endl;
		cout << " : " << phonebook[i].m_phoneNumber << endl;
	}
	return;
}

/*********************************END OF FILE*********************************/
