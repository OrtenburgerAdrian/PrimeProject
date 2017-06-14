#pragma once
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

