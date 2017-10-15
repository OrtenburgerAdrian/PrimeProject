//Adrian
#pragma once
#include <mutex>
#include "LinkedList.hpp"

/**
 *  Enth�lt den Rahmen, um IsItAPrime als Client/Server-Anwendung auszuf�hren. Thread-Sicher
**/

//Anzahl der benoetigten Worker-Threads, wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
extern int numberOfWorker;			//def. in main.cpp

/*Adresse der ersten Node.*/
extern LinkedList *head;			//def. in main.cpp

/*Adresse der letzten Node.*/
extern LinkedList* PrimeListLast;	//def. in main.cpp

class Worker
{
public:
	/*Startet die Worker-Threads.*/
	static void start();

	/*Die Rahmenfunktion, f�r die MultiComputing-Worker-Threads.*/
	static void thread_calculate();
};
