#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"
#include "SingelCore.hpp"

#ifdef _WIN64
#include <dos.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif





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
