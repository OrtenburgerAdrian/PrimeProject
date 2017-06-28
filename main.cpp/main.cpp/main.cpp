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

#include <iostream>
#include <stdlib.h>

#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"
#include "SingelCore.hpp"
#include "MultiCore.hpp"

#if defined _WIN64
#include <dos.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>

#endif


int numberOfWorker;
unsigned long long maxPrime;
LinkedList primesList;
LinkedList *head = &primesList;
LinkedList* PrimListLast = head;

int main(int argc, char *argv[]) {

#if defined _WIN64
	SYSTEM_INFO s_systeminfo;
	GetNativeSystemInfo(&s_systeminfo);
	numberOfWorker = s_systeminfo.dwNumberOfProcessors - 1; // -1, damit der Comunicator im besten fall einen eigenen Core bekommen kann.
#elif __linux__
	numberOfWorker = sysconf(_SC_NPROCESSORS_ONLN) - 1;   // -1, damit der Comunicator im besten fall einen eigenen Core bekommen kann.
#endif
    //numberOfWorker = 2; //Uncomment to manually set number of working threads.
    maxPrime = 0;
	SingelCore::run();


#if defined __linux__
	if (argc <= 1) {
		std::cout << " Inadequate transfer parameters" << std::endl;
	}
	else if (argc > 3) {
		std::cout << " Too many transfer parameters" << std::endl;
	}


	std::string arg1 = argv[1];
    if (arg1 == "multicore") {
        MultiCore::run();
        std::cout << " run multicore.run();" << std::endl;
        int zahl;
        while(true){std::cin >> zahl;}
    }else if (arg1 == "singlecore") {
        SingelCore::run();
        std::cout << " run singelcore.run();" << std::endl;
    }else if (arg1 == "observer"){
        if (argc == 3){
            Observer::run(atoi(argv[2]));
        }else{
            Observer::run();
        }
    }else if (arg1 == "communicator") {
        Worker::start();
        if (argc == 3){
            Communicator::run(argv[2]);
        }else{
            Communicator::run();
        }
    }else {
        std::cout << " Incorrect transfer parameters     " << std::endl;
    }
    return 0;

#endif
}
