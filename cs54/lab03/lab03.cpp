//Gary Steelman
//CS54-D
//9.12.07
//lab03.cpp: 
//Part 1 test whether a student's bridge is overweight
//Part 2 calculates the student's total score
//Part 3 calculates the amount of weight the students' bridge can hold

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	float numsticks = 0; //Number of total sticks used
	float masstotal = 0; //Total mass of the bridge
	float score = 0; //Total score for the sudents' bridges
	float totweight = 0; //Total applied weight to the bridge
	float appweight = 0; //The weight applied each iteration to the bridge
	float breakweight = 0; //The amount of weight currently on the bridge
	
	short numjuncts = 0; //Number of junctions used
	short qualified = 0; //Whether or not the bridge qualified
	short addweight = 1; //Continues the addweight loop while = 1
	short appweightlegit = 0; //Forces continued input of weight if the entered weight is not a legitimate increment
	
	const float STICKWEIGHT = 1.5; //The weight of one stick
	const float JUNCTWEIGHT = 0.5; //The weight of one junction
	
	//Greets the user
	cout << "Welcome. This program will calculate the total weight of your bridge.";
	cout << "\nand then tell you whether or not your bridge is qualified.";
	
	//Prompts the user for the input of the number of sticks they use
	do 
	{
		cout << "\nPlease enter the number of sticks you are using for your bridge.";
		cout << "\nPlease note you are not allowed more than 12 total sticks: ";
		cin >> numsticks; //Gets the number of sticks used
		
		if (numsticks < 0) //If the number of sticks is <1, converts to positive
		{
			cout << "Your entered value for the number of sticks was less than 0.";
			cout << "\nSeriously, come on. Anyway, converting it to positive.";
			numsticks *= (-1);
		}
		
		else if (numsticks == 0) //If the number of sticks = 0 then insults the user and sets default value
		{
			cout << "Your entered value for the number of sticks was 0.";
			cout << "\nHow the heck can you have a bridge with no sticks?";
			cout << "\nSetting a default value of 5 sticks.";
			numsticks = 5;
		}
		
	} while(fabs(numsticks) > 12); //Continues until they enter <12 sticks
	
	//Prompts the user for input of the number of junctions they use
	cout << "\n\nPlease enter the number of junctions you are using for your bridge: ";
	cin >> numjuncts; //Gets the number of junctions
	
	if (numjuncts <= 0) //Checks if the input of the number of junctions is valid
	{
		cout << "Your entered value for the number of junctions is invalid.";
		cout << "\nConverting to a positive, non-zero number.";
		
		if (numjuncts == 0) //Converts to 4 of it was 0
		{
			numjuncts = 4;
		}
		
		else if (numjuncts < 0) //Makes a positive value of the number of junctions
		{
			numjuncts *= (-1);
		}
	}
	 
	//Calculates the total mass of the bridge
	masstotal = (STICKWEIGHT * numsticks) + (JUNCTWEIGHT * numjuncts);
	
	//Outputs the total mass of the bridge to the user
	cout << "\n\nThe total calculated mass of your bridge is: " << masstotal << " grams." << endl;
	
	//Sets qualified to 1 if the bridge is in the weight requirements, 0 otherwise
	if (masstotal > 25 || masstotal < 0)
	{
		cout << "Your bridge is over the weight requirement, you have been";
		cout << "disqualified and will receive a score of 0 points.";
		
		qualified = 0;
	}
	
	else 
	{
		qualified = 1;
	}
	
	//Calculates the students total score
	score = (pow((numsticks + numjuncts),2) / (masstotal * numsticks)) * qualified;
	
	//Outputs the students' scores along with a short prompt of them
	if (score == 0)
	{
		cout << "Wow, you didn't qualify and you got 0 points. Good job genius.";
	}
	
	else 
	{
		cout << "Your total score is: " << score << " points." << endl;
	}
	
	//Adds weight to the bridge itself until it breaks
	do
	{
		//Calculates whether or not the bridge has broken or not
		breakweight = (totweight * fabs(numsticks - numjuncts)) / (numsticks * pow(score,2));
		
		//If breakweight is exceeded, the program ends after output
		if (breakweight >= (score / 2))
		{
			cout << "Your bridge has broken!";
			cout << "\nYour bridge held" << totweight << " kg. Good job!";
			cout << "\nThank you for using this calculator.";
			break;
		}
		
		//Gets input from the user on how much weight to add to their bridge
		do
		{
			cout << "Please input the amount of weight to be added to the bridge.";
			cout << "\nRemember you can only add .5, 1, 2, or 5 kg at one time: ";
			cin >> appweight;
			
			//Checks to make sure the applied weight is a valid increment
			if (appweight == .5)
			{
				appweightlegit = 1;
			}
			
			else if (appweight == 1)
			{
				appweightlegit = 1;
			}
			
			else if (appweight == 2)
			{
				appweightlegit = 1;
			}
			
			else if (appweight == 5)
			{
				appweightlegit = 1;
			}
			
			else 
			{
				appweight = 0;
			}

		} while(appweightlegit == 0);
	
		//Updates the total weight applied
		totweight+=appweight;
	
		//Asks the user whether or not they want to continue
		cout << "\nThe total weight applied to the bridge is: " << totweight << " kg.";
		cout << "\nWould you like to add more weight? Enter 1 for yes or another number for no.";
		cin >> addweight;
		
	} while (addweight == 1);
	
	//The final farewell to the user after the program has completed running
	cout << "You decided to not add more weight.";
	cout << "\nThank you for using the calculator for your bridge!" << endl;
	
	return 0;	
}
