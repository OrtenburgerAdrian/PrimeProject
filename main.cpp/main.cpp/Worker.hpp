//#ifdef __linux__
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

//soviele Worker-Threads werden gestartet, wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
extern int numberOfWorker;			//def. in main.cpp

/*Adresse der ersten Note*/
extern LinkedList *head;			//def. in main.cpp

/*Adresse der letzten Note*/
extern LinkedList* PrimListLast;	//def. in main.cpp

class Worker
{
public:
	static void start();
	static void thread_calculate();
};
//#endif

