#pragma once
#include <iostream>
#include "LinkedList.hpp"

using namespace std;



// only for the 1st Nodeo
void LinkedList::initNode(struct LinkedList *last, unsigned long long n) {
	last->data = n;
	last->next = NULL;
}

// apendingo
LinkedList* LinkedList::addNode(struct LinkedList *last, unsigned long long n) {
	LinkedList *newNode = new LinkedList;
	newNode->data = n;
	newNode->next = NULL;
	if (last->next == NULL) {
		last->next = newNode;

	}
	else {
		// TODO ERRORo
	}


	return newNode;
}

void LinkedList::display(struct LinkedList *head) {
	LinkedList *list = head;
	while (list) {
		cout << list->data << " ";
		list = list->next;
	}
	cout << endl;
	cout << endl;
}