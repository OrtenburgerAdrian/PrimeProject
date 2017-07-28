#pragma once
#include "PrimeArray.hpp"
#include <iostream>
extern const int primeArraylength;
struct LinkedList{
public:
	PrimeArray* data;
	LinkedList* next;
	int iaa;
	
	

	//Adrian
	static void  initNode(struct LinkedList *last, unsigned long long n);
	//static void  initPrimeArray(unsigned long long n);
	//Adrian
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
	//static LinkedList* addNode(struct LinkedList *last, unsigned int n);
	//static  LinkedList* addPrime(unsigned long long n);

	private:

};


/*#pragma once
#include <iostream>

struct LinkedList{
public:
	unsigned long long data;
	LinkedList* next;

	//Adrian
	static void  initNode(struct LinkedList *last, unsigned long long n);
	//Adrian
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);

	private:

	};*/