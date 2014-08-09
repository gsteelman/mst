//////////////////////////////////////////////////////////////////////
//@title rulesSystem.h
//@authors Dale Twombly (the best)
//         Michael Virag
//@brief The rules system variable adjustment header
//////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////////

  @function rulesSystem
  @pre    -
  @post   rulesSystem is created
  
//////////////////////////////////////////////////////////////////////

  @function rulesSystem
  @pre    - 
  @post   rulesSystem is created with passed values
  @param  filename is the filename to open to use as values for the
         rules system
  
//////////////////////////////////////////////////////////////////////

  @function ~rulesSystem
  @pre    - 
  @post   The rulesSystem class instance is destroyed
  
//////////////////////////////////////////////////////////////////////
  
  @function setDaysNotice
  @pre    The value being entered is an integer value (less than INTMAX)
  @post   The value for the new number of days notice required is
          set.
  @param  newDaysNotice is the new value for daysNotice
  @return True if change was successful

//////////////////////////////////////////////////////////////////////
  
  @function getDaysNotice 
  @return The value held for the number of days notice required

//////////////////////////////////////////////////////////////////////
  
  @function setDaysConsecutive
  @pre    The value being entered is an integer value (less than INTMAX)
  @post   The value held for the maximum number of days allowed
          consecutively is set
  @param  newDaysConsecutive is the new value for daysConsecutive
  @note   If the amount entered is -1, then there is no limit to days
          consecutive.
  @return True if change was successful

//////////////////////////////////////////////////////////////////////

  @function getDaysConsecutive
  @return The value held for the maximum number of days allowed
          consecutively 

//////////////////////////////////////////////////////////////////////
  
  @function setMaxPeopleOff
  @pre    The value being entered is an integer value (less than INTMAX)
  @post   The maximum number of people allowed to be off is set. 
  @param  newMaxPeopleOff is the new value for maxPeopleOff
  @note   A set value of -1 means there is no limit to the number of
          people who can be off at any given time.
  @return True if change was successful

//////////////////////////////////////////////////////////////////////
  
  @function getMaxPeopleOff 
  @return The maximum number of people allowed to be off
  @note   If the return is -1, that means there is no limit to the 
          number of people who can be off at any given time.

//////////////////////////////////////////////////////////////////////
  
  @function addBlackout
  @pre    The value being entered is in valid date format (mm/dd) and 
          is a valid date (no greater than 12/31)
  @post   The requested date is added to the list of blackout dates
  @param  blackoutDate is an additional string value to be 
          added to the vector
  @return True if the addition was successful.

//////////////////////////////////////////////////////////////////////
  
  @function removeBlackout
  @pre    The value added is on the list of dates
  @post   The value requested is removed from the list of blackout dates
  @param  blackoutDate is a string value to be 
          removed from the vector
  @return True if removal was successful

//////////////////////////////////////////////////////////////////////

  @function clearBlackout
  @pre    The list of dates is nonempty 
  @return True if clear was successful

//////////////////////////////////////////////////////////////////////

  @function isBlackout
  @pre    The value being entered is in valid date format (mm/dd) and 
          is a valid date (no greater than 12/31)
  @param  date is a string value that will be compared to all
          entries in the vector
  @return True if the date requested is a blackout date
  
//////////////////////////////////////////////////////////////////////

  @function getBlackoutList
  @pre    m_blackout is not empty 
  @return A vector of the blackout dates

//////////////////////////////////////////////////////////////////////

  @function printTo
  @pre    The filename entered is a usable filename (basic filename
          standards)
  @post   The rule set is dumped at the requested filename
  @param  filename is the name of the text file the variables
          and vector will be written to
  @return True if the dump was successful

//////////////////////////////////////////////////////////////////////

  @function loadFrom
  @pre    The filename entered is a usable filename (basic filename
          standards)
  @post   The rule set is loaded from the requested filename
  @param  filename is the name of the text file the variables
          and vector will be gathered from
  @return True if the load was successful

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

  @function findDate
  @pre    The value being entered is in valid date format (mm/dd) and 
          is a valid date (no greater than 12/31)
  @post   The location (if applicable) of the date in the blackout
          vector is found
  @param  The date to look for
  @note   Will return a -1 if date is not in the vector
  @return The location of the date in the vector

////////////////////////////////////////////////////////////////////*/

#ifndef RULESSYSTEM_H
#define RULESSYSTEM_H

///////////////////////////////////
///////////////////////////////////
// FOR TESTING PURPOSES ONLY //////
//  ERASE WHEN INCLUDED IN   //////
//        MAIN FILE!         //////
///////////////////////////////////
///////////////////////////////////
//                               //
#include <vector>                //
using std::vector;               //
//                               //
#include "..\library\file.h"     //
#include "..\library\library.h"  //
#include "..\library\strmanip.h" //
///////////////////////////////////

class rulesSystem {

  private:
    
    unsigned int    m_daysNotice; // = 14;
    unsigned int    m_daysConsecutive; // = 5;
    unsigned int    m_maxPeopleOff; // = -1;
    vector<string>  m_blackout;
    
    File m_filename;
                 
    // string format: "04/02" = April 2
    //                "mm/dd"

  public:

    rulesSystem();
    rulesSystem(string filename);
    ~rulesSystem();
    
    bool            setDaysNotice(unsigned int newDaysNotice);
    unsigned int    getDaysNotice();
    
    bool            setDaysConsecutive(unsigned int newDaysConsecutive);
    unsigned int    getDaysConsecutive();
    
    bool            setMaxPeopleOff(unsigned int newMaxPeopleOff);
    unsigned        getMaxPeopleOff();
    
    bool            addBlackout(string blackoutDate);
    bool            removeBlackout(string blackoutDate);
    bool            clearBlackout();
    bool            isBlackout(string date);
    vector<string>  getBlackoutList();
    
    bool            printTo(string filename);
    bool            loadFrom(string filename);
    
    int             findDate(string date);
    
    string          ruleFileName();
    
};

//#include "rulesSystem.hpp"

#endif
