#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Log.hpp"
extern int numberOfWorker;
extern LinkedList primesList;
extern LinkedList *head;
extern LinkedList* PrimListLast;

class Worker
{
public:
	static void start();
	static void thread_calculate();
};


