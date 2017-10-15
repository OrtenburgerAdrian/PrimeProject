//Adrian
#pragma once
#include "Log.hpp"

/*Basisfunktion, welche Logfunktionen nach gegebenen Einstellungen ausführt.*/
void Log::log(unsigned long long prime) {
	if (moreLog == true) { Log::logprime(prime); } //Eigentlich nur wichtig, um pruefen zu koennen, dass alle Primzahlen richtig sind.
	Log::logtime();
}


/*
Loggt die uebergebene Zahl in .txt Dateien. Damit die Datei nicht zu grosz wird, ist die groesze auf 1.000.000 Zahlen beschränkt.
Der Name dieser Dateien setzt sich aus "logPrime" + PC-Standard-Time in Sekunden + ".txt" zusammen.

@ prime : Zu loggende Primzahl.
*/
void Log::logprime(unsigned long long prime) {
	/*Ich habe mich entschieden die Log-Dateien nicht zu wechseln, wenn sie eine bestimme groesze erreichen,
	sondern wenn ein bestimmte Anzahl an Zahlen geloggt wurde. Denn einen Counter mitlaufen zu lassen ist performanter.*/

	std::stringstream ss; //Wird gebraucht um aus time einen String zu machen.
	static std::ofstream logPrime;	//Stellt die zu schreibende Datei dar.
	static int maxCount = 1000000;	//Soviele PrimZahlen werden in eine Logdatei geschrieben.
	static int count = 0;			//Soviele PrimZahlen wurden bereits in die Logdatei geschrieben.

	if (logPrime.is_open() && count < maxCount) {
		logPrime << prime << std::endl;
		count++;
	}
	else {
        //Nur beim Erstellen der ersten Log-Datei im Programmablauf ist die Bedingung "false".
		if (count >= maxCount) { //Wenn der count >= maxCount ist, muss ein file descriptor offen sein.
			logPrime.close();
		}

		time_t t = time(0); // Systemzeit in sec.
		ss << t;     //time wird zu einem String convertiert.
		std::string dateiName = "./logPrime" + ss.str() + ".txt";
		logPrime.open(dateiName.c_str(), std::ios::app);
		logPrime << prime << std::endl;
		count = 1;
	}

}

/*
Logt wie haeufig diese Funktion aufgerufen wurde, die Zahl wird dann einmal pro Sekunde in der Datei logTime.txt gesichert
zusammen mit der "maxPrime" Variable und den vergangenen Sekunden seit dem Start des Programmes.
Zusaetzlich werden diese Informationen auch in einer Konsole ausgegeben.
*/
void Log::logtime() {
	static std::ofstream logTime; //File descriptor
	static unsigned long long count = 0; //Zaehlt wie haeufig die Funktion aufgerufen wurde.
	static time_t st = time(0); //Zeit in Sekunden, wann diese Funktion das erste mal aufgerufen wurde.
	static time_t lastTime = time(0);	//Wird gebraucht um zu pruefen ob eine Sekunde vergangen ist.
	time_t t = time(0);					//Wird gebraucht um zu pruefen ob eine Sekunde vergangen ist.
	count++;
	if (t > lastTime) {
		lastTime = t;
		if (logTime.is_open()) {
			logTime << count << ":" << maxPrime << "	:	" << t - st << std::endl; //In Datei schreiben
		}
		else {
			std::string dateiName = "./logTime.txt";
			logTime.open(dateiName.c_str(), std::ios::app);
			logTime << count << ":" << maxPrime << "	:	" << t - st << std::endl; //In Datei schreiben
		}
		std::cout << count << ":" << maxPrime << "	:	" << ((t - st) / 60) << ":" << ((t - st) % 60) << std::endl;//In Console schreiben
	}
}
