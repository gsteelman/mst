//////////////////////////////////////////////////////////////////////
//@title rulesSystem.hpp
//@authors Dale Twombly (the best)
//         Michael Virag
//@brief The rules system variable adjustment functions
//////////////////////////////////////////////////////////////////////

#include "rulesSystem.h"

////////////////////////////////////////////////////////////////////
//
//@function rulesSystem
//@pre    -
//@post   rulesSystem is created
//
//////////////////////////////////////////////////////////////////////

rulesSystem::rulesSystem()
{

  //For this one, the default rule set will be loaded
  
  //TEMPORARY COMMENT OUT PLEASE FIX
  //m_filename.open("data\default.ruleset");
  
  //loadFrom(ruleFileName());


}

//////////////////////////////////////////////////////////////////////
/*
  @function rulesSystem
  @pre    - 
  @post   rulesSystem is created with passed values
  @param  filename is the filename to open to use as values for the
         rules system
*/
//////////////////////////////////////////////////////////////////////

rulesSystem::rulesSystem(string filename)
{

  loadFrom(filename);

  /*if (m_filename.error()) {

    throw Exception(30,"Unable to open file " + m_filename.get_filename() + ". (class rulesSystem, rulesSystem(string))");
  
  }*/

}

//////////////////////////////////////////////////////////////////////
/*
  @function ~rulesSystem
  @pre    - 
  @post   The rulesSystem class instance is destroyed
*/
//////////////////////////////////////////////////////////////////////

rulesSystem::~rulesSystem()
{

  

}

////////////////////////////////////////////////////////////////////
/*
  @function setDaysNotice
  @pre    The value being entered is an integer value (less than INTMAX)
  @post   The value for the new number of days notice required is
          set.
  @param  NewdaysNotice is the new value for daysNotice
  @return True if change was successful
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::setDaysNotice(unsigned int newDaysNotice)
{
 
  m_daysNotice = newDaysNotice;
  
  return (m_daysNotice == newDaysNotice);
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function getDaysNotice 
  @return The value held for the number of days notice required
*/
//////////////////////////////////////////////////////////////////////

