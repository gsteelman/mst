/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_SlugBot.cpp
//Purpose    : Includes the class SlugBot definition 

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "gws4g2_SlugBot.h"
#include "gws4g2_Field.h"
#include "gws4g2_Definitions.h"
#include "gws4g2_Mine.h"
#include "gws4g2_Slug.h"

//CONSTRUCTOR------------------------------------------------------------------
/*Pre: A Field object must have been declared and then passed to create
    the SlugBot
  Post: A SlugBot using the default values is declared */
SlugBot::SlugBot(const Field &f):m_field(f),m_energy(STARTINGENERGY){}

//FUNCTIONS--------------------------------------------------------------------
/*Pre: A slugbot object exists
  Post: Sets the Slugbot's energy to the passed value */
void SlugBot::setEnergy(const float &energy) {
	m_energy = energy;
	return;
}
/*Pre: A Field object exists and a struct Point with x and y integer values
    within must exist
  Post: Runs the simulation of the slugbot moving through the field */
void SlugBot::runSimulation() {
	//The bots starting location on the field
	Point loc = {0,0};
	
	//Runs the bot left to right if true (1), else right to left (0)
	int ltr = 1;
  
  //Puts the bot on the field and outputs the field
	m_field.m_field[loc.x][loc.y] = BOT;
  printField();
  
  /*Runs the bot starting on the top row headed to the right, then when the 
    bot hits the right, it drops down a row and heads back to the left */
	for (int i = 0; i < (m_field.m_fieldSize * m_field.m_fieldSize); i++) {
		//headed to the right
    if (ltr == 1) {
      //if we are in the far right column
			if ((loc.y + 1) == m_field.m_fieldSize) {
        //clears the spot the bot was just in
				m_field.m_field[loc.x][loc.y] = EMPTY;
				//drops it down a row
        loc.x+=1;
				ltr = 0;
				if (m_field.hasSlug(loc)) {
					//adds an amount of energy if there is a slug in the bot's spot
          m_energy+=m_field.getSlug();
				}
				if (m_field.hasMine(loc)) {
          //subtracts an amount of energy if there is a mine in the bot's spot
					m_energy-=(m_energy * m_field.getMine());
				}
				if (m_field.isEmpty(loc)) {
					//subtracts an amount of energy every time the bot takes a step
          m_energy-=m_field.getLoss();
				}
        //updates the location on the field with where the bot is
				m_field.m_field[loc.x][loc.y] = BOT;
			}
      //if we are not in the far right column
			else {
				m_field.m_field[loc.x][loc.y] = EMPTY;
				loc.y+=1;
				if (m_field.hasSlug(loc)) {
          m_energy+=m_field.getSlug();
				}
				if (m_field.hasMine(loc)) {
          m_energy-=(m_energy * m_field.getMine());
				}
				if (m_field.isEmpty(loc)) {
          m_energy-=m_field.getLoss();
				}
				m_field.m_field[loc.x][loc.y] = BOT;
				
			}
		}
    //if we are moving from right to left
		else if (ltr == 0) {
			if (loc.y == 0) {
				m_field.m_field[loc.x][loc.y] = EMPTY;
				loc.x+=1;
				ltr = 1;
				if (m_field.hasSlug(loc)) {
          m_energy+=m_field.getSlug();
				}
				if (m_field.hasMine(loc)) {
          m_energy-=(m_energy * m_field.getMine());
				}
				if (m_field.isEmpty(loc)) {
          m_energy-=m_field.getLoss();
				}
				m_field.m_field[loc.x][loc.y] = BOT;
			}
			else {
				m_field.m_field[loc.x][loc.y] = EMPTY;
				loc.y-=1;
				if (m_field.hasSlug(loc)) {
          m_energy+=m_field.getSlug();
				}
				if (m_field.hasMine(loc)) {
          m_energy-=(m_energy * m_field.getMine());
				}
				if (m_field.isEmpty(loc)) {
          m_energy-=m_field.getLoss();
				}
				m_field.m_field[loc.x][loc.y] = BOT;
			}
		}
    
    //Updates the field with the bot's location
    m_field.m_field[loc.x][loc.y] = BOT;
    
    //if the energy after this step is < 0, mission failed
    if (m_energy <= 0) {
      m_energy = 0;
      cout << "\tCurrent energy: " << m_energy << " cells" << endl;
      cout << endl;
      cout << "!-!-!Mission failure!-!-!" << endl;
      break;
    }
    
    //if the spot we are in is the final spot in the bottom on either side
      //mission successful
    if (loc.x == m_field.m_fieldSize && loc.y == 0 
      || loc.y == m_field.m_fieldSize && m_energy > 0) {
      cout << "\tCurrent energy: " << m_energy << " cells" << endl;
      cout << endl;
      cout << "-!-!-Mission successful-!-!-" << endl;
      break;
    }
    
    //Prints out the bot's current energy supply after each step
    cout << "\tCurrent energy: " << m_energy << " cells" << endl;
    
	}
	cout << endl;
	return;
}

/*********************************END OF FILE*********************************/
