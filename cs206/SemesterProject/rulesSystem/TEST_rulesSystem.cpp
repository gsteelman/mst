//////////////////////////////////////////////////////////////////////
//@title TEST_rulesSystem.cpp
//@authors Dale Twombly (the best)
//         Michael Virag
//@brief The rules system variable adjustment test
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/*
  @function test_daysNotice
  @return True if testing worked properly
*/
//////////////////////////////////////////////////////////////////////

bool test_daysNotice()
{

  unsigned int newVal = 25;

  rulesSystem testSystem;

  return (testSystem.setDaysNotice(newVal) && 
         (testSystem.getDaysNotice() == newVal));
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function test_daysConsecutive
  @return True if testing worked properly
*/
//////////////////////////////////////////////////////////////////////

bool test_daysConsecutive()
{
  unsigned int newVal = 25;

  rulesSystem testSystem;
  
  return (testSystem.setDaysConsecutive(newVal) && 
         (testSystem.getDaysConsecutive() == newVal));
  

}

//////////////////////////////////////////////////////////////////////
/* 
  @function test_maxPeopleOff 
  @return True if testing worked properly
*/
//////////////////////////////////////////////////////////////////////

bool test_maxPeopleOff()
{

  unsigned int newVal = 25;

  rulesSystem testSystem;
    
  return (testSystem.setMaxPeopleOff(newVal) && 
         (testSystem.getMaxPeopleOff() == newVal));
  
}

//////////////////////////////////////////////////////////////////////
/*  
  @function test_blackout
  @return True if testing worked properly
*/  
//////////////////////////////////////////////////////////////////////

bool test_blackout()
{
 
  string newStr = "04/01";

  bool success = false;

  rulesSystem testSystem;

  //Test of addBlackout is to add an element then make sure
  //it exists, then adding a second element, then finally
  //attempting to add a second copy of the first element
    
  success = testSystem.addBlackout(newStr) == true;

  success = success && (testSystem.findDate(newStr) == 0)
                    && (testSystem.addBlackout("04/02") == true)
                    && (testSystem.addBlackout(newStr) == false);

  //Test of removeBlackout is to remove all elements

  success = success && (testSystem.removeBlackout(newStr) == true)
                    && (testSystem.removeBlackout("04/02") == true);
  
  //Attempt a final remove, which should obviously fail
  
  success = success && (testSystem.removeBlackout(newStr) == false);
  
  //Test of isBlackout is to fill the list with some dates and make sure
  //each one is adequately noted as a blackout date (while throwing bad
  //dates as well to test both sides)
  
  //Makes it easier to just load a premade ruleset with some dates
  
  testSystem.loadFrom("test.ruleset");
  
  //Big chain of dates to check for, including some red herrings
  
  success = success && (testSystem.isBlackout("01/01") == true)
                    && (testSystem.isBlackout("01/13") == false)
                    && (testSystem.isBlackout("02/09") == false)
                    && (testSystem.isBlackout("02/13") == true)
                    && (testSystem.isBlackout("05/19") == true)
                    && (testSystem.isBlackout("11/11") == false)
                    && (testSystem.isBlackout("11/26") == true)
                    && (testSystem.isBlackout("12/10") == false)
                    && (testSystem.isBlackout("12/25") == true)
                    && (testSystem.isBlackout("12/31") == true)
                    && (testSystem.isBlackout("13/31") == false);
                    
  return success;
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function test_getBlackoutList
  @return True if testing worked properly
*/
//////////////////////////////////////////////////////////////////////

bool test_getBlackoutList()
{

  vector<string> list;
  bool success;

  rulesSystem testSystem("test.ruleset");

  list = testSystem.getBlackoutList();
  
  success = list.size() == 7;

  //Make sure the read-in values is what is to be expected
  //and that everything was sorted properly

  success = success && (list[0] == "01/01");
  success = success && (list[1] == "02/13");
  success = success && (list[2] == "05/19");
  success = success && (list[3] == "07/20");
  success = success && (list[4] == "11/26");
  success = success && (list[5] == "12/25");
  success = success && (list[6] == "12/31");

  return success;
  
}

//////////////////////////////////////////////////////////////////////
/*
  @function test_printTo
  @return True if testing worked properly
*/
//////////////////////////////////////////////////////////////////////

bool test_printTo();
{

  rulesSystem testSystem;
  rulesSystem testSystem2;

  bool success = false;

  //Assuming that the loadFrom function is working properly

  testSystem.loadFrom("printToTest.ruleset");

 
 testSystem.printTo("printToTest_b.ruleset");

  //Now load the second one in for value-to-value comparisons of the two rule systems

  testSystem2.loadFrom("printToTest_b.ruleset");

  success =            (testSystem.getDaysNotice() == testSystem2.getDaysNotice());
  success = success && (testSystem.getDaysConsecutive() == testSystem2.getDaysConsecutive());
  success = success && (testSystem.getMaxPeopleOff() == testSystem2.getMaxPeopleOff());
  success = success && (testSystem.getBlackoutList() == testSystem2.getBlackoutList());
 
  success = success && (testSystem.ruleFileName() != testSystem2.ruleFileName());

  return success;

}

//////////////////////////////////////////////////////////////////////
/*
  @function test_loadFrom
  @return True if testing worked properly
*/
//////////////////////////////////////////////////////////////////////

bool test_loadFrom()
{

   bool success = true;
   
   //loads the rules for testing
   testSystem.loadFrom("test.ruleset");
   
   //verifies the info read from the file is what it's supposed to be
   success = success && (getDaysNotice() == 14);
   success = success && (getDaysConsecutive() == 5);
   success = success && (getMaxPeopleOff() == -1);
   success = success && test_getBlackoutList();
   
   return success;

}

//////////////////////////////////////////////////////////////////////
/*  
  @function test_findDate
  @return True if testing worked properly
*/  
////////////////////////////////////////////////////////////////////*/

bool test_findDate()
{

  rulesSystem testSystem;
  
  bool success = false;

  //Testing the insertion_sort working properly for the values entered

  testSystem.addBlackout("01/02");

  success = testSystem.findDate("01/02") == 0;

  testSystem.addBlackout("01/01");
  
  success = success && (testSystem.findDate("01/01") == 0);
  success = success && (testSystem.findDate("01/02") == 1);

  testSystem.addBlackout("12/31");

  success = success && (testSystem.findDate("01/01") == 0);
  success = success && (testSystem.findDate("01/02") == 1);
  success = success && (testSystem.findDate("12/31") == 2);

  success = success && (testSystem.findDate("05/15") == -1);

  return success;

}



