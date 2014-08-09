//Gary Steelman (gws4g2)
//CS 53-D
//9.5.07

#include <iostream.h>
#include <cmath>

int main()
{
	//Number of gallons to purchase of paint
	int N = 0;
	//Number of children in the vicinity of the painting
	int nc = 0;
	//Number od days expected to complete the job
	int nd = 0;

	//International Painter's constant
	float P = .004;
	//Expected waste for any job
	float W = 1.2;
	//Surface area to be painted
	float S = 0;

	
	//Prompts the user with what the program is and how to use it.
	cout << "Welcome to the IPU calculator!";
	cout << "\nThis program is designed to help painters decide exactly how much ";
	cout << "\npaint to buy. Please input properly." << endl;

	//Prompts the user for input of the number of children in the vicinity.
	cout << "Please enter the number of children that will be in the vicinity ";
	cout << "\nwhen the painting is being done: ";

	cin >> nc;

	//Prompts the user for input of the surface area to be painted
	cout << "\nPlease input the surface area to be painted: ";

	cin >> S;

	//Prompts the user for the input of the numbers of days expected to complete
	cout << "\nPlease input how many days will this painting take to complete: ";

	cin >> nd;

	//Calculates the number of gallons the company should buy

	N = ceil(((P * static_cast<float>(nc) * S) + W) * ceil((1 + 1 / static_cast<float>(nd))));

	//Outputs the number of gallons to buy and ends the program
	cout << "The buyer of the paint should buy " << N << " gallons." << endl;
	cout << "Thank you for using the IPU calculator! Ending program..." << endl;

	return 0;
}
