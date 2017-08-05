#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <bitset>
#include <thread>
#include <mutex>

#ifdef __linux__
#include <unistd.h>
#endif

#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "tcpiptk.hpp"

static int connectedSocketfd;
static std::mutex fdWriteMutex;
void Communicator::run(){
    std::string ip;
    std::cout << "Please enter a valid ServerIP:\n>";
    getline(std::cin, ip);
    Communicator::run(ip);
}
//#ifdef __linux__
void Communicator::run(std::string ip) {
    int initPort = 30000;
    connectedSocketfd = tcpiptk::connectSocket(ip.c_str(), initPort);

    while(true){
        bool linkedListInitialized;
        void * message;
        unsigned long long prime;
        message = malloc(sizeof(unsigned long long));
        tcpiptk::getMessage(connectedSocketfd,message,sizeof(unsigned long long));
        std::memcpy(&prime, message, sizeof(unsigned long long));
        if(prime == 0){
            printf("Connection to Server lost!");
            close(connectedSocketfd);
            return;
        }
        //printf("Got a Message from Observer: %llu is definitely a prime.\n", prime);
        if (linkedListInitialized == false){
            LinkedList::initNode(head, prime);
            linkedListInitialized = true;
        }else{
            PrimeListLast = LinkedList::addNode(PrimeListLast, prime);
        }
        if(prime > maxPrime) maxPrime = prime;
    }
}

void Communicator::sendMessage(unsigned long long maybePrime, bool isLocalPrime, void * msgbuffer){
    //printf("I am telling the Observer, that %llu is %sa prime for me.\n", maybePrime, isLocalPrime ? "" : "not ");

    maybePrime += isLocalPrime ? 0 : 1; //Addiert den Boolean auf die fragliche Primzahl. Da maybePrime immer ungerade ist, geht das.
    //std::memcpy(msgbuffer, &maybePrime, sizeof(unsigned long long));
    fdWriteMutex.lock();
    tcpiptk::writeMessage(connectedSocketfd, &maybePrime, sizeof(unsigned long long));
    fdWriteMutex.unlock();
}
//#endif


