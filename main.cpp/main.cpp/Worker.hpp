#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"
extern bool threadActive[];
extern bool threadIsPrime[];
extern bool threadNotDelete[];
extern unsigned long long threadToCalculate[];
extern int nuberOfWorker;
extern LinkedList primesList;
extern LinkedList resultList;

class Worker
{
public:
	static void start();
	static void thread_calculate(int threadNumber);
	static void setTestingInt(unsigned long long prime, int threadNumber);
	static void stop(int threadNumbe);
	static void TestingInt(int threadNumbe, unsigned long long prime);
	static unsigned long long TestingInt(int threadNumbe);

	static void Active(int threadNumber, bool activ);
	static bool Active(int threadNumber);


};


