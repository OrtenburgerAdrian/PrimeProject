//Adrian
#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include "WorkList.hpp"
										//Anzahl der zu startenden Worker-Threads; wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
extern int numberOfWorker;				//def. in main.cpp

										//aus der Worklist kommen die zuprüfenden Zahlen und die Resultate werden verarbeitet.
extern WorkList *wl;					//def. in main.cpp

class PeerWorker
{
public:
	static void threadprog();
	static void run();
};

