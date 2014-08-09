/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_main.cpp
//Purpose    : To write the driver for testing the Field and Slugbot classes
	
#include <iostream>
//#include <fstream>
#include <cmath>
#include <ctime>
#include "gws4g2_SlugBot.h"
#include "gws4g2_Field.h"
#include "gws4g2_Definitions.h"
#include "gws4g2_Mine.h"
#include "gws4g2_Slug.h"

int main() {
	float energy = 0; //Amount of energy the user wants the bot to have
	bool withinRange = false; //Boolean used to range-check the amount of energy
	srand(time(NULL)); //Seeds the random number generator
	
	Field myField; //Declares a default field
	
	SlugBot defaultBot(myField); //Declares a default slugbot
	
	//Sets the user defined parameters for the field
	myField.setFieldSize();
	myField.setNumSlugs();
	myField.setNumMines();
	
	//Creates a bot using the user defined field
	SlugBot bot(myField);
	
	//Asks for, range checks and then assigns the user-input amount of energy
    //into the slugbot
	do {
		cout << "The max energy the SlugBot can have is: " << MAXENERGY
			<< " cells." << endl;
		cout << "Please enter the desired amount of energy (cells): ";
		cin >> energy;
		if (energy <= MAXENERGY && energy >= 0)
			withinRange = true;
	} while (withinRange == false);
	bot.setEnergy(energy);
	withinRange = false;
	
	//Prints out the user created SlugBot
	bot.printField();
	
	//Runs the simulation for the SlugBot
	bot.runSimulation();
	
	//Prints out the bot stats after the simulation has been run
  cout << "The final field of battle: " << endl;
	bot.printField();
	
	return 0;
}
		
/*********************************END OF FILE*********************************/
