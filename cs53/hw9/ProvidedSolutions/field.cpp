// file        : Field.cpp
// author      : Kate Holdener
// date        : November 8, 2007
// description : implementation of the member functions of the Field class


#include "Field.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Field::Field(const unsigned int numSlugs;const unsigned int numMines,
             const unsigned int size):m_numSlugs(numSlugs),m_numMines(numMines),
             m_dim(size)
{
  // initialize the filed to be empty
  clear();
  //randomly scatter slugs
  scatterSlugs();
  //randomly scatter mines
  scatterMines();
}

// Copy constructor
Field::Field(const Field &f):
             m_numSlugs(f.m_numSlugs),
             m_numMines(f.m_numMines),
             m_dim(f.m_dim),
             m_start(f.m_start)
{
  for (int i=0; i< m_dim; i++)
	for(int j=0; j< m_dim; j++)
      m_sector[i][j] = f.m_sector[i][j];
}

// hasSlug     : verifies whether the field contains a slug at the
//               specified location
// pre         : none
// post        : returns true if the specified location is whitin
//               this Field and contains a slug, returns false otherwise
bool Field::hasSlug(const Point &loc)
{
  return (loc.m_x<m_dim && loc.m_y<m_dim && m_sector[loc.m_x][loc.m_y]==SLUG?true:false);
}

// hasMine     : verifies whether the field contains a mine at the
//               specified location
// pre         : none
// post        : returns true if the specified location is whitin
//               this Field and contains a mine, returns false otherwise
bool Field::hasMine(const Point &loc)
{
  return (loc.m_x<m_dim && loc.m_y<m_dim && m_sector[loc.m_x][loc.m_y]==MINE?true:false);
}

// clear        : places a char in each cell of the field that represents an empty cell
// pre          : none.
// post         : each cell of m_sector has a special char in it representing an empty cell
void Field::clear()
{
  for(int i=0; i<m_dim; i++)
  {
    for(int j=0; j<m_dim; j++)
    {
	  m_sector[i][j] = EMPTY;
	}
  }
}

// scatterslugs : scatters m_numSlugs in random fashion accross the field
//                placing a char there that represents the slug
// pre          : m_numSlugs must be less than number of cells in field
// post         : field has been populated with slugs        
void Field::scatterSlugs()
{
  int slugTotal = 0;
  int x,y;                     // location of slug to be placed

  while (slugTotal < m_numSlugs)
  {
    do
    {
      x = rand() % m_dim;
      y = rand() % m_dim;
    } while(m_sector[y][x]!=EMPTY || (x==m_start.m_x && y==m_start.m_y));
    m_sector[y][x] = SLUG;
    slugTotal++;
  }
}

// scatterMines : scatters m_numMines in random fashion accross the field
//                placing a char there that represents the mine
// pre          : m_numMines must be less than number of cells in field
// post         : mines are placed on the field            
void Field::scatterMines()
{
  int mineTotal = 0;
  int x,y;

  while (mineTotal < m_numMines)
  {
    do
    {
      x = rand() % m_dim;
      y = rand() % m_dim;
    } while(m_sector[y][x]!=EMPTY || (x==m_start.m_x && y==m_start.m_y));
    m_sector[y][x] = MINE;
    mineTotal++;
  }
}

ostream& operator<<(ostream &out, const Field &f)
{

  for(int j=0; j<=2*f.m_dim; j++)
  {
    out<<"-";
  }
  out<<endl;
  for(int i=0; i<f.m_dim; i++)
  {
	out<<"|";

    for(int j=0; j<f.m_dim; j++)
    {
	  out<<f.m_sector[i][j]<<"|";
	}
	out<<endl;
  }
  for(int j=0; j<=2*f.m_dim; j++)
  {
    out<<"-";
  }
  out<<endl;
}
