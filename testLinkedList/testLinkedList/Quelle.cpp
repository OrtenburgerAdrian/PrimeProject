#pragma once
#include <iostream>
#include "LinkedList.hpp"
//#include "LinkedList.cpp"
using namespace std;


int main()
{
	
	LinkedList primesList;
	LinkedList *head = &primesList;
	LinkedList* PrimListLast = head;
	

	LinkedList::initNode(head, 10);
	LinkedList::display(head);

	PrimListLast = LinkedList::addNode(PrimListLast, 20 );
	LinkedList::display(head);

	PrimListLast = LinkedList::addNode(PrimListLast, 30 );
	LinkedList::display(head);

	PrimListLast = LinkedList::addNode(PrimListLast, 388 );
	LinkedList::display(head);

	PrimListLast = LinkedList::addNode(PrimListLast, 40);
	LinkedList::display(head);


	
	while (true)
	{

	}
	return 0;
}