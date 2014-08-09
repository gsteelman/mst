// file        : Field.h
// author      : Kate Holdener
// date        : November 8, 2007
// description : A Field class containing slugs, mines, and SlugBots.


#ifndef FIELD_H
#define FIELD_H

#include "defs.h"
#include <iostream>

using namespace std;

// definition of the Field class. A Field represents the "living space" for a slugbot

class Field
{
  public:
    // This constructor serves as a default constructor. It clears the field (putting
    //    empty space in each cell of the array), scatters slugs and mines.
    Field(const unsigned int numSlugs = 20,
          const unsigned int numMines = 0,
          const unsigned int size = 10);

    // Copy constructor      
    Field(const Field &f);
    
    // hasSlug     : verifies whether the field contains a slug at the
    //               specified location
    // pre         : none
    // post        : returns true if the specified location is whitin
    //               this Field and contains a slug, returns false otherwise
    //
    bool hasSlug(const Point &location);
    
    // hasMine     : verifies whether the field contains a mine at the
    //               specified location
    // pre         : none
    // post        : returns true if the specified location is whitin
    //               this Field and contains a mine, returns false otherwise
    bool hasMine(const Point &location);
    
    // getDim      : returns the dimension of the field
    inline int getDim(){return m_dim;}
    
    friend ostream& operator<<(ostream &out, const Field &f);

  private:
    int   m_dim;
    char  m_sector[MAX_DIM][MAX_DIM];
    int   m_numSlugs;
    int   m_numMines;

    // scatterslugs : scatters m_numSlugs in random fashion accross the field
    //                placing a char there that represents the slug
    // pre          : m_numSlugs must be less than number of cells in field
    void scatterSlugs();
    
    // scatterMines : scatters m_numMines in random fashion accross the field
    //                placing a char there that represents the mine
    // pre          : m_numMines must be less than number of cells in field
    void scatterMines();
    
    // clear        : places a char in each cell of the field that represents an empty location
    // pre          : none.
    // post         : each cell of m_sector has a special char in it representing an empty location
    void clear();
};

#endif
