#pragma once
#include "IsItAPrime.hpp"





bool IsItAPrime::isItAPrime(unsigned long long prime) {
	unsigned long long divisor = 2;
	LinkedList * primOP = head;
	static const unsigned long long maxDifference= 250000;
	while((maxPrime + maxDifference*2) < prime){}
	while(maxPrime*2 < prime){}
	int i = 0;
	while (divisor * divisor <= prime) {
		if (prime % divisor == 0) { return false; }
		i++;
		if (i > primOP->iaa) {
			primOP = primOP->next;
			i = 0;
			divisor = primOP->data->primeArray[i];
		}
		else {
			divisor = primOP->data->primeArray[i - 1];
		}
	}
	return true;
};
/*
bool IsItAPrime::isItAPrime(unsigned long long prime) {
	unsigned long long divisor = 2;
	LinkedList * primOP = head;
	static const unsigned long long maxDifference= 250000;
	while((maxPrime + maxDifference*2) < prime){}
	while(maxPrime*2 < prime){}
	while (divisor * divisor <= prime ) {
		if (prime % divisor == 0) { return false; }
		divisor = primOP->data;
		primOP = primOP->next;
	}
	return true;
	};*/