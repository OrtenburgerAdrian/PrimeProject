#pragma once
#include <iostream>

struct LinkedList{
public:
	unsigned long long data;
	bool isPrime;
	LinkedList* next;

	//Adrian
	static void  initNode(struct LinkedList *last, unsigned long long n);
	//Adrian
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
	//Adrian
	static	void  display(struct LinkedList *head);

	private:

};

/*struct resultList
{
	unsigned long long data;
	bool isPrime;
	LinkedList* next;
	//Adrian
	static void  initNode(struct LinkedList *last, unsigned long long n);
	//Adrian
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
	//Adrian
	static	void  display(struct LinkedList *head);
};*/