/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/22/07
//File: gws4g2_hw7_main.cpp
//Purpose: To the main function for the hw7 project

#include "gws4g2_hw7.h"
#include "selectsort.h"

int main() {

	//Seeds the random number generator
	srand(time(NULL));
	
	double totalx[SEGMENTSEACHWALK]; //The total of the x components for each walk
	double grandtotalx[WALKSTOTAKE]; //The total of all the x components for all walks, in an array
	double ubergrandtotalx = 0; //The grand total of all x components added together
	double totaly[SEGMENTSEACHWALK]; //The total of the y components for each walk
	double grandtotaly[WALKSTOTAKE]; //The total of all the y components for all walks, in an array
	double ubergrandtotaly = 0; //The grand total of all y components added together
	double walkDistance[WALKSTOTAKE]; //The distance each walk was
	double longestwalk = 0; //The longest walk taken by the user
	double shortestwalk = REALLYBIGNUMBER; //the shortest walk taken by the user
	double averageWalkDistance = 0; //The average distance walked for all walks
	double median = 0; //The median walking distance index
	
	segment walk[SEGMENTSEACHWALK];

	for (int i = 0; i < WALKSTOTAKE; i++) {
		for (int j = 0; j < SEGMENTSEACHWALK; j++) {
			generateSegment(walk[j]); //Generates this segment of the walk
			//Updates the total distance travelled in the x direction for this walk
			totalx[j] += walk[j].m_stepx; 
			//Updates the total distance travelled in the y direction for this walk
			totaly[j] += walk[j].m_stepy;
			//Stores the total walk values in each direction in an array
			grandtotalx[i] = totalx[j];
			grandtotaly[i] = totaly[j];
			
			//Checks to see if the current walk is the longest and/or shortest and updates
			//The running values accordingly
			if (j == (SEGMENTSEACHWALK - 1)) {
				longestwalk = calcLongest(totalx[j], totaly[j], longestwalk);
				shortestwalk = calcShortest(totalx[j], totaly[j], shortestwalk);
			}
		}
		//Fills the array walkdistance array with the distance of each walk
		walkDistance[i] = sqrt(pow(grandtotalx[i],2) + pow(grandtotaly[i],2));
	}
	
	//Outputs the distances for the longest and shortest walk
	cout << "Longest walk (total distance after all 50 segments): " << longestwalk << endl;
	cout << "Shortest walk (total distance after all 50 segments): " << shortestwalk << endl;
	
	//Sorts the walkDistance array from smallest to largest
	//bubbleSort<double, int>(walkDistance, WALKSTOTAKE);
	selectSort<double, int>(walkDistance, WALKSTOTAKE);
	
	//Gets the value of the median for the all the walks
	median = calcMedian(walkDistance, WALKSTOTAKE);
	
	//Outputs the value of the median
	cout << "The median for all walks (after all 100 walks) was: " << median << endl;
	
	//Sets the total x and y values for all walks into one variable for each component
	for (int i = 0; i < WALKSTOTAKE; i++) {
		ubergrandtotalx += grandtotalx[i];
		ubergrandtotaly += grandtotaly[i];
	}
	
	//Gets the average walk distnace for all walks
	averageWalkDistance = calcAverageWalk(ubergrandtotalx, ubergrandtotaly);
	
	//Outputs the average walk distance for all walks
	cout << "The average walk distance for all " << WALKSTOTAKE << " walks is: " << averageWalkDistance << endl;

	return 0;
}
	
/**********************************END OF FILE********************************/
