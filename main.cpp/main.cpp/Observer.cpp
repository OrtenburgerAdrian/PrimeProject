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
#include <sstream>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "tcpiptk.hpp"

void Observer::run() {
    if(fork() == 0){
        int inputfd = tcpiptk::createSocket(23355);
        std::string message = tcpiptk::getMessage(inputfd);
        std::cout << message << std::endl;
    }else{
        sleep(2);
        int myfd = tcpiptk::connectSocket("192.168.188.32", 23355);
        tcpiptk::writeMessage(myfd,"Testnachricht");
    }
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
    std::stringstream ss;
	static std::ofstream ofs;
	static int maxCount = 100000; // soviele PrimZahen werden in ein und die selbe Logdatei geschrieben
	static int count = 0;			//soviele PrimZahen wurden bereits in die Logdatei geschrieben
	if (ofs.is_open() && count < maxCount) {
		ofs << prim << std::endl;
		count++;
	}
	else{
        if (count >= maxCount) {//wenn der count >= maxCount ist muss ein ofs offen sein
            ofs.close();
		}
		time_t t = time(0); // Systemzeit in sec
		ss << t;
		std::string dateiName = "./log" + ss.str() + ".txt";
		ofs.open(dateiName.c_str(), std::ios::app);
		ofs << prim << std::endl;
		count = 1;
	}
	return 0;
}
void Observer::initCommunicator() {

}


