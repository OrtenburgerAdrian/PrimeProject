#pragma once
//für diese .hpp gibt es keine .cpp
struct PrimeArray {
	unsigned long long primeArray[1000000];

	//Adrian
	/*Ein neues Array für die LinkedList*/
	static PrimeArray* initPrimeArray() {
		PrimeArray *primeArray = new PrimeArray;
		return  primeArray;
	}
};

