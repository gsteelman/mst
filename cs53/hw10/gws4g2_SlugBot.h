/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_SlugBot.h
//Purpose    : Includes the class SlugBot definition 

#ifndef SLUGBOT_H
#define SLUGBOT_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "gws4g2_SlugBot.h"
#include "gws4g2_Field.h"
#include "gws4g2_Definitions.h"
#include "gws4g2_Mine.h"
#include "gws4g2_Slug.h"

class Field;

class SlugBot {
public:
	/*Pre: A Field object must have been declared and then passed to create
      the SlugBot
    Post: A SlugBot using the default values is declared */
	SlugBot(const Field &f);
	
	/*Pre: The << operator is defined for type Field
    Post: Outputs the bot's current energy and the field */
	void printField() {
		cout << "Current energy: " << m_energy << " cells" << endl;
		cout << m_field;
		return;
	}
	
	/*Pre: A Field object exists and a struct Point with x and y integer values
      within must exist
    Post: Runs the simulation of the slugbot moving through the field */
	void runSimulation();
	
	/*Pre: A slugbot object exists
    Post: Sets the Slugbot's energy to the passed value */
	void setEnergy(const float &energy);

private:
  //Creates a field for the slugbot to exist on
	Field m_field;
  
  //Creates a point for the location on the field of the slugbot
	Point m_location;
  
  //The amount of energy the slugbot has
	float m_energy;
};

#endif

/*********************************END OF FILE*********************************/
