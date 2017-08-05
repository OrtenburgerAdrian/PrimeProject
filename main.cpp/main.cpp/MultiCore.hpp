#pragma once
#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Log.hpp"

/*Die bis jetz größte gepeicherte Primzahl, ist für jeden Client-PC eine andere, da jeder PC nur seine größte Zahl kennt.*/
extern unsigned long long maxPrime;		//def. in main.cpp
extern LinkedList primesList;
//soviele Worker-Threads werden gestartet, wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
extern int numberOfWorker;				//def. in main.cpp

/*Adresse der ersten Note*/
extern LinkedList *head;				//def. in main.cpp

/*Adresse der letzten Note*/
extern LinkedList* PrimListLast;		//def. in main.cpp

static std::mutex timeMutex;
static std::mutex primeMutex;
static std::mutex Calculate;
static std::mutex setMaxPrime;

class MultiCore
{
public:
	/*Diese Funktion ist die rahmen Funktion, um local auf einen PC mit mehren Threads Primzahlen zuberechen*/
	static void threadprog();

	/*Startet die Worker-Threads und lässt diese die Funktion "MultiCore::threadprog()" ausführen. 
	Es wird kein Core für zusätzliche Arbeitgebraucht und können alle mit Worker-Threads belegt werden.*/
	static void run();
};
