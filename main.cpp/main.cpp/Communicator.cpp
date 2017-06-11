#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "tcpiptk.hpp"




void Communicator::startListener() {

}
void Communicator::run() {
     /*   int initPort = 30000;
        int myfd = tcpiptk::connectSocket("192.168.188.32", initPort); //Verbinde mit der "Lobby"
        std::string message = tcpiptk::getMessage(myfd); //Empfange Nachricht. Diese enthält den port der statischen Verbindung.
        tcpiptk::closeAndShutdownSocket(myfd); //Schließt den Socket, den er nicht mehr braucht. (Verlässt die Lobby)
        myfd = tcpiptk::connectSocket("192.168.188.32", atoi(message.c_str())); //Verbindet sich mit dem neuen Port.
        tcpiptk::writeMessage(myfd, "Penis"); //Testnachricht gesendet.*/
}



