//Adrian
#pragma once
#include <mutex>
#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Log.hpp"

/*Die bis jetz groeßte gepeicherte Primzahl, ist für jeden Client-PC eine andere, da jeder PC nur seine groeßte Zahl kennt.*/
extern unsigned long long maxPrime;		//def. in main.cpp
extern LinkedList primesList;
//Anzahl der zu startenden Worker-Threads; wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
extern int numberOfWorker;				//def. in main.cpp

/*Adresse der ersten Node.*/
extern LinkedList *head;				//def. in main.cpp

/*Adresse der letzten Node.*/
extern LinkedList* PrimeListLast;		//def. in main.cpp

static std::mutex timeMutex;
static std::mutex primeMutex;
static std::mutex Calculate;
static std::mutex setMaxPrime;

class MultiCore
{
public:
	/*Diese Funktion ist die Rahmen-Funktion, um local auf einen PC mit mehren Threads Primzahlen zu berechnen.*/
	static void threadprog();

	/*Startet die Worker-Threads und lässt diese die Funktion "MultiCore::threadprog()" ausfuehren.
	Es wird kein Core für zusaetzliche Arbeit gebraucht und so koennen alle CPU-Core's mit Worker-Threads belegt werden.*/
	static void run();
};
