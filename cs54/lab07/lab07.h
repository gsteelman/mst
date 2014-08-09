/* these next two lines wrap the header file
   wrapping a header file is a good practice
   and prevents the file from being included
   too many times */
#ifndef LAB07_H
#define LAB07_H

// Name: Gary Steelman
// Class and Section: CS 54, Section D
// Date: 10.10.07
// Purpose: To define the structs and functions for the toxic cookies

/* we include iostream and the namespace here
   now anything that includes lab06.h doesn't
   need to include this again */
   
#include <iostream>
#include <cmath>

using namespace std;

/* structs */
struct cookie
{
	double m_flour; /* in kg */
	double m_sugar; /* in kg */
	double m_butter; /* in kg */
	int m_eggs;
};

/* function prototypes */
//Gets input from the user for the amount of each ingredient for the cookies
//Then calculates and returns the amount of harm the cookies will do
double cookieHarm(cookie &recipe);

//Calculates the number of days eating these harmful cookies will take off
//of your life depending on the input recipe and the harm calculated from that
double cookieDays(cookie &recipe, double Harm);

//Calculates the number of days left in the person's life based on the recipe
//of the cookie and their age
double daysLeft(double Days);

//Length of a year in days
const float YEARLENGTH = 365.2425;

/* this line ends the if that began on line 5 */
#endif
