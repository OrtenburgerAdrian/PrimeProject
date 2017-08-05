#pragma once
#include <mutex> //WIESO	
#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Log.hpp"


//soviele Worker-Threads werden gestartet, wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
extern int nuberOfWorker;			//def. in main.cpp

/*Adresse der ersten Note*/
extern LinkedList *head;			//def. in main.cpp

/*Adresse der letzten Note*/
extern LinkedList *PrimListLast;	//def. in main.cpp

//Für diese .hpp gibt es keine .cpp Datei.
class SingelCore
{
public:

//Adrian
/*Singelcore-Rahmen-Funktion, sehr ähnlich zur MultiCore-Funktion, nur nicht Thread sicher*/
	static void run() {
		static unsigned long long i = 3;
		maxPrime = 3;
		LinkedList::initNode(head, 3);
		while (true)
		{
			if (IsItAPrime::isItAPrime(i)){								//prüfung auf Primzahl
				PrimListLast = LinkedList::addNode(PrimListLast, i);	//speichern der Primzahl
				maxPrime = i;
				Log::log(i);
				i= i+2;
			}
			else {
				i= i+2;
			}
		}
	}
};