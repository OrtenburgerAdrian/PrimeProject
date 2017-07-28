#pragma once
#include "LinkedList.hpp"

using namespace std;



// only for the 1st Node
void LinkedList::initNode(struct LinkedList *last, unsigned long long n) {

	last->data = PrimeArray::initPrimeArray();
	(*last).data->primeArray[0] = n;
	last->iaa = 1;
	last->next = NULL;
}


LinkedList* LinkedList::addNode(struct LinkedList *last, unsigned long long n) {
	if (last->iaa > 1000000) {
		LinkedList *newNode = new LinkedList;
		newNode->data = PrimeArray::initPrimeArray();
		newNode->data->primeArray[0] = n;
		newNode->iaa = 1;
		newNode->next = NULL;
		if (last->next == NULL) {
			last->next = newNode;
		}
		else {
			// TODO ERROR
		}
		return newNode;
	}
	else
	{
		(*last).data->primeArray[last->iaa] = n;
		last->iaa++;
		return last;
	}

}
/*#pragma once
#include <iostream>
#include "LinkedList.hpp"

using namespace std;



// only for the 1st Node
void LinkedList::initNode(struct LinkedList *last, unsigned long long n) {
	last->data = n;
	last->next = NULL;
}


// apending
LinkedList* LinkedList::addNode(struct LinkedList *last, unsigned long long n) {
	LinkedList *newNode = new LinkedList;
	newNode->data = n;
	newNode->next = NULL;
	if (last->next == NULL) {
		last->next = newNode;
	}
	else {
		// TODO ERROR
	}
	return newNode;
}
*/