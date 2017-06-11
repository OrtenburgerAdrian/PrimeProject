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
#include <time.h>
#include <dos.h>
#include <windows.h>
#include <iostream> 
#include <stdlib.h>
#include <sstream>

#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

static std::ofstream logDebugg;

void Log::logerror(std::string Nachricht){
	static std::stringstream ss;
	static time_t t;
	t = time(0); // Systemzeit in sec
	ss << t;     //time wird zu einem String convertirt


	if (logDebugg.is_open()) {
		logDebugg << ss.str() << "	: "<< Nachricht << "	: " <<  std::strerror(errno) << std::endl;
		std::cout << ss.str() << "	: " << Nachricht << "	: " << std::strerror(errno) << std::endl;

	}
	else {

		std::string dateiName = "./logDebugg" + ss.str() + ".txt";
		logDebugg.open(dateiName.c_str(), std::ios::app);
		logDebugg << ss.str() << "	: " << Nachricht << "	: " << std::strerror(errno) << std::endl;
		std::cout << ss.str() << "	: " << Nachricht << "	: " << std::strerror(errno) << std::endl;
	}
}

void Log::log(unsigned long long prime){
	/**ich habe mich entschiedern die logdatein nicht, wenn sie eine bestimme größe erreichen zu wechseln,
	sonder wenn ein bestimme anzahl an zahlen hinen geschrieben wurden, einen counter mitlaufen zu lassen ist performanter.  **/
	static std::stringstream ss; //wird gebraucht um aus time einen String zu machen. 
	static std::ofstream logPrime; //filedeskripteor 
	static int maxCount = 100000; // soviele PrimZahen werden in ein und die selbe Logdatei geschrieben
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
void Log::log(std::string Nachricht){
	struct tm *localtime(const time_t *timer);

	static std::stringstream ss;
	static time_t t;
	t = time(0); // Systemzeit in sec
	ss << t;     //time wird zu einem String convertirt


	if (logDebugg.is_open()) {
		logDebugg << ss.str() << "	: "<< Nachricht << std::endl;
		std::cout << ss.str() << "	: " << Nachricht << std::endl;
	}
	else {
				    
		std::string dateiName = "./logDebugg" + ss.str() + ".txt";
		logDebugg.open(dateiName.c_str(), std::ios::app);
		logDebugg << ss.str() << "	: " << Nachricht << std::endl;
		std::cout << ss.str() << "	: " << Nachricht << std::endl;
	}
}