unsigned int rulesSystem::getDaysNotice()
{
  
  return m_daysNotice;
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function setDaysConsecutive
  @pre    The value being entered is an integer value (less than INTMAX)
  @post   The value held for the maximum number of days allowed
          consecutively is set
  @param  newDaysConsecutive is the new value for daysConsecutive
  @note   If the amount entered is -1, then there is no limit to days
          consecutive.
  @return True if change was successful
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::setDaysConsecutive(unsigned int newDaysConsecutive)
{

  m_daysConsecutive = newDaysConsecutive;
  
  return (m_daysConsecutive == newDaysConsecutive);
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function getDaysConsecutive
  @return The value held for the maximum number of days allowed
          consecutively 
*/
//////////////////////////////////////////////////////////////////////

unsigned int rulesSystem::getDaysConsecutive()
{
  
  return m_daysConsecutive;
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function setMaxPeopleOff
  @pre    The value being entered is an integer value (less than INTMAX)
  @post   The maximum number of people allowed to be off is set. 
  @param  newMaxPeopleOff is the new value for maxPeopleOff
  @note   A set value of -1 means there is no limit to the number of
          people who can be off at any given time.
  @return True if change was successful
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::setMaxPeopleOff(unsigned int newMaxPeopleOff)
{
  
  m_maxPeopleOff = newMaxPeopleOff;
  
  return (m_maxPeopleOff == newMaxPeopleOff);
  
}

//////////////////////////////////////////////////////////////////////
/*  
  @function getMaxPeopleOff 
  @return The maximum number of people allowed to be off
  @note   If the return is -1, that means there is no limit to the 
          number of people who can be off at any given time.
*/
//////////////////////////////////////////////////////////////////////

unsigned int rulesSystem::getMaxPeopleOff()
{

  return m_maxPeopleOff;
  
}

//////////////////////////////////////////////////////////////////////
/*  
  @function addBlackout
  @pre    The value being entered is in valid date format (mm/dd) and 
          is a valid date (no greater than 12/31)
  @post   The requested date is added to the list of blackout dates
  @param  blackoutDate is an additional string value to be 
          added to the vector
  @return True if the addition was successful.
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::addBlackout(string blackoutDate)
{

  //To prevent duplicates, it checks if the date is already 
  if (!isBlackout(blackoutDate)) {
  
    m_blackout.push_back(blackoutDate);
    
    //Now sort the data for easy usage
    
    insertion_sort(m_blackout);
  
    return (m_blackout.back() == blackoutDate);

  }

  return false;
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function removeBlackout
  @pre    The value added is on the list of dates
  @post   The value requested is removed from the list of blackout dates
  @param  blackoutDate is a string value to be 
          removed from the vector
  @return True if removal was successful
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::removeBlackout(string blackoutDate)
{
  
  int position = findDate(blackoutDate);
  
  if (position != -1 && !m_blackout.empty()) {
	
      //Since begin() will start at 0, position needs to be
      //decremented to erase the proper entry

      //position -= 1;

      m_blackout.erase(m_blackout.begin() + position);
      
      //Good escape because it was erased
      
      return true;
    
  }
  
  //Not found, so no remove
  return false;
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function clearBlackout
  @pre    The list of dates is nonempty 
  @return True if clear was successful
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::clearBlackout()
{
  
  if (!m_blackout.empty()) {

    m_blackout.clear();
    
    return true;
    
  } else {
  
    return false;
    
  }
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function isBlackout
  @pre    The value being entered is in valid date format (mm/dd) and 
          is a valid date (no greater than 12/31)
  @param  date is a string value that will be compared to all
          entries in the vector
  @return True if the date requested is a blackout date
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::isBlackout(string date)
{
  
  //Since findDate returns a -1 if it is not on the list, this is
  //an easy thing to check for
  
  return (findDate(date) != -1);
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function getBlackoutList
  @pre    m_blackout is not empty 
  @return A vector of the blackout dates
*/
//////////////////////////////////////////////////////////////////////

vector<string> rulesSystem::getBlackoutList()
{

  return m_blackout;
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function printTo
  @pre    The filename entered is a usable filename (basic filename
          standards)
  @post   The rule set is dumped at the requested filename
  @param  filename is the name of the text file the variables
          and vector will be written to
  @return True if the dump was successful
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::printTo(string filename)
{

  m_filename.open(filename);
  
  //The strings holding the data must be converted to integers
  m_filename.insert_line(m_filename.num_lines(), int_to_str(m_daysNotice));
  m_filename.insert_line(m_filename.num_lines(), int_to_str(m_daysConsecutive));
  m_filename.insert_line(m_filename.num_lines(), int_to_str(m_maxPeopleOff));
  
  m_filename.insert_line(m_filename.num_lines(), "START BLACKOUT LIST");
  m_filename.insert_lines(m_filename.num_lines(), m_blackout);
  m_filename.insert_line(m_filename.num_lines(), "END BLACKOUT LIST");
  
  m_filename.save_file(filename);
  
  return (!m_filename.error());

}

//////////////////////////////////////////////////////////////////////
/*
  @function loadFrom
  @pre    The filename entered is a usable filename (basic filename
          standards)
  @post   The rule set is loaded from the requested filename
  @param  filename is the name of the text file the variables
          and vector will be gathered from
  @return True if the load was successful
*/
//////////////////////////////////////////////////////////////////////

bool rulesSystem::loadFrom(string filename)
{
  
  unsigned int linepos = 0;
  string linecheck;
  
  //Reload the file just in case it wasn't loaded before

  m_filename.open(filename);
  
  m_daysNotice = str_to_int(m_filename[linepos]);
    linepos++;
  
  m_daysConsecutive = str_to_int(m_filename[linepos]);
    linepos++;
  
  m_maxPeopleOff = str_to_int(m_filename[linepos]);
    linepos += 2;

  linecheck = m_filename[linepos];

  do
  {
  
    addBlackout(linecheck);
    
    linepos++;

    linecheck = m_filename[linepos];
    
  } while(linecheck != "END BLACKOUT LIST");

  return true;
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function findDate
  @pre    The value being entered is in valid date format (mm/dd) and 
          is a valid date (no greater than 12/31)
  @post   The location (if applicable) of the date in the blackout
          vector is found
  @param  The date to look for
  @note   Will return a -1 if date is not in the vector
  @return The location of the date in the vector, if not in vector
          will throw an exception
*/
//////////////////////////////////////////////////////////////////////

int rulesSystem::findDate(string date)
{

  for (short currPos = 0; currPos < m_blackout.size(); currPos += 1) {
  
    if (m_blackout[currPos] == date) {
    
      //Positive result, returning the position of the value
      
      return currPos;
      
    }
    
  }
  
  //Negative result
  
  return -1;
  
}

/*
ROUGH FILE FORMAT OUTLINE: (not confirmed or approved, just thoughts)
**Note: Items in < > are actual values, the <> are not to be there!**

//////////////////////////

<m_daysNotice>
<m_daysConsecutive>
<m_maxPeopleOff>

START
<blackout_1>
<blackout_2>
...
<blackout_n>
END

//////////////////////////

Basically, the vector is laid out one by one between the START and END
text.

*/

//////////////////////////////////////////////////////////////////////
/*
  @function ruleFileName
  @pre we are using a rules file with a name
  @return The name of the rule file currently being used is returned
*/
//////////////////////////////////////////////////////////////////////

string rulesSystem::ruleFileName()
{
  
  return m_filename.get_filename();
  
}