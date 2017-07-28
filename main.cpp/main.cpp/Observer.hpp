#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
//#include <semaphore.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

extern unsigned long long maxPrime;
extern LinkedList * head;
extern LinkedList * PrimListLast;
extern int numberOfWorker;

class Observer
{
	static void run_listener();
	static void run_teller();

public:
	//Benni:
	static void run();
	static void run(int expectedClientCount);
};
