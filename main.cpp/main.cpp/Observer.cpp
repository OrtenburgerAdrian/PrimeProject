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

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"



void Observer::run() {

}


void Observer::addCommunicator() {

}
void Observer::deleteCommunicator() {

}
void Observer::startListener() {

}
/**ich habe mich entschiedern die logdatein nicht wenn sie eine bestimme grösze erreichen zu wechseln,
sonder wenn ein bestimme anzahl an zahlen hinen geschrieben wurden, einen counter mitlaufen zu lassen ist performanter**/
int Observer::logPrime(unsigned long long prim) {
	static std::ofstream ofs;
	static int maxCount = 100000; // soviele PrimZahen werden in ein und die selbe Logdatei geschrieben 
	static int count = 0;			//soviele PrimZahen wurden bereits in die Logdatei geschrieben
	if (ofs.is_open() && count < maxCount) {
		ofs << prim << std::endl;
		count++;
	}
	else if (count >= maxCount) {//wenn der count >= maxCount ist muss ein ofs offen sein
		ofs.close();
		time_t t = time(0); // Systemzeit in sec
		std::string dateiName = "./log" + std::to_string(t) + ".txt";
		ofs.open(dateiName, std::ios::app);
		ofs << prim << std::endl;
		count = 1;
	}
	else
	{ // wird nur mein ersten mal aufrufen der logFunktion ausgeführ, da kein FD geschlossen werden muss, es war ja noch keiner offen
		time_t t = time(0); // Systemzeit in sec
		std::string dateiName = "./log" + std::to_string(t) + ".txt";
		ofs.open(dateiName, std::ios::app);
		ofs << prim << std::endl;
		count = 1;
	}
	return 0;
}
void Observer::initCommunicator() {

}


