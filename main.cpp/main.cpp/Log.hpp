#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>


extern unsigned long long maxPrime; //def. in main.cpp

class Log
{
public:
	/*
	Kann logprime und logtime miteinander verbinden, logprime wird nur gebraucht, um prüfen zukönnen, ob alle Primzahlen auch richtig sind.
	
	@prime : zu loggende Primzahl (logprime) bzw. die Information, dass eine neue Primzahl gefunden wurde (logtime). 
	*/
 static void log(unsigned long long prime);

/*
Logt die übergeben Zahl in .txt Datein, 1.000.000 Zahlen pro Datei, damit die Datei nicht zugroß wird. 
Der Name dieser Datein setzt sich aus "logPrim" + PC-Standard-Time in sec + ".txt"

@prime : zu loggende Primzahl
*/
 static void logprime(unsigned long long prime);

 /*
 Logt wie heufig diese Funktion aufgerufen wird, die Zahl wird dann einmal pro Sekunde in der Datei logTime.txt gesichert 
 zusammen mit der "maxPrime" Variable und den vergangenen Sekunden seit dem Start des Programmes. 
 Zusätslich werden diese Informationen auch in einer Konsole ausgegeben.
 */
 static void logtime();
};

