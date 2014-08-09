/*****************************BEGINNING OF FILE*******************************/
//Gary Steelman
//CS53-D
//gws4g2_hw5.cpp - Homework 5
//10.3.07

//Includes:--------------------------------------------------------------------
#include <iostream>
#include <ctime>
#include <string>

//Which namespace to use:------------------------------------------------------
using namespace std;

//Structures:------------------------------------------------------------------
struct Professor {
	string m_name;
	int m_PubNum;
	int m_CommNum;
	float m_StuScore; 
	float m_Raise;
};

//Function Prototypes:---------------------------------------------------------
void greetings(); //Greets the user

string getname(); //Gets and returns the users name

char menu(); //Displays the menu and returns the user's choice

Professor act_on_choice(char c, Professor p); 
	/*Accepts the user's menu choice and then acts on it, being passed a
	professor object and then modifying it	then returning it; the switch case
	statement is here*/
	
Professor calc_raise(Professor p); //Calculates the raise and returns p

void display_raise(Professor p); //Displays the raise and the info it's based on

void goodbyes(); //Thanks the user for using
	
//Global Constants:------------------------------------------------------------
const short PubNumMax = 1000;
const short PubNumMin = 0;
const short ComNumMax = 50;
const short ComNumMin = 0;
const short StuScoreMax = 4;
const short StuScoreMin = 0;
const float PubMult = 0.4;
const float EvalMult = 0.45;
const float RandMult = 0.1;
const float CommMult = 0.05;

//The main function:-----------------------------------------------------------
int main() {
    //Creates a prof from Professor so we can use our Professor
	Professor prof;
	
    char choice = 'z';
    bool quit = false;
		    
	//Seeds the random number generator
	srand(time(NULL));                    
	
	//Sets the output of our couts to have 2 decimal precision
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);
	
    //Initializes the professor object we will use
	prof.m_name = "Frink";
	prof.m_PubNum = 0;
	prof.m_CommNum = 0;
	prof.m_StuScore = 0; 
	prof.m_Raise = 0;
	
	greetings();
	
    prof.m_name = getname();
	
	do {
        choice = menu();
		
        if (choice != 'q' && choice != 'Q') {
            prof = act_on_choice(choice,prof);
			
            if (choice == 'c' || choice == 'C')
                display_raise(prof);
        }
        
		else
			quit = true;
    } while (!quit);
    
	goodbyes();
    
	return 0;
}

//Greets the user--------------------------------------------------------------
void greetings() { 
	cout << "Welcome to the Pay Raise Calculator!" << endl; 
	
	return;
}

//Gets and returns the users name----------------------------------------------
string getname() {
	string name; //Local name entry, to be passed back
	
	cout << "Please enter your name: ";
	cin >> name;
	
	return name;
}

//Displays the menu and returns the user's choice------------------------------
char menu() {
	char choice; //Local menu choice entry, to be passed back
	cout << "\n\n ------Pay Raise Calculation Menu------ ";
	cout << "\n1.  (P)ublications (count)";
	cout << "\n2.  (S)ervice (number of committees)";
	cout << "\n3.  (E)valuation Score (student evaluations, 4.0 scale)";
	cout << "\n4.  (C)alculate Raise";
	cout << "\n5.  (Q)uit" << endl;
	cin >> choice;
	
	//Converts number menu choices to chars
	if (choice == '1') { choice = 'p'; }
	if (choice == '2') { choice = 's'; }
	if (choice == '3') { choice = 'e'; }
	if (choice == '4') { choice = 'c'; }
	if (choice == '5') { choice = 'q'; }

	return choice;
}

/*Accepts the user's menu choice and then acts on it, being passed a
professor object and then modifying it	then returning it; the switch case
statement is here*/
Professor act_on_choice(char c, Professor p) {
	short RandDart = 0; //The dart randomization for raise calculation
	
	switch (c) {
		//In the case of the first menu item, gets the number of publications
		case 'P':
		case 'p':
			do {
				cout << "How many publications do you have " << p.m_name << "? ";
				cin >> p.m_PubNum;
			} while (!(p.m_PubNum >= PubNumMin && p.m_PubNum <= PubNumMax));
		break;
		
		//In the case of the second menu item, gets the number of committees
		case 'S':
		case 's':
			do {
				cout << "How many service committees are you on " << p.m_name << "? ";
				cin >> p.m_CommNum;
			} while (!(p.m_CommNum >= ComNumMin && p.m_CommNum <= ComNumMax));
		break;
		
		//In the case of the third menu item, gets the student eval score
		case 'E':
		case 'e':
			do {
				cout << "What was your student evaluation score " << p.m_name << "? ";
				cin >> p.m_StuScore;
			} while (!(p.m_StuScore >= StuScoreMin && p.m_StuScore <= StuScoreMax));
		break;
			
		//In the case of the fourth menu item, calculates the raise
		case 'C':
		case 'c':
			RandDart = rand() % 11;
					
			p.m_Raise = (PubMult * p.m_PubNum) + (CommMult * p.m_CommNum) + (EvalMult * p.m_StuScore) + (RandMult * RandDart);
		break;
		
		default:
			cout << "Invalid input, please re-input.";
			break;
	}

	return p;
}

//Displays the raise and the info it's based on
void display_raise(Professor p) {

	cout << "Based on the following entered information:" << endl;
	cout << "Professor name:           " << p.m_name << endl;
	cout << "Number of publications:   " << p.m_PubNum << endl;
	cout << "Number of commmittees:    " << p.m_CommNum << endl;
	cout << "Student evaluation score: " << p.m_StuScore << endl;
	cout << "Your raise will be:       " << p.m_Raise << "%" << endl;
	
	return;
}

//Thanks the user for using----------------------------------------------------
void goodbyes() {
	cout << "Thank you for using the Pay Raise Calculator!" << endl;
	
	return;
}

/********************************END OF FILE**********************************/
