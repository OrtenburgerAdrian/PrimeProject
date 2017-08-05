//Adrian
#pragma once
#include <mutex>
#include "LinkedList.hpp"

//Soviele Worker-Threads werden gestartet, wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
extern int numberOfWorker;			//def. in main.cpp

/*Adresse der ersten Note.*/
extern LinkedList *head;			//def. in main.cpp

/*Adresse der letzten Note.*/
extern LinkedList* PrimeListLast;	//def. in main.cpp

class Worker
{
public:
	/*Startet die Worker-Threads.*/
	static void start();

	/*Die Rahmen-Funktion, für die MultiComputing-Worker-Threads.*/
	static void thread_calculate();
};