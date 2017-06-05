#pragma once
#include <iostream>

struct LinkedList{
public:
	unsigned long long data;
	LinkedList* next;

	//Adriano
	static void  initNode(struct LinkedList *last, unsigned long long n);
	//Adriano
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
	//Adriano
	static	void  display(struct LinkedList *head);
	private:






};