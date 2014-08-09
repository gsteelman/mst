//BEGINNING OF FILE------------------------------------------------------------
/******************************************************************************
	Name: Gary Steelman
	Class and Section: CS53-D
	Date: 10.11.07
	Purpose: To write function definitions for the gws4g2_hw6 quiz program
******************************************************************************/

//Includes the header file for this quiz program
#include "gws4g2_hw6.h"

/* greetUser() greets the user
Pre: None
Post: Outputs greeting to the user upon running the program */
void greetUser() {
	cout << "Hello! Welcome to the MathQuiz 2000 arithmetic quiz program!";

	return;
}

/* showMenu() shows the main menu to the user and gets their difficulty choice
Pre: None
Post: Outputs the main menu and returns the user's choice as an int value 
	1, 2, 3, or 4. */
int showMenu() {
	char choiceChar = 'z'; //User's choice from the main menu
	int choice = 0; //Converted value of user's choice into an easier int
	
	//Displays the main menu and prompts user for their choice of input
	cout << "\n\n\t---Select your difficuly level---";
	cout << "\n1. (E)asy (1 digit)";
	cout << "\n2. (M)oderate (2 digits)";
	cout << "\n3. (A)dvanced (4 digits)";
	cout << "\n4. (Q)uit";
	cout << "\nYou get two chances to answer each question correctly, good luck!";
	cout << "\nYour choice: ";
	cin >> choiceChar;
	
	//Switches on the user's choice and converts the input char to an int
	//Such that it can be easier worked with in other functions
	switch (choiceChar) {
		case '1':
		case 'E':
		case 'e':
			cout << "\nYou have selected easy difficulty." << endl;
			choice = 1;
			break;
		case '2':
		case 'M':
		case 'm':
			cout << "\nYou have selected moderate difficulty." << endl;
			choice = 2;
			break;
		case '3':
		case 'A':
		case 'a':
			cout << "\nYou have selected advanced difficulty." << endl;
			choice = 3;
			break;
		case 4:
		case 'Q':
		case 'q':
			cout << "\nYou have selected quit." << endl;
			choice = 4;
			break;
		default:
			cout << "\nMenu switch-case failed." << endl;
			break;
	}
	
	return choice;
}

/* generateProblem(problem current, int choice) generates a random number
	between 2 given other integer
Pre: Must be passed a problem and a user choice for difficulty
Post: Returns a problem with generated numbers and an operation */
problem generateProblem(problem current, int choice) {
	
	//The easy difficuly random number generation for 1-10
	if (choice == 1) {
		current.first = (rand() % 10) + 1; //Gives a random int 
		current.second = (rand() % 10) + 1; //Gives a random int 
		current.operand = rand() % 2; //Gives a random int from 0 to 1
	}
		
	//The moderate difficuly random number generation for 10-99
	if (choice == 2) {
		current.first = (rand() % 90) + 10; //Gives a random int  
		current.second = (rand() % 90) + 10; //Gives a random int 
		current.operand = rand() % 2; //Gives a random int from 0 to 1
	}
		
	//The advanced difficuly random number generation for 100-1000
	if (choice == 3) {
		current.first = (rand() % 900) + 100; //Gives a random int 
		current.second = (rand() % 900) + 100; //Gives a random int 
		current.operand = rand() % 2; //Gives a random int from 0 to 1
	}
	
	return current;
}

/* displayProblem(problem current) displays the current problem 
Pre: Must be passed a problem that has intitialized values
Post: Displays the problem via cout to the user */
void displayProblem(problem current) {
	cout << current.first;
	
	if (current.operand == 0)
		cout << " + ";
	else if (current.operand == 1)
		cout << " - ";
	else
		cout << " Error in displayProblem()";
	
	cout << current.second << " = ";

	return;
}

/* getAnswers(problem current) calculates the answer to the current problem
	and also gets the user's answer, checks to see if the user is right and
	if the user is, tallies a point
Pre: Must be passed a problem that has initialized values
Post: Tallies a point if the user answers the problem correctly */
void getAnswers(problem current, int &points) {
	int answer = 0;
	int userAnswer = 0;

	if (current.operand == 0) 
		answer = current.first + current.second;
	else if (current.operand == 1)
		answer = current.first - current.second;
	else
		cout << "Error calculating answer in getAnswers()";
	
	cin >> userAnswer;
	
	if (userAnswer == answer) {
		cout << "Good job! You got it right. +1 point!" << endl;
		++points;
	}
	else {
		cout << "Incorrect answer :( Try again!" << endl;
		cin >> userAnswer;
		
		if (userAnswer == answer) {
			cout << "Good job! You got it right. +1 point!" << endl;
			++points;
		}
		else 
			cout << "Incorrect answer. That was your second try. Next question:" << endl;
		}
	
	return;
}

/* displayPoints() displays the current points the user has accumulated
Pre: An int passed to the function
Post: Outputs the number of points to the screen */
void displayPoints(int &points) {
	cout << "Current points: " << points << endl;
	
	return;
}

/* stillGo() prompts the user as to whether or not to do another quiz
Pre: None
Post: Returns 1 for continue with another quiz, 0 for quit */
int stillGo() {
	char stillGoYes = 'z';
	int stillGoLol = 0;
	
	do {
		cout << "\nWould you like to take another quiz? y/n: ";
		cin >> stillGoYes;
	} while (stillGoYes == 'y' && stillGoYes == 'Y' && stillGoYes == 'n' && stillGoYes == 'N');
	//while (!(p.m_PubNum >= PubNumMin && p.m_PubNum <= PubNumMax));
	
	if (stillGoYes == 'Y' || stillGoYes == 'y')
		stillGoLol = 1;
	else if (stillGoYes == 'N' || stillGoYes == 'n')
		stillGoLol = 0;
	else
		cout << "Error in stillGo()" << endl;
	
	return stillGoLol;
}

/* goodbyeUser() says goodbye to the user
Pre: None
Post: Outputs goodbye upon user selecing 4 from the main menu */
void goodbyeUser() {
	cout << "Thank you for using the MathQuiz 2000 arithmetic quiz program!" << endl;

	return;
}

//END OF FILE------------------------------------------------------------------
