/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_Slug.h
//Purpose    : Includes the class Slug definition

#ifndef SLUG_H
#define SLUG_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "gws4g2_SlugBot.h"
#include "gws4g2_Field.h"
#include "gws4g2_Definitions.h"
#include "gws4g2_Mine.h"
#include "gws4g2_Slug.h"

class Slug {
public:
  /*Pre: none
    Post: creates a Slug with a certain amount of energy and fills an array 
      of strings with names read in from a file called "slugNames.txt" 
      slugNames.txt must be located in the same directory as this file*/
  Slug();
  
  //Makes the Field class be able to access the private members of Mine
  friend class Field;
  
  /*Pre: A slug object has been created
    Post: returns the amount of energy a slug will restore */
  //float getEnergy() const;
  
  /*Pre: low < high
    Post: returns a random float between the passed values */
  float randFloat(float low, float high);
  
  /*Pre: the file "slugNames.txt" has only 5 lines of names, 1 name on each 
      line. slugNames.txt is ine the same directory as this file 
    Post: fills the m_name array of the slug class with names from the file */
  void readSlugNames(string m_name[]);
  
  /*Pre: m_name has been filled with names for the slugs
    Post: chooses a random name from the array and outputs it */
  void outputSlugName(string m_name[]);
  
private:
  float m_energy; //The amount of energy the slug will restore
  string m_name[NUMSLUGNAMES]; //The list of names for the different slugs
};

#endif

/*********************************END OF FILE*********************************/
