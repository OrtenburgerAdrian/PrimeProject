#pragma once
//f�r diese .hpp gibt es keine .cpp
struct PrimeArray {
	unsigned long long primeArray[1000000];

	//Adrian
	/*Ein neues Array f�r die LinkedList*/
	static PrimeArray* initPrimeArray() {
		PrimeArray *primeArray = new PrimeArray;
		return  primeArray;
	}
};

