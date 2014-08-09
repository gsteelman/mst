/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_Mine.cpp
//Purpose    : Includes the class Mine definition

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
/*Pre: none
  Post: creates a mine that will do a certain percent damage */
Mine::Mine() {
	int randDamage = rand() % 4;
	switch (randDamage) {
		case 0:
			m_damage = .25;
			break;
		case 1:
			m_damage = .50;
			break;
		case 2:
			m_damage = .75;
			break;
		case 3:
			m_damage = 1.00;
			break;
		default:
			cout << "Default case statement reached in mine. Error in code." << endl;
			m_damage = 0;
			break;
	}
  cout << "--Energy from a mine: " << (100 * m_damage) << "%!" << endl;
}

/*********************************END OF FILE*********************************/
