//Adrian
//Fuer diese .hpp gibt es keine .cpp Datei.
#pragma once
#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Log.hpp"

//Anzahl der zu startenden Worker-Threads; wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
extern int nuberOfWorker;			//def. in main.cpp

/*Adresse der ersten Node.*/
extern LinkedList *head;			//def. in main.cpp

/*Adresse der letzten Node.*/
extern LinkedList *PrimeListLast;	//def. in main.cpp

class SingelCore
{
public:

	/*Singelcore-Rahmen-Funktion, sehr aehnlich zur MultiCore-Funktion, nur nicht Thread sicher.*/
	static void run() {
		static unsigned long long i = 3;
		maxPrime = 3;
		LinkedList::initNode(head, 3);
		while (true)
		{
			if (IsItAPrime::isItAPrime(i)) {								//Pruefung auf Primzahl
				PrimeListLast = LinkedList::addNode(PrimeListLast, i);		//Speichern der Primzahl
				maxPrime = i;
				Log::log(i);
				i = i + 2;
			}
			else {
				i = i + 2;
			}
		}
	}
};
