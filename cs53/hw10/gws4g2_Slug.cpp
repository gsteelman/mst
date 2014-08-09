/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_Slug.cpp
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
  Post: creates a Slug with a certain amount of energy and fills an array 
    of strings with names read in from a file called "slugNames.txt" 
    slugNames.txt must be located in the same directory as this file*/
Slug::Slug() {
  //gets a random energy level
  m_energy = randFloat(LSLUGENERGYBOUND, USLUGENERGYBOUND);
  cout << "++Energy from a slug: " << m_energy << endl;
  
  //reads slug names from file
  readSlugNames(m_name);
  
  //outputs a random slug name
  outputSlugName(m_name);
}

//FUNCTIONS--------------------------------------------------------------------
/*Pre: low < high
  Post: returns a random float between the passed values */
float Slug::randFloat(float low, float high) {
  float temp;
  temp = (rand() / (static_cast<float>(RAND_MAX) + 1.0))
       * (high - low) + low;
  return temp;
}

/*Pre: the file "slugNames.txt" has only 5 lines of names, 1 name on each 
    line. slugNames.txt is ine the same directory as this file 
  Post: fills the m_name array of the slug class with names from the file */
void Slug::readSlugNames(string m_name[]) {
  ifstream i;
  i.open("slugNames.txt");
  
  int j = 0;
	while (!i.eof()) {
    if (i.eof()) { break; }
    i >> m_name[j];
    j++;
  }
  
  i.close();
	
	return;
}

/*Pre: m_name has been filled with names for the slugs
  Post: chooses a random name from the array and outputs it */
void Slug::outputSlugName(string m_name[]) { 
  int i = rand() % 5;
  cout << "Bot devours a slug named " << m_name[i] << endl;
  return;
}

/*********************************END OF FILE*********************************/
