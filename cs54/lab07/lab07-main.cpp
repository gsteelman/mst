// Name: Gary Steelman
// Class and Section: CS 54, Section D
// Date: 10.10.07
// Purpose: To write functions that evaluate toxic cookies

// include the header file for this lab
#include "lab07.h"

int main()
{
	cookie recipe;
	double Harm = 0;
	double Days = 0;
	double daysLeftAlive = 0;
	
	/* ask the user to enter input & update the cookie struct
    make sure none of their inputs are negative */
	Harm = cookieHarm(recipe);

	/* display the results from cookieHarm() */
	cout << "\nThe harm calculated from the cookies is: " << Harm << endl;

	/*get the number of days the user has lost of their life based on
	the recipe from the cookie struct, makes sure amount of sugar is
	at least .01*/
	Days = cookieDays(recipe, Harm);
	
	/* display the results from cookieDays() */
	cout << "\nThe number of days that eating these cookies ";
	cout << "\nwill take off of your life for a single batch is: " << Days << endl;

	/*calculates the number of days left the user has to live*/
	daysLeftAlive = daysLeft(Days);
	
	/* display the results from daysLeft() */
	if (daysLeftAlive > 0) {
		cout << "\nAssuming that you live 75 years, you have: " << daysLeftAlive;
		cout << " days left to live, ";
		cout << "which is " << daysLeftAlive / YEARLENGTH << " years." << endl;
		
	}
	
	else {
		cout << "\nSadly, you've already eaten enough cookies to die.";
		cout << "\nGood night. DEATH BY COOKIE? SERIOUSLY? COME ON." << endl;
	}
	
	return 0;
}
