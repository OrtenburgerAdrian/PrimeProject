#pragma once
#include <iostream>

struct LinkedList{
public:
	unsigned long long data;
	LinkedList* next;


	static void  initNode(struct LinkedList *last, unsigned long long n);
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
	static	void  display(struct LinkedList *head);
	private:






};