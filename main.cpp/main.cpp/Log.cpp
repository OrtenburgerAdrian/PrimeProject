//Adrian
#pragma once
#include "Log.hpp"
/*Um zuentscheiden, welche Logfunktionen gebraucht werden*/
void Log::log(unsigned long long prime) {
	///Log::logprime(prime); //Eigendlich nur wichtig, um pruefen zukoennen, dass alle Primzahlen richtig sind.
	Log::logtime();
}


/*
Logt die uebergeben Zahl in .txt Datein, 1.000.000 Zahlen pro Datei, damit die Datei nicht zugrosz wird.
Der Name dieser Datein setzt sich aus "logPrim" + PC-Standard-Time in Sekunden + ".txt" zusammen.

@ prime : Zuloggende Primzahl.
*/
void Log::logprime(unsigned long long prime) {
	/*Ich habe mich entschieden die Log-Datein nicht, wenn sie eine bestimme groesze erreichen zu wechseln,
	sonder wenn ein bestimme Anzahl an Zahlen gelogt wurde, den einen Counter mitlaufen zu lassen ist performanter.*/

	std::stringstream ss; //wird gebraucht um aus time einen String zu machen.
	static std::ofstream logPrime;	//Filedeskripteor
	static int maxCount = 1000000;	//Soviele PrimZahen werden in ein und die selbe Logdatei geschrieben.
	static int count = 0;			//Soviele PrimZahen wurden bereits in die Logdatei geschrieben.

	if (logPrime.is_open() && count < maxCount) {
		logPrime << prime << std::endl;
		count++;
	}
	else {
		if (count >= maxCount) {//Wenn der count >= maxCount ist muss ein ofs offen sein
			logPrime.close();
		}
		time_t t = time(0); // Systemzeit in sec.
		ss << t;     //time wird zu einem String convertirt.
		std::string dateiName = "./logPrime" + ss.str() + ".txt";
		logPrime.open(dateiName.c_str(), std::ios::app);
		logPrime << prime << std::endl;
		count = 1;
	}

}

/*
Logt wie heufig diese Funktion aufgerufen wurde, die Zahl wird dann einmal pro Sekunde in der Datei logTime.txt gesichert
zusammen mit der "maxPrime" Variable und den vergangenen Sekunden seit dem Start des Programmes.
Zusaetslich werden diese Informationen auch in einer Konsole ausgegeben.
*/
void Log::logtime() {
	static std::ofstream logTime; //Filedeskripteor
	static unsigned long long count = 0; //Zaehlt wie heufig die Funktion aufgerufen wurde. 
	static time_t st = time(0); //Zeit in Sekunden, wann diese Funktion das erste mal aufgerufen wurde.
	static time_t lastTime = time(0);	//Wird gebraucht um zupruefen ob eine Sekunde vergangen ist.
	time_t t = time(0);					//Wird gebraucht um zupruefen ob eine Sekunde vergangen ist.
	count++;
	if (t > lastTime) {
		lastTime = t;
		if (logTime.is_open()) {
			logTime << count << ":" << maxPrime << "	:	" << t - st << std::endl;//In Datei schreiben 
		}
		else {
			std::string dateiName = "./logTime.txt";
			logTime.open(dateiName.c_str(), std::ios::app);
			logTime << count << ":" << maxPrime << "	:	" << t - st << std::endl;//In Datei schreiben 
		}
		std::cout << count << ":" << maxPrime << "	:	" << ((t - st) / 60) << ":" << ((t - st) % 60) << std::endl;//Auf Console schreibe
	}
}
