/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 3 Dec 07
//File       : gws4g2_Field.cpp
//Purpose    : Includes the Field class functions

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
  Post: creates a Field with the starting values as indicated */
Field::Field(int slugs, int mines, int size) {
	m_numSlugs = slugs;
	m_numMines = mines;
	m_fieldSize = size;
	clearField();
	//added
	scatterSlugs();
	scatterMines();
}

//FUNCTIONS--------------------------------------------------------------------
/*Pre: A field object has a value at the passed point
  Post: returns whether or not the location has a slug in it */
bool Field::hasSlug(const Point &location)
{
	return (location.x < m_fieldSize && location.y < m_fieldSize && 
		m_field[location.x][location.y] == SLUG ? true : false);
}

/*Pre: A field object has a value at the passed point
  Post: returns whether or not the location has a mine in it */
bool Field::hasMine(const Point &location)
{
	return (location.x < m_fieldSize && location.y < m_fieldSize && 
		m_field[location.x][location.y] == MINE ? true : false);
}

/*Pre: A field object has a value at the passed point
  Post: returns whether or not the location is empty */
bool Field::isEmpty(const Point &location)
{
	return (location.x < m_fieldSize && location.y < m_fieldSize && 
		m_field[location.x][location.y] == EMPTY ? true : false);
}

/*Pre: None
  Post: Fills the field with blank spaces */
void Field::clearField() {
	for (int i = 0; i <= m_fieldSize; i++) {
		for (int j = 0; j <= m_fieldSize; j++) {
			m_field[i][j] = EMPTY;
		}
	}
	return;
}

/*Pre: None
  Post: Scatters the slugs on the field in random spots
  Note: Will not create a slug at position 0,0 */
void Field::scatterSlugs() {
	int randx = 0;
	int randy = 0;
	for (int i = 0; i < m_numSlugs; i++) {
		randx = (rand() % m_fieldSize);
		randy = (rand() % m_fieldSize);
		if (randx == 0 && randy == 0) {
			i-=1;
		}
		else if (m_field[randx][randy] == SLUG) {
			i-=1;
		}
		else
			m_field[randx][randy] = SLUG;
	}
	return;
}

/*Pre: None
  Post: Scatters the mines on the field in random spots that slugs do not
    already exist
  Note: Will not create a mine at position 0,0 */
void Field::scatterMines() {
	int randx = 0;
	int randy = 0;
	for (int i = 0; i < m_numMines; i++) {
		randx = (rand() % m_fieldSize);
		randy = (rand() % m_fieldSize);
		if (randx == 0 && randy == 0) {
			i-=1;
		}
		else if (m_field[randx][randy] == SLUG) {
			i-=1;
		}
		else if (m_field[randx][randy] == MINE) {
			i-=1;
		}
		else
			m_field[randx][randy] = MINE;
	}
	return;
}

/*Pre: A field object has been created
  Post: returns the length of one side of the field */
int Field::getFieldSize() const {
	return m_fieldSize;
}

/*Pre: A field object has been created
  Post: sets the size of one leg of the field to the passed value */
void Field::setFieldSize() {
	int fieldSize = 0;
	bool withinRange = false;
	do {
		cout << "Please enter the desired size of the field: ";
		cin >> fieldSize;
		if (fieldSize <= MAXFIELDSIZE && fieldSize > 0 )
			withinRange = true;
	} while (withinRange == false);
	m_fieldSize = fieldSize;
	clearField();
	return;
}

/*Pre: A field object has been created
  Post: sets the number of slugs to have on the field */
void Field::setNumSlugs() {
	int slugs = 0;
	bool withinRange = false;
	do {
		cout << "Please enter the desired number of slugs. This cannot " 
			<< "be more than " << ((m_fieldSize * m_fieldSize) - 1) << ": ";
		cin >> slugs;
		if (slugs <= ((m_fieldSize * m_fieldSize) - 1) && slugs >= 0)
			withinRange = true;
	} while (withinRange == false);
	m_numSlugs = slugs;
	scatterSlugs();
	return;
}

/*Pre: A field object has been created
  Post: sets the number of mines to have on the field */
void Field::setNumMines() {
	int mines = 0;
	bool withinRange = false;
	do {
		cout << "Please enter the desired number of mines. This cannot " 
			<< "be more than " << (((m_fieldSize * m_fieldSize) - m_numSlugs) - 1) << ": ";
		cin >> mines;
		if (mines <= (((m_fieldSize * m_fieldSize) - m_numMines) - 1) && mines >= 0)
			withinRange = true;
	} while (withinRange == false);
	m_numMines = mines;
	scatterMines();
	return;
}

/*Pre: A field object has been created
  Post: Outputs the field object */
ostream& operator<<(ostream &o, const Field &f) {
	o << "Field Stats: " << endl;
	o << "\tSize: " << f.m_fieldSize << " x " << f.m_fieldSize
	  << endl;
	o << "\tInitial Slugs: " << f.m_numSlugs << endl;
	o << "\tInitial Mines: " << f.m_numMines << endl;
	o << "The field of battle: " << endl;
	for (int i = 0; i < f.m_fieldSize; i++) {
		for (int j = 0; j < f.m_fieldSize; j++) {
			o << "|" << f.m_field[i][j];
		}
		cout << "|" << endl;
	}
	return o;
}

/*Pre: A field object has been created
  Post: returns the damage done by a mine */
float Field::getMine() const {
  Mine currMine;
	return currMine.m_damage;
}

/*Pre: A field object has been created
  Post: returns the energy gained by devouring a slug */
float Field::getSlug() const {
  Slug currSlug;
  return currSlug.m_energy;
}

/*Pre: A field object has been created
  Post: returns the amount of energy lost by taking a step in the field */
float Field::getLoss() const {
  cout << "--Energy from a step: " << ENERGYLOSSPERSTEP << endl;
  return ENERGYLOSSPERSTEP;
}

/*********************************END OF FILE*********************************/
