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