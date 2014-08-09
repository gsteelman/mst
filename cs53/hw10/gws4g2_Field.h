/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_Field.h
//Purpose    : Includes the class Field definition 

#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "gws4g2_SlugBot.h"
#include "gws4g2_Field.h"
#include "gws4g2_Definitions.h"
#include "gws4g2_Mine.h"
#include "gws4g2_Slug.h"

class Field {
public:
	//Gives the SlugBot class access to the Field class' members
	friend class SlugBot;
	
	/*Pre: none
    Post: creates a Field with the starting values as indicated */
	Field(int slugs = STARTINGSLUGS, 
				int mines = STARTINGMINES,
			  int size = STARTINGSIZE);
				
	/*Pre: A field object has a value at the passed point
    Post: returns whether or not the location has a slug in it */
	bool hasSlug (const Point &location);
	
	/*Pre: A field object has a value at the passed point
    Post: returns whether or not the location has a mine in it */
	bool hasMine (const Point &location);
	
	/*Pre: A field object has a value at the passed point
    Post: returns whether or not the location is empty */
	bool isEmpty(const Point &location);
	
	/*Pre: A field object has been created
    Post: Outputs the field object */
	friend ostream& operator<<(ostream &o, const Field &f);
	
	/*Pre: A field object has been created
    Post: returns the length of one side of the field */
	int getFieldSize() const;
  
  /*Pre: A field object has been created
    Post: returns the damage done by a mine */
  float getMine() const;
  
  /*Pre: A field object has been created
    Post: returns the energy gained by devouring a slug */
  float getSlug() const;

  /*Pre: A field object has been created
    Post: returns the amount of energy lost by taking a step in the field */
  float getLoss() const;
  
	/*Pre: A field object has been created
    Post: sets the size of one leg of the field to the passed value */
	void setFieldSize();
  
	/*Pre: A field object has been created
    Post: sets the number of mines to have on the field */
	void setNumMines();
  
  /*Pre: A field object has been created
    Post: sets the number of slugs to have on the field */
	void setNumSlugs();
	
private:
	int m_numSlugs; //The number of slugs on the field
	int m_numMines; //The number of mines on the field
	int m_fieldSize; //The length of one side of the field
	char m_field[MAXFIELDSIZE][MAXFIELDSIZE]; //The field representation
	
	/*Pre: None
    Post: Scatters the slugs on the field in random spots
    Note: Will not create a slug at position 0,0 */
	void scatterSlugs();
  
	/*Pre: None
    Post: Scatters the mines on the field in random spots that slugs do not
      already exist
    Note: Will not create a mine at position 0,0 */
	void scatterMines();
  
	/*Pre: None
    Post: Fills the field with blank spaces */
	void clearField();

};

#endif

/*********************************END OF FILE*********************************/
