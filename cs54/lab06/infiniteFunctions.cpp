/* Programmer: Dylan McDonald
   Class & Section: CS 54, Section <n>
   Date: 2 October 2007
   Purpose: Illustrate how functions call each other */

/* function prototypes */
void f(int x);
void g(int x);

int main()
{
  /* start the madness */
  f(0);
  return 0;
}

void f(int x)
{
  /* call g() again */
  g(x + 1);
}

void g(int x)
{
  /* call f() again */
  f(x + 1);
}
