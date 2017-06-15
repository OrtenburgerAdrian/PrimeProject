#pragma once
#include <stdio.h>
#include <string.h>
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
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <string.h>
#include <locale>
#include <errno.h>
#include <cerrno>

#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

#ifdef _WIN32
#include <dos.h>
#include <windows.h>
#endif
static std::ofstream logDebug;

void Log::logerror(std::string Nachricht) {
	static std::stringstream ss;
	static time_t t;
	t = time(0); // Systemzeit in sec
	ss << t;     //time wird zu einem String convertirt

	char i[100];


	if (logDebug.is_open()) {
        logDebug << ss.str() << "	: " << Nachricht << "	: " << strerror(errno) << std::endl;
		std::cout << ss.str() << "	: " << Nachricht << "	: " << strerror(errno) << std::endl;

	}
	else {

		std::string dateiName = "./logDebugg" + ss.str() + ".txt";
		logDebug.open(dateiName.c_str(), std::ios::app);
		logDebug << ss.str() << "	: " << Nachricht << "	: " << strerror(errno) << std::endl; //strerror_s(i, 100, errno)
		std::cout << ss.str() << "	: " << Nachricht << "	: " << strerror(errno) << std::endl;
	}
}

void Log::log(unsigned long long prime) {
	Log::logtime();
	/**ich habe mich entschiedern die logdatein nicht, wenn sie eine bestimme gr��e erreichen zu wechseln,
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
void Log::log(std::string Nachricht) {
	struct tm *localtime(const time_t *timer);

	static std::stringstream ss;
	static time_t t;
	t = time(0); // Systemzeit in sec
	ss << t;     //time wird zu einem String convertirt


	if (logDebug.is_open()) {
		logDebug << ss.str() << "	: " << Nachricht << std::endl;
		std::cout << ss.str() << "	: " << Nachricht << std::endl;
	}
	else {

		std::string dateiName = "./logDebugg" + ss.str() + ".txt";
		logDebug.open(dateiName.c_str(), std::ios::app);
		logDebug << ss.str() << "	: " << Nachricht << std::endl;
		std::cout << ss.str() << "	: " << Nachricht << std::endl;
	}
}
void Log::logtime() {




	static std::ofstream logTime; //filedeskripteor
	static int maxCount = 100000; // soviele PrimZahen werden in ein und die selbe Logdatei geschrieben
	static unsigned long long count = 0;			//soviele PrimZahen wurden bereits in die Logdatei geschrieben
	time_t t = time(0);
	count++;
	if (count % 1000 == 0 || count == 750 || count == 500 || count == 250 || count >= 249) {
		if (logTime.is_open()) {
			logTime << count << "		:	" << t << std::endl;

		}
		else {


			std::string dateiName = "./logTime.txt";
			logTime.open(dateiName.c_str(), std::ios::app);
			logTime << count << "		:	" << t << std::endl;
		}
	}
}





