#include "ii.h"

int main() {
	const int ARRAYSIZE = 100;
	int array1[ARRAYSIZE];
	int array2[ARRAYSIZE];
	int min = 0;
	
	userType Student[ARRAYSIZE];
	
	//initializes the array by putting incrementing values
	for (int i = 0; i < ARRAYSIZE; i++) {
		Student[i].numberType = i;
		Student[i].characterType = i;
	}
	
	/*//satisfies both preconditions
	min = findMin<int>(array1, ARRAYSIZE);
	cout << "Min: " << min << endl;
	
	//satisfies all but array[]
	min = findMin<int>(array2, ARRAYSIZE);
	cout << "Min: " << min << endl;
	
	//satisfies all but n
	min = findMin<int>(array1, 110);
	cout << "Min: " << min << endl;*/
	
	min = findMin<int>(Student, ARRAYSIZE);
	cout << "Min: " << min << endl;
	
	return 0;
}

