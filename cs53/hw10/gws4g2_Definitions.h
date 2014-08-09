/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_Definitions.h
//Purpose    : Includes the struct definitions and global constants necessary
	//For the SlugBot program

#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "gws4g2_SlugBot.h"
#include "gws4g2_Field.h"
#include "gws4g2_Definitions.h"

using namespace std;

//GLOBAL CONSTANTS-------------------------------------------------------------
//The constant to represent a slug object
const char SLUG = 's';

//The constant to represent a mine object
const char MINE = 'm';

//The constant to represent a slugbot object
const char BOT = 'b';

//The constant to represent where a mine used to be
const char CRATER = 'x';

//The constant to represent a blank spot on the map
const char EMPTY = ' ';

//The maximum energy the slugbot can have
const float MAXENERGY = 15000000;

//The starting energy for the slugbot
const float STARTINGENERGY = 25;

//The maximum field size for the field the slugbot is to exist in
const int MAXFIELDSIZE = 100;

//The number of slugs the field starts with when the constructor for the 
	//field class is called
const int STARTINGSLUGS = 20;

//The number of mines the field starts with when the constructor for the 
	//field class is called
const int STARTINGMINES = 0;

//The starting size of the field when the constructor for the field class
	//is called
const int STARTINGSIZE = 10;

//The number of names of different kinds of slugs the bot can devour
const int NUMSLUGNAMES = 5;

//The bounds for the amount of energy the slugs can give
const float USLUGENERGYBOUND = 4.5; //Upper bound
const float LSLUGENERGYBOUND = 3.5; //Lower bound

//The amount of energy the bot loses per blank space stepped on
const float ENERGYLOSSPERSTEP = 1.0;

//STRUCTURE DEFINITIONS--------------------------------------------------------
//Structure for a point (location on the field, 2 dimensional)
struct Point {
	//The x coordinate
	int x;
	//the y coordinate
	int y;
};
#endif

/*********************************END OF FILE*********************************/
