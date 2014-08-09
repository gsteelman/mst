// file        : SlugBot.h
// author      : Kate Holdener
// date        : November 8, 2007
// description : contains struct definitions and constants needed
//               for the slug bot program

#ifndef DEFS_H
#define DEFS_H

// constant to represent a slug object
const char SLUG = 's';

// constant to represent a mine object
const char MINE = 'm';

// constant to represent a slugbot object
const char BOT  = 'b';

// constant to represent an empty space
const char EMPTY = ' ';

// constant to represent where a mine used to be - maybe used later
const char EXPLOSION = 'X';

// constant for the maximum size  a field for the purposes of static memory declaration
const int  MAX_DIM = 100;

// constant for the initial energy of a slugbot
const float INIT_ENERGY=20;

// structure for a point (location in the field)
struct Point
{
  int m_x;
  int m_y;
};

#endif
