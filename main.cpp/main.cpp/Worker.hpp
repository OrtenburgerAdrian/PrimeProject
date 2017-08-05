#pragma once
#include <mutex>
#include "LinkedList.hpp"


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


