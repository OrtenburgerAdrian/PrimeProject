#pragma once
#include "Log.hpp"
/*Um zuentscheiden, welche Logfunktionen gebraucht werden, */
 void Log::log(unsigned long long prime) {
	 ///Log::logprime(prime); 
	 Log::logtime();
	}


 /*
 Logt die übergeben Zahl in .txt Datein, 1.000.000 Zahlen pro Datei, damit die Datei nicht zugroß wird.
 Der Name dieser Datein setzt sich aus "logPrim" + PC-Standard-Time in sec + ".txt"

 @prime : zu loggende Primzahl
 */
void Log::logprime(unsigned long long prime){
	//ich habe mich entschiedern die logdatein nicht, wenn sie eine bestimme größe erreichen zu wechseln,
	//sonder wenn ein bestimme anzahl an zahlen hinen geschrieben wurden, einen counter mitlaufen zu lassen ist performanter.

	std::stringstream ss; //wird gebraucht um aus time einen String zu machen.
	static std::ofstream logPrime;	//filedeskripteor
	static int maxCount = 1000000;	//soviele PrimZahen werden in ein und die selbe Logdatei geschrieben
	static int count = 0;			//soviele PrimZahen wurden bereits in die Logdatei geschrieben

	if (logPrime.is_open() && count < maxCount) {
		logPrime << prime << std::endl;
		count++;
	}
	else {
		if (count >= maxCount) {//wenn der count >= maxCount ist muss ein ofs offen sein
			logPrime.close();
		}
		time_t t = time(0); // Systemzeit in sec
		ss << t;     //time wird zu einem String convertirt
		std::string dateiName = "./logPrime" + ss.str() + ".txt";
		logPrime.open(dateiName.c_str(), std::ios::app);
		logPrime << prime << std::endl;
		count = 1;
	}

}

/*
Logt wie heufig diese Funktion aufgerufen wird, die Zahl wird dann einmal pro Sekunde in der Datei logTime.txt gesichert
zusammen mit der "maxPrime" Variable und den vergangenen Sekunden seit dem Start des Programmes.
Zusätslich werden diese Informationen auch in einer Konsole ausgegeben.
*/
void Log::logtime() {
	static std::ofstream logTime; //Filedeskripteor
	static unsigned long long count = 0; //Zählt wie heufig die Funktion aufgerufen wurde. 
	static time_t st = time(0); //Zeit in Sekunden, wann diese Funktion das erste mal aufgerufen wurde.
	static time_t lastTime = time(0);	//Wird gebraucht um zuprüfen ob eine Sekunde vergangen ist.
	time_t t = time(0);					//Wird gebraucht um zuprüfen ob eine Sekunde vergangen ist.
	count++;
	if (t > lastTime) {
		lastTime = t;
		if (logTime.is_open()) {
			logTime << count<<":"<< maxPrime << "	:	" << t - st << std::endl;//In Datei schreiben 
		}
		else {
            std::string dateiName = "./logTime.txt";
			logTime.open(dateiName.c_str(), std::ios::app);
			logTime << count << ":" << maxPrime << "	:	" << t - st << std::endl;//In Datei schreiben 
		}
		std::cout << count << ":" << maxPrime << "	:	" << ((t - st)/60)<< ":"<< ((t - st) % 60) << std::endl;//Auf Console schreibe
	}
}
