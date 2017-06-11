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
#include "Log.hpp"




void Observer::run() {
/*
	if(fork() == 0){
        int inputfd = tcpiptk::createSocket(23355);
        std::string message = tcpiptk::getMessage(inputfd);
        std::cout << message << std::endl;
    }else{
        sleep(2);
        int myfd = tcpiptk::connectSocket("192.168.188.32", 23355);
        tcpiptk::writeMessage(myfd,"Testnachricht");
    }*/
}


void Observer::addCommunicator() {

}
void Observer::deleteCommunicator() {

}
void Observer::startListener() {

}
void Observer::initCommunicator() {

}


