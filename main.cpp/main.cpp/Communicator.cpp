#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <bitset>
#include <thread>

#ifdef __linux__
#include <unistd.h>
#endif

#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "tcpiptk.hpp"

static int connectedSocketfd;

//#ifdef __linux__
void Communicator::run() {
    int initPort = 30000;
    std::string ip = "192.168.188.32";
    //uncomment this to enable manual IP input
    //std::cout << "Please enter a valid ServerIP (" + ip + " is default):\n>";
    //getline(std::cin, ip);
    connectedSocketfd = tcpiptk::connectSocket(ip.c_str(), initPort);

    while(true){
        bool linkedListInitialized;
        void * message;
        unsigned long long prime;
        message = malloc(sizeof(unsigned long long));
        tcpiptk::getMessage(connectedSocketfd,message,sizeof(unsigned long long));
        std::memcpy(&prime, message, sizeof(unsigned long long));
        //printf("Got a Message from Observer: %llu is definitely a prime.\n", prime);
        if (linkedListInitialized == false){
            LinkedList::initNode(head, prime);
            linkedListInitialized = true;
        }else{
            PrimListLast = LinkedList::addNode(PrimListLast, prime);
        }
        if(prime > maxPrime) maxPrime = prime;
    }
}

void Communicator::sendMessage(unsigned long long maybePrime, bool isLocalPrime){
    size_t length = sizeof(unsigned long long) + sizeof(bool);
    void * msgbuffer = malloc(length);
    std::memcpy(msgbuffer, &maybePrime, sizeof(unsigned long long));
    std::memcpy(msgbuffer + sizeof(unsigned long long), &isLocalPrime, sizeof(bool));
    //printf("I am telling the Observer, that %llu is %sa prime for me.\n", maybePrime, isLocalPrime ? "" : "not ");
    tcpiptk::writeMessage(connectedSocketfd, msgbuffer, length);
    free(msgbuffer);
}
//#endif


