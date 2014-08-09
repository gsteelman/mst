/*******************************BEGINNING OF FILE*****************************/
//Author: Gary Steelman
//Date: 10/23/07
//Purpose: To sort an array using the bubblesort method

/* Templated bubbleSort function will sort primitive data types with no 
overloading of operators.
Pre: Operator > is defined for passed type, C < than length of array passed
	Must be passed an array followed by the length of the array
Post: Sorts passed array from least to greatest  */
template<typename T, typename C>
void bubbleSort(T array[], const C arraysize) {
	T temp = 0;
	T x = 0;
	T y = 0;
	for (int i = 0; i < arraysize; i++) {
		for (int j = 0; j < arraysize; j++) {
			if (array[j] > array[j + 1])
			{	
				x = array[j];
				y = array[j + 1];
				temp = x;
				x = y;
				y = temp;
			}
		}
	}
	return;
}

/**********************************END OF FILE********************************/
