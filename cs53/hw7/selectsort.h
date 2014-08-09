/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/19/07
//Purpose: To sort an array using the selectsort method

/* Templated selectSort function will sort primitive data types with no 
overloading of operators.
Pre: Operator > is defined for passed type, C < than length of array passed
	Must be passed an array followed by the length of the array
Post: Sorts passed array from least to greatest  */
template<typename T, typename C>
void selectSort(T array[], const C datasize) {
	int nextsmallest, i;
	for (i = 0; i < datasize; i++) {
		int j, k = i;
		T min = array[i];
		
		for (j = i + 1; j < datasize; j++) {
			//Change the following < to > for a greatest to least sort
			if (array[j] < min) {
				min = array[j];
				k = j;
			}
		}
		nextsmallest = k;

		T temp = array[i];
		array[i] = array[nextsmallest];
		array[nextsmallest] = temp;
	}
}
/**********************************END OF FILE********************************/
