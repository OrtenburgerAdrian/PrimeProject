#pragma once
#include <iostream>

struct LinkedList{
public:
	unsigned long long data;
	LinkedList* next;

	//Adrian
	static void  initNode(struct LinkedList *last, unsigned long long n);
	//Adrian
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
	//Adrian
	static	void  display(struct LinkedList *head);

	 

	private:






};