/* Programmer: Dylan McDonald
   Class & Section: CS 54, Section <n>
   Date: 2 October 2007
   Purpose: Watch a faulty elevator fall to the ground */

int main()
{
  /* well known (and not so well known) physical constants */
  const double GRAVITY = 9.80665;
  const double TIME_STEP = .1;
  const double ROOM_HEIGHT = 42 * 3.2;
  const double DRAG_CONSTANT = 7.008;

  /* variables for the implementation of the fall */
  double mass = 420.346;
  double acceleration, fallTime = 0.0;
  double currVelocity, currDisplacement = 0.0;
  double prevVelocity = 0.0, prevDisplacement = 0.0;

  /* now watch it fall - wheeee! */
  while (currDisplacement < ROOM_HEIGHT)
  {
    /* calculate our current three */
    acceleration = ((mass * GRAVITY)
                 - (DRAG_CONSTANT * prevVelocity * prevVelocity)) / mass;
    currVelocity = prevVelocity + acceleration * TIME_STEP;
    currDisplacement = prevDisplacement + currVelocity * TIME_STEP;

    /* save them as our previous three & advance time */
    prevVelocity = currVelocity;
    prevDisplacement = currDisplacement;
    fallTime += TIME_STEP;
  }

  return 0;
}
