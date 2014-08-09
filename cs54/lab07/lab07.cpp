// Name: Gary Steelman
// Class and Section: CS 54, Section D
// Date: 10.10.07
// Purpose: To write functions that evaluate toxic cookies

// include the header file for this lab
#include "lab07.h"

// implement all the functions here

//Gets input from the user for the amount of each ingredient for the cookies
//Then calculates and returns the amount of harm the cookies will do
double cookieHarm(cookie &recipe) {

	double Harm = 0;
	
	do {
		cout << "Please enter the amount of flour used (in kg): ";
		cin >> recipe.m_flour;
	} while (recipe.m_flour < 0);
	
	do {
		cout << "Please enter the amount of butter used (in kg): ";
		cin >> recipe.m_butter;
	} while (recipe.m_butter < 0);
	
	do {
		cout << "Please enter the amount of sugar used (in kg): ";
		cin >> recipe.m_sugar;
	} while (recipe.m_sugar < 0);
	
	do {
		cout << "Please enter the amount of eggs used (whole number): ";
		cin >> recipe.m_eggs;
	} while (recipe.m_eggs < 0);
	
	Harm = sqrt(recipe.m_flour) + (((recipe.m_butter * pow(recipe.m_sugar,2)) / recipe.m_eggs));
	
	return Harm;
}

//Calculates the number of days eating these harmful cookies will take off
//of your life depending on the input recipe and the harm calculated from that
double cookieDays(cookie &recipe, double Harm) {

	double Days = 0;
	
	if (recipe.m_sugar == 0) { recipe.m_sugar = .01; }
	
	Days = (Harm * (((12 * recipe.m_eggs) + (3 * recipe.m_sugar)) / recipe.m_sugar));
	
	return Days;
}

//Calculates the number of days left in the person's life based on the recipe
//of the cookie and their age
double daysLeft(double Days) {
	
	double daysLeftAlive = 0;
	double age = 0;
	double batches = 0;
	
	do {
		cout << "\nIn order to calculate how long you have left to live, please";
		cout << "\ninput your age: ";
		
		cin >> age;
	} while (age < 0);
	
	do {
		cout << "\nAnd the number of batches of these cookies you have eaten";
		cout << "\nin your lifetime: ";
		
		cin >> batches;
	} while (batches < 0);
	
	daysLeftAlive = ((75 * YEARLENGTH) - (Days * batches));
	
	return daysLeftAlive;
}

