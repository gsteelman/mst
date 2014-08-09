//BEGINNING OF FILE------------------------------------------------------------
/******************************************************************************
	Name: Gary Steelman
	Class and Section: CS53-D
	Date: 10.11.07
	Purpose: To prototype the functions and write the structs for the 
		quiz program (hw6)
******************************************************************************/

//Prevents this header file from being included twice in the executable
#ifndef GWS4G2_Included
#define GWS4G2_Included
   
//INCLUDES---------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

//STRUCTURES------------------------------------------------------------------- 
//A problem for the quiz
struct problem
{
	int first; //First int in the problem
	int second; //Second int in the problem
	int operand; //The operation between them
};

//FUNCTION PROTOTYPES----------------------------------------------------------
/* greetUser() greets the user
Pre: None
Post: Outputs greeting to the user upon running the program */
void greetUser();

/* showMenu() shows the main menu to the user and gets their difficulty choice
Pre: None
Post: Outputs the main menu and returns the user's choice as an int value 
	1, 2, 3, or 4. */
int showMenu();

/* generateProblem(problem current, int choice) generates a random number
	between 2 given other integer
Pre: Must be passed a problem and a user choice for difficulty
Post: Returns a problem with generated numbers and an operation */
problem generateProblem(problem current, int choice);

/* displayProblem(problem current) displays the current problem 
Pre: Must be passed a problem that has intitialized values
Post: Displays the problem via cout to the user */
void displayProblem(problem current);

/* getAnswers(problem current) calculates the answer to the current problem
	and also gets the user's answer, checks to see if the user is right and
	if the user is, tallies a point
Pre: Must be passed a problem that has initialized values
Post: Tallies a point if the user answers the problem correctly */
void getAnswers(problem current, int &points);

/* displayPoints() displays the current points the user has accumulated
Pre: An int passed to the function
Post: Outputs the number of points to the screen */
void displayPoints(int &points);

/* stillGo() prompts the user as to whether or not to do another quiz
Pre: None
Post: Returns 1 for continue with another quiz, 0 for quit */
int stillGo();

/* goodbyeUser() says goodbye to the user
Pre: None
Post: Outputs goodbye upon user selecing 4 from the main menu */
void goodbyeUser();

//GLOBAL CONSTANTS AND VARIABLES-----------------------------------------------

//double cookieDays(cookie &recipe, double Harm);



//Ends the if statemnt from line 10 
#endif

//END OF FILE------------------------------------------------------------------
