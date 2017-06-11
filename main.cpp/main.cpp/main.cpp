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
#include <unistd.h>

#include <iostream>
#include <stdlib.h>

#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"

#ifdef _WIN32
    #include <dos.h>
    #include <windows.h>
#endif

bool threadActive[16];
bool threadNotDelete[16];
bool threadIsPrime[16];
unsigned long long threadToCalculate[16];
int nuberOfWorker;
LinkedList primesList;



int main(int argc, char *argv[]) {
	//programm init

#ifdef _WIN32
                SYSTEM_INFO s_systeminfo;
				GetNativeSystemInfo(&s_systeminfo);
				int nuberOfWorker = s_systeminfo.dwNumberOfProcessors - 1; // -1, damit der Comunicator im besten fall einen eigenen Core bekommen kann.
#elif __linux__
				int nuberOfWorker = sysconf(_SC_NPROCESSORS_ONLN) - 1;   // -1, damit der Comunicator im besten fall einen eigenen Core bekommen kann.
#endif
				std::fill_n(threadActive, nuberOfWorker, false);// screibt in jedes feld false rein , kein thread arbeitet, bis sein Feld auf true gesetzt ist.
				std::fill_n(threadIsPrime, nuberOfWorker, false);// screibt in jedes feld false rein
				std::fill_n(threadNotDelete, nuberOfWorker, true);// screibt in jedes feld true rein
				std::fill_n(threadToCalculate, nuberOfWorker, 0);// screibt in jedes feld 0 rein

	Worker::start();


	if (argc <= 1) {
		std::cout << " Inadequate transfer parameters" << std::endl;
	}
	else if (argc > 2) {
		std::cout << " Too many transfer parameters" << std::endl;
	}
	else {
		std::string arg1 = argv[1];
		if (arg1 == "observer") {
			Observer::run();
			std::cout << " run observer.run()" << std::endl;
		}
		else if (arg1 == "communicator") {
			Communicator::run();
			std::cout << " run communicator.run();" << std::endl;
		}
		else {
			std::cout << " Incorrect transfer parameters     " << std::endl;
		}
	}
	while (true)
	{

	}

}
