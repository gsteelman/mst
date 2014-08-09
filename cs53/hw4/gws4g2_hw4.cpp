//Gary Steelman
//CS53-D
//gws4g2_hw4.cpp
//Last modified 9.20.07

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int main()
{
	//Seeds the random number generator
	srand(time(NULL));
	
	//Sets the output of our couts to have 2 decimal precision
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);
	
	string lFirstName = "";
	string lLastName = "";
	
	short lRandDart = 0;
	short lMenuChoice = 0;
	short lPubNum = 0;
	short lMenuChoice1Chosen = 0;
	short lComNum = 0;
	short lMenuChoice2Chosen = 0;
	short lMenuChoice3Chosen = 0;
	short lChoice4Available = 0;
	short lQuit = 0;
	/*float lCurrPay = 0;*/
	float lRaise = 0;
	float lStuScore = 0;
	
	const short lPubNumMax = 1000;
	const short lPubNumMin = 0;
	const short lComNumMax = 50;
	const short lComNumMin = 0;
	const short lStuScoreMax = 4;
	const short lStuScoreMin = 0;
	const float lPubMult = 0.4;
	const float lEvalMult = 0.45;
	const float lRandMult = 0.1;
	const float lCommMult = 0.05;
	/*const float lPayMax = 250000;
	const float lPayMin = 0;*/

	cout << "Please input your first name: ";
	cin >> lFirstName;
	cout << "\nPlease input your last name: ";
	cin >> lLastName;
	
	do
	{
		do
		{
			cout << "\n\n ------Pay Raise Calculation Menu------ ";
			cout << "\n1.  Publications (count)";
			cout << "\n2.  Service (number of committees)";
			cout << "\n3.  Evaluation Score (student evaluations, 4.0 scale)";
			cout << "\n4.  Calculate Raise (must complete 1-3 first)";
			cout << "\n5.  Quit" << endl;
			
			cin >> lMenuChoice;
			
		} while (!(lMenuChoice == 1 || lMenuChoice == 2 || lMenuChoice == 3 || lMenuChoice == 4 || lMenuChoice == 5));
		
		switch (lMenuChoice)
		{
			case 1:
			
				do
				{
					cout << "How many publications do you have " << lFirstName << "? ";
					cin >> lPubNum;
				} while (!(lPubNum >= lPubNumMin && lPubNum <= lPubNumMax));
				lMenuChoice1Chosen = 1;
				break;
			
			case 2:
			
				do
				{
					cout << "How many service committees are you on " << lFirstName << "? ";
					cin >> lComNum;
				} while (!(lComNum >= lComNumMin && lComNum <= lComNumMax));
				lMenuChoice2Chosen = 1;
				break;
			
			case 3:
			
				do
				{
					cout << "What was your student evaluation score " << lFirstName << "? ";
					cin >> lStuScore;
				} while (!(lStuScore >= lStuScoreMin && lStuScore <= lStuScoreMax));
				lMenuChoice3Chosen = 1;
				break;
			
			case 4:
			
				if (lChoice4Available == 1)
				{
					lRandDart = rand() % 11;
					
					lRaise = (lPubMult * lPubNum) + (lCommMult * lComNum) + (lEvalMult * lStuScore) + (lRandMult * lRandDart);
					
					/*do
					{
						cout << "What is your current yearly salary " << lFirstName << "? ";
						cin >> lCurrPay;
					} while (!(lCurrPay >= lPayMin && lCurrPay <= lPayMax));*/
				
					cout << "Your current pay raise will be: " << lRaise << "%";
					/*cout << "Which is a " << (100*(lRaise/lCurrPay)) << "% increase in pay!";*/
					break;
				}
				
				else
				{
					cout << "You have not input all of the necessary information yet " << lFirstName << ". Please input all of the necessary information first." << endl;
					break;
				}
				break;
			
			case 5:
		
				cout << "Thank you for using the PayRaise Calculator program " << lFirstName << "." << endl;
				lQuit = 1;
				break;
			
		}
		
		if (lMenuChoice1Chosen == 1 && lMenuChoice2Chosen == 1 && lMenuChoice3Chosen == 1)
		{
			lChoice4Available = 1;
		}
		
	} while (lQuit != 1);
	
	return 0;
}
