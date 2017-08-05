#pragma once
#include <mutex>
#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Log.hpp"
#include "Threads.hpp"
#include "MultiCore.hpp"

/*Diese Funktion ist die rahmen Funktion, um local auf einen PC mit mehren Threads Primzahlen zuberechen*/
	 void MultiCore::threadprog() {
		static unsigned long long i = 1; //Ein Counter welcher für alle Threads gilt, dieser wird gebrauch damit die threts wissen welche Zahlen sie als nächstes prüfen müssen. 
		unsigned long long i2;
		while (true)
		{
			/*Threadsiche Incrementirung des Counters*/
			Calculate.lock();
			i = i + 2;
			i2 = i;
			Calculate.unlock();

			if (IsItAPrime::isItAPrime(i2)) {//prüfung auf Primzahl

				/*Speichern der neuen Primzahl in der Linklist*/
				primeMutex.lock();
				PrimListLast = LinkedList::addNode(PrimListLast, i2);
				primeMutex.unlock();

				/*Sätzen der neuen höchsten Primzahl*/
				setMaxPrime.lock();
				if (maxPrime < i2) { maxPrime = i2; }
				setMaxPrime.unlock();

				/*Loggen der neuen Primzahl*/
				timeMutex.lock();
				Log::log(i2);
				timeMutex.unlock();
			}
		}
	}

	 /*Startet die Worker-Threads und lässt diese die Funktion "MultiCore::threadprog()" ausführen.*/
	 void MultiCore::run() {
		LinkedList::initNode(head, 3); // Eine Priemzahl ist ausreichend um das Programm zustarten. 
		maxPrime = 3; //Da nun die höchste Primzahl welche gespeichert wure 3 ist muss diese auch gesätz werden.
		numberOfWorker++; // Da die numberOfWorker bei ihrer Initialisierung -1 gerechnet wurden, was hier nicht von vorteil ist, da keine PC-Leißtung für einen weiteren Thread gespart werden sollte. 
		Threads::start("multiCore", numberOfWorker);
	}