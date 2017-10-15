//Adrian
#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>


extern unsigned long long maxPrime; //def. in main.cpp
extern bool moreLog;				//def. in main.cpp

class Log
{
public:
	/*
	Kann logprime und logtime miteinander verbinden, logprime wird nur gebraucht, um pruefen zu koennen, ob alle Primzahlen auch richtig sind.

	@ prime : Zu loggende Primzahl (logprime) bzw. die Information, dass eine neue Primzahl gefunden wurde (logtime).
	*/
	static void log(unsigned long long prime);

	/*
	Logt die uebergeben Zahl in .txt Datein mit jeweils 1.000.000 Zahlen pro Datei, damit die Datei nicht zu grosz wird.
	Der Name dieser Dateien setzt sich aus "logPrime" + PC-Standard-Time in Sekunden + ".txt" zusammen.

	@ prime : Zu loggende Primzahl.
	*/
	static void logprime(unsigned long long prime);

	/*
	Loggt wie haeufig diese Funktion aufgerufen wird, die Zahl wird dann einmal pro Sekunde in der Datei logTime.txt gesichert
	zusammen mit der "maxPrime" Variable und den vergangenen Sekunden seit dem Start des Programmes.
	Zusaetzlich werden diese Informationen auch in einer Konsole ausgegeben.
	*/
	static void logtime();
};

