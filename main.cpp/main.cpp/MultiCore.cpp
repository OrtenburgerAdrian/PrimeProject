//Adrian
#pragma once
#include <mutex>
#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Log.hpp"
#include "Threads.hpp"
#include "MultiCore.hpp"

/*Diese Funktion ist die Rahmen-Funktion, um local auf einen PC mit mehren Threads, Primzahlen zuberechen*/
void MultiCore::threadprog() {
	static unsigned long long i = 1; //Ein Counter welcher für alle Threads gilt, dieser wird gebraucht1 damit die Threads wissen welche Zahlen sie als naechstes pruefen muessen.
	unsigned long long i2;
	while (true)
	{
		/*Thread-Sichere Inkrementierung des Counters*/
		Calculate.lock();
		i = i + 2;
		i2 = i;
		Calculate.unlock();

		if (IsItAPrime::isItAPrime(i2)) {//Pruefung auf Primzahl

			/*Speichern der neuen Primzahl in der Linkedlist*/
			primeMutex.lock();
			PrimeListLast = LinkedList::addNode(PrimeListLast, i2);
			primeMutex.unlock();

			/*Setzen der neuen hoechsten Primzahl*/
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

/*Startet die Worker-Threads und laesst diese die Funktion "MultiCore::threadprog()" ausfuehren.*/
void MultiCore::run() {
	LinkedList::initNode(head, 3); // Eine Primzahl ist ausreichend um das Programm zu starten.
	maxPrime = 3; //Da nun die erste Primzahl in der LinkedList 3 ist, muss diese auch gesetzt werden.
	numberOfWorker++; // Da die numberOfWorker bei ihrer Initialisierung -1 gerechnet wurden, was hier nicht von vorteil ist, da keine PC-Leistung für einen weiteren Thread gespart werden sollte.
	Threads::start("multiCore", numberOfWorker);
}
