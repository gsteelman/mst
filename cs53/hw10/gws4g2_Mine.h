/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_Mine.h
//Purpose    : Includes the class Mine definition

#ifndef MINE_H
#define MINE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "gws4g2_SlugBot.h"
#include "gws4g2_Field.h"
#include "gws4g2_Definitions.h"
#include "gws4g2_Mine.h"
#include "gws4g2_Slug.h"

class Mine {
public:
	/*Pre: none
    Post: creates a mine that will do a certain percent damage */
	Mine();
  
  //Makes the Field class be able to access the private members of Mine
  friend class Field;
	
private:
  //The amount of damage the mine will do
	float m_damage;
};

#endif

/*********************************END OF FILE*********************************/
