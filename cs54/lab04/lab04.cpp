//Gary Steelman
//CS54-D
//9.19.07
//Lab 04 does fun stuff :D

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
	float lImpulseTotal = 0; //Total impulse on the elevator
	float lImpulseInst = 0; //Impulse for each iteraion of input mass
	float lMass = 0; //The mass being put into the elevator
	float lMassTotal = 0; //The total mass put into the elevator
	float lProbOfBreak = 0; //Probability of breaking of the elevator
	float lPctOfDeath = 0; //Probability of dying in the broken elevator
	float lBreakHeight = 0; //The height of the elevator when it breaks
	float lAAmt = 0; //The amount of acceleration of the elevator
	float lVAmt = 0; //The amount of velocity of the elevator
	float lXPos = 0; //The height of the elevator
	float lTime = 0; //The time after the elevator breaks and begins to descend
	
	int lRand = 0; //A random integer
	int lDeath = 0; //The number for deciding if you die or not
	
	const short LMAXMASS = 1000; //The max amount of mass the elevator can hold
	const short LMINMASS = 100; //The min amount of mass the elevator will detect
	const float LIMPCONST = 136.876; //The impulse equation constant
	const float G = 9.8; //Average gravity on the surface of the earth
	
	srand(time(NULL)); //Seeds our rand()
	
	for (int x = 0; x < 4; x++)
	{
		//Gets mass input as long as its valid
		do
		{
			cout << "Please input the " << x + 1 << " iteration of the mass of";
			cout << " the elevator in kilograms.";
			cout << "\nNote that your mass must be <1000 and >100 kg: ";
			
			cin >> lMass;
		} while (!(lMass > LMINMASS && lMass < LMAXMASS));
		
		lMassTotal+=lMass;
		
		//Calculates and outputs this iteration's impulse and total impulse
		lImpulseInst = LIMPCONST * lMass;
		cout << "The Impulse generated on this trip is: " << lImpulseInst;
		
		lImpulseTotal+=lImpulseInst;
		cout << "\nThe total impulse generated thus far is: " << lImpulseTotal << endl;
	}
	
	//Decides the chance of the elevator breaking
	lRand = rand() % static_cast<int>(lImpulseTotal) + 1;
	lProbOfBreak = lImpulseTotal / (lImpulseTotal + lRand);
	cout << "\nThe probability that the cable has broken is: " << lProbOfBreak << endl;
	
	//Decides the percent of death
	lPctOfDeath = 100 * lProbOfBreak;
	cout << "Your chances of dying are: " << lPctOfDeath << "%." << endl;
	
	//Decides whether the person dies or not
	lDeath = ((100 * rand()) % static_cast<int>(lPctOfDeath)) + 1;
	if (lDeath >= 4)
	{
		cout << "Death comes swiftly when the elevator comes crashing down." << endl;
	}
	else
	{
		cout << "You avoid death...for now.";
	}

	lBreakHeight = (3.6 * 42);
	
	do
	{
		lAAmt = (((lMassTotal * G) - (7.008 * (lVAmt * lVAmt))) / lMassTotal);
		
		lVAmt = lVAmt + (lAAmt * lTime);
	
		lXPos = lXPos+ (lVAmt * lTime);
		
		lTime += 1e-6;
	} while (lXPos < lBreakHeight);
	
	cout << "Total Time: " << lTime << endl;
	cout << "Final Acceleration: " << lAAmt << endl;
	cout << "Final Velocity: " << lVAmt << endl;
	cout << "Final X Position (the Ground): " << lXPos << endl;
	
	return 0;
}
