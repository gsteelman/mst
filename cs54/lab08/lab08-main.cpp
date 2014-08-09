/*******************************BEGINNING OF FILE*****************************/
// Name: Gary Steelman
// Class and Section: CS 54, Section D
// Date: 10.17.07
// Purpose: To write the main function for a program that uses bubble sort to
	//sort an array

#include "lab08.h"
	
int main() 
{
	time_t start, end;
	double dif;
	
	srand(time(NULL)); //Seeds random number generator
	
	int numbers1[ARRAYSIZE1]; //Makes an array of length ARRAYSIZE1
	int numbers2[ARRAYSIZE2]; //Makes an array of length ARRAYSIZE1
	int numbers3[ARRAYSIZE3]; //Makes an array of length ARRAYSIZE1
	int numbers4[ARRAYSIZE4]; //Makes an array of length ARRAYSIZE1

	initiateArray(numbers1, ARRAYSIZE1); //Initializes values of the array 1-100
	initiateArray(numbers2, ARRAYSIZE2); //Initializes values of the array 1-100
	initiateArray(numbers3, ARRAYSIZE3); //Initializes values of the array 1-100
	initiateArray(numbers4, ARRAYSIZE4); //Initializes values of the array 1-100
				
	//printArray(numbers1); //ouputs the array
	
	//Times and sorts numbers 1
	time (&start);
	bubbleSort(numbers1, ARRAYSIZE1); //Sorts the numbers1 using the bubbleSort method
	time (&end);
	dif = difftime (end, start);
	cout << "It took " << dif << " seconds to sort array 1." << endl;
	
	//Times and sorts numbers 2
	time (&start);
	bubbleSort(numbers2, ARRAYSIZE2); //Sorts the numbers2 using the bubbleSort method
	time (&end);
	dif = difftime (end, start);
	cout << "It took " << dif << " seconds to sort array 2." << endl;
	
	//Times and sorts numbers 3
	time (&start);
	bubbleSort(numbers3, ARRAYSIZE3); //Sorts the numbers3 using the bubbleSort method
	time (&end);
	dif = difftime (end, start);
	cout << "It took " << dif << " seconds to sort array 3." << endl;
	
	//Times and sorts numbers 4
	time (&start);
	bubbleSort(numbers4, ARRAYSIZE4); //Sorts the numbers4 using the bubbleSort method
	time (&end);
	dif = difftime (end, start);
	cout << "It took " << dif << " seconds to sort array 4." << endl;
	
	
	return 0;
}

/**********************************END OF FILE********************************/
