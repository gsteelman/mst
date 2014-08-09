/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 14 Nov 07
//File       : gws4g2_main.cpp
//Purpose    : To write the driver for testing the Field and Slugbot classes
	
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "gws4g2_SlugBot.h"
#include "gws4g2_Field.h"
#include "gws4g2_Definitions.h"

int main() {
	float energy = 0;
	int size = 0;
	int numSlugs = 0;
	int numMines = 0;
	bool withinRange = false;
	
	srand(time(NULL));
	
	SlugBot bot;

	do {
		cout << "The max energy the SlugBot can have is: " << MAXENERGY << endl;
		cout << "Please enter the desired amount of energy: ";
		cin >> energy;
		if (energy <= MAXENERGY && energy >= 0)
			withinRange = true;
	} while (withinRange == false);
	bot.setEnergy(energy);
	withinRange = false;
	
	bot.printField();
	
	return 0;
}
		
/*********************************END OF FILE*********************************/
