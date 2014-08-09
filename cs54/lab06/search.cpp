/* Programmer: Dylan McDonald
   Class & Section: CS 54, Section <n>
   Date: 2 October 2007
   Purpose: Randomly search a search space & get close to a solution */

#include<cstdlib>
#include<iostream>
using namespace std;

int main()
{
  /* seed the random numbers */
  srand(time(NULL));

  /* randomly decide where to start searching */
  int searchPoint = rand() - rand();
  int endPoint = searchPoint * rand() % 10;

  /* for a positive search point, randomly get closer */
  while (searchPoint < endPoint)
  {
    /* good enough for government work */
    if ((abs(searchPoint - endPoint)) < 42)
    {
      cout << "We're close enough!" << endl;
      break;
    }

    /* randomly move on */
    searchPoint += rand() % 100;
  }
  return 0;
}
