//BEGINNING OF FILE------------------------------------------------------------
/******************************************************************************
	Name: Gary Steelman
	Class and Section: CS53-D
	Date: 10.11.07
	Purpose: To write the main function for the gws4g2_hw6 quiz program
******************************************************************************/

//Includes the header file for this quiz program
#include "gws4g2_hw6.h"

int main()
{
	srand(time(NULL)); //Seeds the random number generator based on time
	
	int choice = 0; //The numerical value of the user's menu choice
	int points = 0; //The amount of points the user has, each corrent answer gets 1 point
	int stillGoYes = 1;
	
	do {
		problem current; //Creates the current math problem 
		
		greetUser(); //Greets the User
		
		choice = showMenu(); //Shows the menu
			
			//Quits the program if the user chose quit from the menu
			if (choice == 4) {
				goodbyeUser();
				return 0;
			}
			
		for (int i = 1; i <= 10; i++) {
			//Generates values for the current problem
			current = generateProblem(current, choice); 
			
			displayProblem(current); //Displays the current problem
			
			getAnswers(current, points); //Gets the user's answer for the problem
			
			displayPoints(points);
		}
		
		stillGoYes = stillGo();
		
	} while (stillGoYes == 1);
	
	goodbyeUser();
	
	return 0;
}

//END OF FILE------------------------------------------------------------------
