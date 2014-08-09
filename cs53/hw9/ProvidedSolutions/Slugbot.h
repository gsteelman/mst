// file        : SlugBot.h
// author      : Kate Holdener
// date        : November 8, 2007
// description : A SlugBot class definition

#ifndef SLUG_BOT_H
#define SLUG_BOT_H

#include "Field.h"
#include "defs.h"

// class definition for a slug eatin' robot

class SlugBot
{
  public:

    // Constructor that takes a field object
    SlugBot(const Field &f);

    void printField(ostream& o){o<<"energy = "<<m_energy<<endl;o<<m_field;}

  private:
    float m_energy;
//    Point m_location;      //you'll need this in the future
    Field m_field;
};

#endif


