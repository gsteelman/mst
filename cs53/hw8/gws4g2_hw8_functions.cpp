/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 11 Nov 07
//File       : gws4g2_hw8_functions.cpp
//Purpose    : To write the function implementation for the hw8 project

#include "gws4g2_hw8.h"

int getInputType(ifstream &inFile) {
	char inputType = 'z';
	char inputFileName[MAXFILENAMELENGTH];
	int inputTypeLegit = 0;
	
	do {
		cout << "Please enter the type of input you wish to use." << endl;
		cout << "   Enter \"k\" for keyboard or \"f\" for a file: ";
		cin >> inputType;
		switch (inputType) {
			case 'k':
			case 'K':
				cout << "--You have selected to input from the keyboard." 
					<< endl;
				inputTypeLegit = 2;
				break;
			case 'f':
			case 'F':
				cout << "--You have selected to input from a file." << endl;
				cout << "Please input the name of the file to read from: ";
				cin >> inputFileName;
				inputTypeLegit = 1;
				break;
			default: 
				cout << "--Incorrect input type, please choose again." << endl;
				inputTypeLegit = 0;
				break;
		}
	} while (inputTypeLegit == 0);
	
	if (inputTypeLegit == 1) {
		inFile.open(inputFileName);
		if (!inFile.fail()) {
			cout << "--Input file found." << endl;
		}
		else {
			cout << "--Input file not found. Ending program." << endl;
			return 1;
		}
	}
	return inputTypeLegit;
}

int getOutputType(ofstream &outFile) {
	char outputType = 'z';
	char outputFileName[MAXFILENAMELENGTH];
	int outputTypeLegit = 0;
	char overwrite = 'z';
	int overwriteLegit = 0;
	
	do {
		cout << "Please enter the type of output you wish to use." << endl;
		cout << "   Enter \"s\" for screen or \"f\" for a file: ";
		cin >> outputType;
		switch (outputType) {
			case 's':
			case 'S':
				cout << "You have selected to output to the screen." <<endl;
				outputTypeLegit = 2;
				break;
			case 'f':
			case 'F':
				cout << "You have selected to output to a file." << endl;
				cout << "Please input the name of the file to write to: ";
				cin >> outputFileName;
				outputTypeLegit = 1;
				break;
			default: 
				cout << "--Incorrect output type, please choose again." 
					<< endl;
				outputTypeLegit = 0;
				break;
		}
	} while (outputTypeLegit == 0);
	
	if (outputTypeLegit == 1) {
	outFile.open(outputFileName);
		if(!outFile.fail()) {
			do {
				cout << "Output file exists. Overwrite? (y/n): ";
				cin >> overwrite;
				switch (overwrite) {
					case 'y':
					case 'Y':
						cout << "--File will be overwritten." << endl;
						overwriteLegit = 1;
						break;
					case 'n':
					case 'N':
						cout << "--File will not be overwritten, output ";
						cout << "not happen.";
						overwriteLegit = 1;
						break;
					default:
						cout << "--Incorrect overwrite answer, please ";
						cout << "choose again." << endl;
				}
			}while (outputType == 0);
		}
	}
	return outputTypeLegit;
}

void readFileContents(ifstream &inFile, char fileContents[]) {
	double wordCount = 0;
	cout << "--Reading contents of file..." << endl;
	while (!inFile.eof()) {
		for (int i = 0; i < MAXFILECONTENTSLENGTH; i++) {
			if (inFile.eof()) { fileContents[i] = '\0'; break; }
			fileContents[i] = inFile.get();
		}
	}
	wordCount = countInputStreamWords(fileContents);
	cout << "There are " << wordCount << " words in the input stream." << endl;
	return;
}

void readKeyboardContents(char fileContents[]) {
	double wordCount = 0;
	cout << "Please enter a quote of at least 5 words: ";
	cin.ignore();
	cin.getline(fileContents, MAXFILECONTENTSLENGTH);
	wordCount = countInputStreamWords(fileContents);
	cout << "--There are " <<  wordCount << " words in the input stream." 
		<< endl;
	return;
}

