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


#ifdef __linux__
#include <unistd.h>
#endif


#include <vector>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "tcpiptk.hpp"
#include "Log.hpp"

void Observer::run() {
  /*  int initPort = 30000;
    std::vector<int> communicators;

    //Servercode
    int incomingSocketfd = tcpiptk::acceptConnection(tcpiptk::createSocket(initPort)); //Öffnet Lobby, um Ports zu verteilen.
    int newPort = initPort + 1 + communicators.size(); //Ermittelt einen unbenutzten Port.
    std::stringstream ss; //Aufwendigstes IntToString conversion ever.
    ss << newPort;
    tcpiptk::writeMessage(incomingSocketfd, ss.str().c_str()); //Schickt den ermittelten Port an den Anfragenden.
    tcpiptk::closeAndShutdownSocket(incomingSocketfd); //Hier müsste der Port neu geöffnet werden und eine Schleife greifen. Aktuell schließe ich noch.
    communicators.push_back(tcpiptk::acceptConnection(tcpiptk::createSocket(newPort))); //Verbindet sich mit dem Client am neuen Port und schreibt die Nachricht in den Vector.
    std::cout << tcpiptk::getMessage(communicators.back()) << std::endl; //Empfängt Testnachricht und gibt diese aus.
	*/
}

void Observer::addCommunicator() {

}
void Observer::deleteCommunicator() {

}
void Observer::startListener() {

}
void Observer::initCommunicator() {

}


