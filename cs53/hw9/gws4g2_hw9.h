/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 14 Nov 07
//File       : gws4g2_hw9.h
//Purpose    : To write the controlling header file for the hw9 project
	//This includes structs, variables, and function prototypes
	
#ifndef gws4g2_hw9_h
#define gws4g2_hw9_h

#include <iostream>
#include <cstdlib>
//#include "gws4g2_Field.h"
//#include "gws4g2_SlugBot.h"

using namespace std;

//GLOBAL VARIABLES-------------------------------------------------------------
const int MAXFIELDSIZE = 50;
const float MAXENERGY = 15000000;
const float STARTINGENERGY = 25;
const int STARTINGSLUGS = 20;
const int STARTINGMINES = 0;
const int STARTINGSIZE = 10;

//CLASSES----------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FIELD CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Field {
public:
	Field(int slugs = STARTINGSLUGS, int mines = STARTINGMINES
		, int size = STARTINGSIZE);

	friend class SlugBot;
	friend void printField(const SlugBot &s);
	void clearField();
	void setFieldSize();
	void setNumSlugs();
	void setNumMines();
	void scatterSlugs();
	void scatterMines();
	int getFieldSize() const;

private:
	int m_numSlugs;
	int m_numMines;
	int m_fieldSize;
	char m_field[MAXFIELDSIZE][MAXFIELDSIZE];
};

class Field;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SLUGBOT CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class SlugBot {
public:
	Field myField;
	float m_energy;
	SlugBot(float energy = STARTINGENERGY);
	
	void setSize();
	void getSize();
	void setSlug();
	void setMine();
	void setEnergy(const float &energy);
	
	friend ostream& operator<<(ostream &o, const SlugBot &s);

private:
};

//FUNCTION PROTOTYPES----------------------------------------------------------
//ostream& operator<<(ostream &o, const SlugBot &s);
void printField(const SlugBot &s);

#endif
	
/*********************************END OF FILE*********************************/
