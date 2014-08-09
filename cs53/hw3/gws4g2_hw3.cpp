//Gary Steelman
//CS53-D
//9.12.07
//gws4g2_hw3.cpp
//Uses a simple menu to get input from the user about specific conditions 
//And then uses those conditions to tell the user what kind of gun to use to
//Hunt the bunnies and how much ammunition to use as well

#include <iostream>

using namespace std;

int main ()
{
	//Variable Declarations
	short lBunnyType = 0; //The type of bunny
	short lTempCActual = 0; //Rounded Celsius temperature
	short lGunType = 0; //1 for shotgun 2 for rifle
	short lAmmunition = 0; //How many bullets the hunter needs to take
	
	float lTemperatureF = 0; //The input temperature
	float lTemperatureC = 0; //The Celsius temperature
	
	char lRain = 'a'; //Whether it is raining or not y/n
	
	const short LTEMPFUL = 120; //Upper limit for input temperature
	const short LTEMPFLL = -40; //Lower limit for input temperature
	
	do
	{
		//Prompts the user with the simple menu to begin the program
		cout << "\t\tBUNNY MENU";
		cout << "\n\t\t----------";
		cout << "\nChoose the type of bunny you want to hunt";
		cout << "\n1. Plastic";
		cout << "\n2. Porcelain";
		cout << "\n3. Chocolate";
		cout << "\n4. Quit the Program";
		cout << "\nYour choice: ";
		
		//Gets the user's choice of which bunny to hunt
		cin >> lBunnyType;
	} while (!(lBunnyType == 1 || lBunnyType == 2 || lBunnyType == 3 || lBunnyType == 4));
	//Above make sure the bunny type entered is legitimate
	
	//Continues the program if type 4 was not chosen
	if (lBunnyType != 4) 
	{
		do
		{
			//Prompts the user for the temperature outside in degrees F
			cout << "\nWhat is the temperature outside?";
			cout << "\n[In Fahrenheit degrees and between -40 and 120]: ";
			
			//Gets the temperature otuside from the user
			cin >> lTemperatureF;
		} while (!(lTemperatureF <= LTEMPFUL && lTemperatureF >= LTEMPFLL));
		//Above line makes sure the input temperature is within range
		
		//Converts the fahrenheit temperature to a celsius degree
		lTemperatureC = (((lTemperatureF - 32) / 9) * 5);

		//Rounds the temperature C to the nearest degree
		if (lTemperatureC >= 0)
		{
			if ((((lTemperatureC + 1) - lTemperatureC)) >= .5)
			{
				lTempCActual = static_cast<int>(lTemperatureC) + 1;
			}
			
			else if ((((lTemperatureC + 1) - lTemperatureC)) < .5)
			{
				lTempCActual = static_cast<int>(lTemperatureC);
			}
		}
		
		else if (lTemperatureC < 0)
		{
			if (((((lTemperatureC * -1) + 1) - (lTemperatureC * -1))) >= .5)
			{
				lTempCActual = static_cast<int>(lTemperatureC) - 1;
			}
			
			else if (((((lTemperatureC * -1) + 1) - (lTemperatureC * -1))) < .5)
			{
				lTempCActual = static_cast<int>(lTemperatureC);
			}
		}
	
		do
		{
			//Prompts the user for the weather (rain or not)
			cout << "\nIs it raining outside? [y/n]: ";
			
			//Gets whether or not it is raining outside
			cin >> lRain;
		}while (!(lRain == 'y' || lRain == 'n'));
		
		//If we are wanting to hunt a plastic bunny
		if (lBunnyType ==1)
		{
			if (lTempCActual > 0)
			{
				cout << "I am terribly sorry, but the plastic bunnies only";
				cout << "\ncome out when the temperature is under 0 C.";
				cout << "\nYou cannot hunt this bunny right now.";
				cout << "\nEnding Program..." << endl;
				return 0;
			}
			
			else
			{
				cout << "\nYou can hunt plastic bunnies.";
				lGunType = 1;
			}
		}
		
		//If we are wanting to hunt a porcelain bunny
		if (lBunnyType == 2)
		{
			if (lTempCActual < 0)
			{
				cout << "I am terribly sorry, but the plastic bunnies only";
				cout << "\ncome out when the temperature is over 0 C.";
				cout << "\nYou cannot hunt this bunny right now.";
				cout << "\nEnding program..." << endl;
				return 0;
			}
			
			else if (lRain == 'y')
			{
				cout << "I am terribly sorry, but the porcelain bunnies can";
				cout << "\nonly be hunted with a rifle and rifles cannot";
				cout << "\nbe used when it is raining. You cannot hunt this";
				cout << "\nbunny right now.";
				cout << "\nEnding Program..." << endl;
				return 0;
			}
			
			else 
			{
				cout << "\nYou can hunt porcelain bunnies.";
				lGunType = 2;
			}
		}
		
		//If we are wanting to hunt a chocolate bunny
		if (lBunnyType == 3)
		{
			if (lTempCActual > 20)
			{
				cout << "I am terribly sorry, but the chocolate bunnies only";
				cout << "\ncome out when the temperature is below 20 C.";
				cout << "\nYou cannot hunt this bunny right now.";
				cout << "\nEnding program..." << endl;
				return 0;
			}
			
			else 
			{
				cout << "\nYou can hunt chocolate bunnies.";
				lGunType = 2;
			}
		}
		
		//Calculates how much ammunition the hunter needs to take
		if (lTempCActual < 0)
		{
			lAmmunition = 1;
		}
		
		for (int lTemperatureCheck = 0; lTemperatureCheck < lTempCActual; lTemperatureCheck+=5)
		{
			lAmmunition+=1;
		}
		
		//The next 2 statements output how much ammunition the hunter must take
		//And the kind of gun he is to use
		if (lGunType == 1)
		{
			cout << "\n\nYou necessitate the use of the shotgun and" << lAmmunition << " bullets.";
			cout << "\nGood hunting and godspeed!" << endl;
		}

		if (lGunType == 2)
		{
			cout << "\n\nYou necessitate the use of the rifle and " << lAmmunition << " bullets.";
			cout << "\nGood hunting and godspeed!" << endl;
		}
	} 
	
	//If 4 was originally chosen, the program ends
	else if (lBunnyType == 4)
	{
		cout << "Thank you for using the bunny hunting program." << endl;
	}
	
	return 0;
}
