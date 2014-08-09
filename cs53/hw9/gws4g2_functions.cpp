/******************************BEGINNING OF FILE******************************/
//Programmer : Gary Steelman
//Date       : 14 Nov 07
//File       : gws4g2_functions.cpp
//Purpose    : To write function implementation for the hw9 project
	
#include "gws4g2_hw9.h"

//CONSTRUCTORS-----------------------------------------------------------------
Field::Field(int slugs, int mines, int size) {
	m_numSlugs = slugs;
	m_numMines = mines;
	m_fieldSize = size;
	clearField();
}

SlugBot::SlugBot(float energy) {
	m_energy = energy;
	setSize();
	setSlug();
	setMine();
}

//FUNCTIONS--------------------------------------------------------------------
ostream& operator<<(ostream &o, const SlugBot &s) {
	printField(s);
	return o;
}

void printField(const SlugBot &s) {
	cout << "Field Stats: " << endl;
	cout << "\tSize: " << s.myField.m_fieldSize << " x " << s.myField.m_fieldSize
	  << endl;
	cout << "\tSlugs: " << s.myField.m_numSlugs << endl;
	cout << "\tMines: " << s.myField.m_numMines << endl;
	cout << "SlugBot Stats: " << endl;
	cout << "\tEnergy: " << s.m_energy << endl;
	cout << "The field of battle: " << endl;
	for (int i = 0; i < s.myField.m_fieldSize; i++) {
		for (int j = 0; j < s.myField.m_fieldSize; j++) {
			cout << "|" << s.myField.m_field[i][j];
		}
		cout << "|" << endl;
	}
	return;
}

void Field::clearField() {
	for (int i = 0; i <= m_fieldSize; i++) {
		for (int j = 0; j <= m_fieldSize; j++) {
			m_field[i][j] = ' ';
		}
	}
	return;
}

void Field::scatterSlugs() {
	int randx = 0;
	int randy = 0;
	for (int i = 0; i < m_numSlugs; i++) {
		randx = (rand() % m_fieldSize);
		randy = (rand() % m_fieldSize);
		if (m_field[randx][randy] == 's') {
			i-=1;
		}
		m_field[randx][randy] = 's';
	}
	return;
}

void Field::scatterMines() {
	int randx = 0;
	int randy = 0;
	for (int i = 0; i < m_numMines; i++) {
		randx = (rand() % m_fieldSize);
		randy = (rand() % m_fieldSize);
		if (m_field[randx][randy] == 's') {
			i-=1;
		}
		if (m_field[randx][randy] == 'm') {
			i-=1;
		}
		m_field[randx][randy] = 'm';
	}
	return;
}

int Field::getFieldSize() const {
	return m_fieldSize;
}

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

void Field::setNumSlugs() {
	int slugs = 0;
	bool withinRange = false;
	do {
		cout << "Please enter the desired number of slugs: ";
		cin >> slugs;
		if (slugs <= (m_fieldSize * m_fieldSize) && slugs >= 0)
			withinRange = true;
	} while (withinRange == false);
	m_numSlugs = slugs;
	scatterSlugs();
	return;
}

void Field::setNumMines() {
	int mines = 0;
	bool withinRange = false;
	do {
		cout << "Please enter the desired number of mines. This cannot " 
			<< "be more than " << ((m_fieldSize * m_fieldSize) - m_numSlugs) << ": ";
		cin >> mines;
		if (mines <= ((m_fieldSize * m_fieldSize) - m_numMines) && mines >= 0)
			withinRange = true;
	} while (withinRange == false);
	m_numMines = mines;
	scatterMines();
	return;
}

void SlugBot::setSize() {
	myField.setFieldSize();
	return;
}

void SlugBot::setSlug() {
	myField.setNumSlugs();
	return;
}

void SlugBot::setMine() {
	myField.setNumMines();
	return;
}

void SlugBot::setEnergy(const float &energy) {
	m_energy = energy;
	return;
}

void SlugBot::getSize() {
	myField.getFieldSize();
	return;
}
/*********************************END OF FILE*********************************/
