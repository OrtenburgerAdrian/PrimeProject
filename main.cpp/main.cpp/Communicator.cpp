#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <bitset>
#include <unistd.h>

#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "tcpiptk.hpp"

static int connectedSocketfd;

void Communicator::startListener() {

}
void Communicator::run() {
    int initPort = 30000;
    connectedSocketfd = tcpiptk::connectSocket("192.168.188.32", initPort); //Verbinde mit der "Lobby"
    /*std::string message = tcpiptk::getMessage(myfd); //Empfange Nachricht. Diese enthält den port der statischen Verbindung.
    tcpiptk::closeAndShutdownSocket(myfd); //Schließt den Socket, den er nicht mehr braucht. (Verlässt die Lobby)
    myfd = tcpiptk::connectSocket("192.168.188.32", atoi(message.c_str())); //Verbindet sich mit dem neuen Port.
    tcpiptk::writeMessage(myfd, "Penis"); //Testnachricht gesendet.*/
    for( int i = 0; i < 10; i++){
        Communicator::sendMessage(static_cast<unsigned long long>(i) , true);
        sleep(1);
    }
}

void Communicator::sendMessage(unsigned long long maybePrime, bool isPrime){
    printf("%llu: %i\n", maybePrime, isPrime);
    size_t length = sizeof(unsigned long long) + sizeof(bool);
    void * msgbuffer = malloc(512);
    std::memcpy(msgbuffer, &maybePrime, sizeof(unsigned long long));
    std::memcpy(msgbuffer + sizeof(unsigned long long), &isPrime, sizeof(bool));
    tcpiptk::writeMessage(connectedSocketfd, msgbuffer, length);
}



