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

static std::ofstream logDebug;


 void Log::log(unsigned long long prime) {
	 //Log::logprime(prime);
	 Log::logtime();
	}

void Log::logprime(unsigned long long prime){
	//ich habe mich entschiedern die logdatein nicht, wenn sie eine bestimme größe erreichen zu wechseln,
	//sonder wenn ein bestimme anzahl an zahlen hinen geschrieben wurden, einen counter mitlaufen zu lassen ist performanter.

	std::stringstream ss; //wird gebraucht um aus time einen String zu machen.
	static std::ofstream logPrime; //filedeskripteor
	static int maxCount = 1000000; // soviele PrimZahen werden in ein und die selbe Logdatei geschrieben
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




void Log::logtime() {
	static std::ofstream logTime; //filedeskripteor
	static unsigned long long count = 0;
	static time_t st = time(0);
	static time_t lastTime = time(0);
	time_t t = time(0);
	count++;
	if (t > lastTime) {
		lastTime = t;
		if (logTime.is_open()) {
			logTime << count<<":"<< maxPrime << "	:	" << t - st << std::endl;
		}
		else {
            std::string dateiName = "./logTime.txt";
			logTime.open(dateiName.c_str(), std::ios::app);
			logTime << count << ":" << maxPrime << "	:	" << t - st << std::endl;
		}
		std::cout << count << ":" << maxPrime << "	:	" << ((t - st)/60)<< ":"<< ((t - st) % 60) << std::endl;
	}
}