void convertEs(char fileContents[], int start, ofstream &outFile) {
	char newFileContents[MAXFILECONTENTSLENGTH];
	char herFileContents[MAXFILECONTENTSLENGTH];
	char himFileContents[MAXFILECONTENTSLENGTH];
	char areFileContents[MAXFILECONTENTSLENGTH];
	char  esFileContents[MAXFILECONTENTSLENGTH];
	char sayFileContents[MAXFILECONTENTSLENGTH];
	
	//Initializes the arrays to all zeroes.
	for (int i = 0; i < MAXFILECONTENTSLENGTH; i++) 
		{ newFileContents[i] = 0; }
	for (int i = 0; i < MAXFILECONTENTSLENGTH; i++) 
		{ herFileContents[i] = 0; }
	for (int i = 0; i < MAXFILECONTENTSLENGTH; i++) 
		{ himFileContents[i] = 0; }
	for (int i = 0; i < MAXFILECONTENTSLENGTH; i++) 
		{ areFileContents[i] = 0; }
	for (int i = 0; i < MAXFILECONTENTSLENGTH; i++) 
		{  esFileContents[i] = 0; }
	for (int i = 0; i < MAXFILECONTENTSLENGTH; i++) 
		{ sayFileContents[i] = 0; }
	
	int y = 0;
	fileContents[strlen(fileContents)] = ' ';
	
	cout << "fileContents:: " << fileContents << endl;
	
	//Shifts everything in the fileContents array to the right one, adding 
	//a space at the beginning
	newFileContents[0] = ' ';
	for (int i = 0; i < strlen(fileContents); i++) 
		{ newFileContents[i + 1] = fileContents[i]; }
	for (int i = 0; i < strlen(newFileContents); i++) 
		{ fileContents[i] = newFileContents[i]; }
	
	cout << "fileContents after space addition:: " << fileContents << endl;
	cout << "newFileContents after space addition:: " << newFileContents 
		<< endl;
	
	//uses newFileContents to search for words > 9 characters logn and then
	//appends them into fileContents (should have written this one first T_T)
	//"-er-" or "-uh-" or "-um-", regular fashion
	int insertStatementChoice = 0;
	int letterCount = 0;
	int z = 0;
	y = 0;
	/*for (int i = 0; i < strlen(newFileContents)-1; i++) {
		fileContents[y] = newFileContents[z];
		for (int j = 0; newFileContents[i + j] != ' '; j++) {
			letterCount+=1;
			//cout << "i inside j loop: " << i << endl;
			//cout << "j inside j loop: " << j << endl;
			//cout << "y inside j loop: " << y << endl;
			//cout << "letterCount inside j loop: " << letterCount << endl;
		}
		
		int tempi = i;
		int tempz = z;
		do {
			//if (newFileContents[i + z] == ' ') { letterCount = 0; break; }
			if (newFileContents[tempi + tempz] != ' ') { 
				letterCount+=1; 
			}
			cout << "tempi inside do loop: " << tempi << endl;
			cout << "tempz inside do loop: " << tempz << endl;
			//letterCount+=1;
			tempz+=1;
		} while (newFileContents[tempi + tempz] != ' ');
		cout << "i: " << i << endl;
		cout << "y: " << y << endl;
		if (letterCount >= 9) {
			for (int blargh = 0; blargh < 6; blargh++) { 
				fileContents[y + blargh] = newFileContents[i + blargh]; 
				cout << "   fileContents[y + blargh]: " << fileContents[y + blargh] << endl;
				cout << "newFileContents[i + blargh]: " << newFileContents[i + blargh] << endl;
			}
			if (insertStatementChoice == 0) { 
				strcat(fileContents, "-er-"); 
				insertStatementChoice = 1;
			}
			else if (insertStatementChoice == 1) { 
				strcat(fileContents, "-uh-"); 
				insertStatementChoice = 2;
			}
			else if (insertStatementChoice == 0) { 
				strcat(fileContents, "-um-"); 
				insertStatementChoice = 0;
			}
			y+=10;
			z+=6;
		}
		cout << "lettercount: " << letterCount << " ";
		z+=1;
		letterCount = 0;
		y+=1;
	}
	cout << endl;
	cout << "fileContents after -xx- addition:: " << fileContents << endl;*/
	
	//Replaces she to he.
	for (int i = 0; i < strlen(fileContents) + 1; i++) {
		herFileContents[y] = fileContents[i];
		if (fileContents[i] == ' ') {
			if (fileContents[i + 1] == 's') {
				if (fileContents[i + 2] == 'h') {
					if (fileContents[i + 3] == 'e') {
						if (fileContents[i + 4] == ' ') {
							cout << ">she found at index: " << i << endl;
							strcat(herFileContents, "her ");
							//length of what replaced with
							y+=4;
							//length of whats being replaced
							i+=4;
						}
					}
				}
			}
		}
		y+=1;
	}
	
	cout << "herFileContents after she -> her:: " << herFileContents << endl;

	//Replaces he to him.
	y = 0;
	for (int i = 0; i < strlen(herFileContents) + 1; i++) {
		himFileContents[y] = herFileContents[i];
		if (herFileContents[i] == ' ') {
			if (herFileContents[i + 1] == 'h') {
				if (herFileContents[i + 2] == 'e') {
					if (herFileContents[i + 3] == ' ') {
						cout << ">he found at index: " << i << endl;
						strcat(himFileContents, "him ");
						//length of what replaced with
						y+=4;
						//length of whats being replaced
						i+=3;
					}
				}
			}
		}
	y+=1;
	}
	
	cout << "himFileContents after he -> him:: " << himFileContents << endl;
	
	//Replaces is to are.
	y = 0;
	for (int i = 0; i < strlen(himFileContents) + 1; i++) {
		areFileContents[y] = himFileContents[i];
		if (himFileContents[i] == ' ') {
			if (himFileContents[i + 1] == 'i') {
				if (himFileContents[i + 2] == 's') {
					if (himFileContents[i + 3] == ' ') {
						cout << ">are found at index: " << i << endl;
						strcat(areFileContents, "are ");
						//length of what replaced with
						y+=4;
						//length of whats being replaced
						i+=3;
					}
				}
			}
		}
	y+=1;
	}
		
	cout << "areFileContents after is -> are:: " << areFileContents << endl;
	
	//Adds es to the ends of words that end in s
	y = 0;
	for (int i = 0; i < strlen(areFileContents) + 1; i++) {
		esFileContents[y] = areFileContents[i];
		if (areFileContents[i] == 's') {
			if (areFileContents[i + 1] == ' ') {
				cout << ">s  found at index: " << i << endl;
				strcat(esFileContents, "es ");
				//length of what replaced with
				y+=3;
				//length of whats being replaced
				i+=1;
			}
		}
	y+=1;
	}
		
	cout << "esFileContents after s  -> ses:: " << esFileContents << endl;

	//inserts a phrase at a random spot between words -_____-;;
	//0
	char fightEvil[20] = {"-- to fight evil --"}; 
	//1
	char governor[31] = {"-- that's what governors do --"};
    //2
	char patient[25] = {"-- I'm a patient man --"};
    //3
	char honor[28] = {"-- will honor the people --"};
    //4
	char mankind[38] = {"-- for the embetterment of mankind --"};
    //5
	char believe[21] = {"-- I believe it's --"};
    //6
	char they[29] = {"-- they misunderestimated --"};
    //7
	char first[29] = {"-- but first things first --"};
    //8
	char framework[36] = {"-- the framework, not groundwork --"};
    //9
	char diplomatic[40] = {"-- in the diplomatic nuanced circles --"};
    //10
	char mistake[31] = {"-- make no mistake about it --"};
		
	y = 0;
	//rand int 5-15
	int wordCounter = 0;
	int randPos = (rand() % 10) + 5;
	int randSay = (rand() % 11);
		for (int i = 0; i < strlen(esFileContents); i++) {
			wordCounter = 0;
			randPos = (rand() % 10) + 5;
			randSay = (rand() % 11);
			sayFileContents[y] = esFileContents[i];
			if (esFileContents[i] == ' ') {
				wordCounter+=1;
				if (wordCounter == randPos) {
					switch (randSay) {
					case 0:
						strcat(sayFileContents, fightEvil);
						y+=strlen(fightEvil);
						break;
					case 1:
						strcat(sayFileContents, governor);
						y+=strlen(governor);
						break;
					case 2:
						strcat(sayFileContents, patient);
						y+=strlen(patient);
						break;
					case 3:
						strcat(sayFileContents, honor);
						y+=strlen(honor);
						break;
					case 4:
						strcat(sayFileContents, mankind);
						y+=strlen(mankind);
						break;
					case 5:
						strcat(sayFileContents, believe);
						y+=strlen(believe);
						break;
					case 6:
						strcat(sayFileContents, they);
						y+=strlen(they);
						break;
					case 7:
						strcat(sayFileContents, first);
						y+=strlen(first);
						break;
					case 8:
						strcat(sayFileContents, framework);
						y+=strlen(framework);
						break;
					case 9:
						strcat(sayFileContents, diplomatic);
						y+=strlen(diplomatic);
						break;
					case 10:
						strcat(sayFileContents, mistake);
						y+=strlen(mistake);
						break;
					
					}
					
				}
			}
			y+=1;
		}
		cout << "sayFileContents:: " << sayFileContents << endl;
		toFile(outFile, sayFileContents);
	return;
}

int countInputStreamWords(char quote[]) {
	int wordCounter = 1;
	for (int i = 0; i < strlen(quote); i++) {
		if (quote[i] == ' ')
			wordCounter+=1;
	}
	/*if (wordCounter < 4)
		cout << "Input amount of words in quote is insufficient." << endl;*/
	return wordCounter;
}

void toFile(ofstream &outFile, char fileContents[]) {
	for (int i = 0; i < strlen(fileContents); i++)
	outFile << fileContents[i];
	cout << "Output file created successfully." << endl;
	return;
}

void toScreen(char fileContents[]) {
	cout << "The mangled quote is: " << endl;
	for (int i = 0; i < strlen(fileContents); i++) {
		cout << fileContents[i];
	}
	cout << endl;
	return;
}

/*********************************END OF FILE*********************************/
