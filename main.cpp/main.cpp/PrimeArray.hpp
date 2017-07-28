#pragma once
#include <iostream>

struct PrimeArray {
public:
	unsigned long long primeArray[1000000];

	//Adrian
	static PrimeArray* initPrimeArray() {
		PrimeArray *primeArray = new PrimeArray;
		return  primeArray;

	}
	

};

