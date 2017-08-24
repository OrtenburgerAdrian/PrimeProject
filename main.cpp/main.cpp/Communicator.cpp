//Benjamin
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
static std::mutex fdWriteMutex; //Nötig, da das senden von Nachrichten anscheinend nicht Threadsicher ist.

// Fragt noetige Parameter ab.
void Communicator::run(){
    std::string ip;
    std::cout << "Please enter a valid ServerIP:\n>";
    getline(std::cin, ip);
    Communicator::run(ip);
}

// Initialisiert die Communication mit dem Observer und nimmt Nachrichten an.
void Communicator::run(std::string ip) {
    int initPort = 30000;
    connectedSocketfd = tcpiptk::connectSocket(ip.c_str(), initPort);

    bool linkedListInitialized = false; //Der Umgang mit Adrians LinkedList ist zwar sonderbar, funktioniert aber.
    //void * message = malloc(sizeof(unsigned long long));
    unsigned long long prime;

    // Receiving loop.
    while(true){
        tcpiptk::getMessage(connectedSocketfd,&prime,sizeof(unsigned long long)); //Empfängt die Nachricht.
        if(prime == 0){ //Wenn 0 empfangen wird, wurde der Socket vom Observer geschlossen.
            printf("Connection to Server lost!");
            close(connectedSocketfd);
            return;
        }
        //printf("Got a Message from Observer: %llu is definitely a prime.\n", prime); //Nützlich für Tests.
        if (linkedListInitialized == false){ //Initialisiert die LinkedList...
            LinkedList::initNode(head, prime);
            linkedListInitialized = true;
        }else{
            PrimeListLast = LinkedList::addNode(PrimeListLast, prime);
        }
        if(prime > maxPrime) maxPrime = prime; //MaxPrime ist in main.cpp definiert und beschreibt die höchste Primzahl, die der Prozess kennt.
        //Nach meinem Verständnis müsste eine eingehende Nachricht IMMER eine neue höchste Primzahl enthalten, hier fasse ich aber nichts mehr an...
    }
}

//Diese Funktion wird von den Threads genutzt, um dem Observer mitzuteilen, ob eine Zahl für den Prozess eine Primzahl ist.
void Communicator::sendMessage(unsigned long long maybePrime, bool isLocalPrime){
    //printf("I am telling the Observer, that %llu is %sa prime for me.\n", maybePrime, isLocalPrime ? "" : "not "); //Nützlich für Tests.

    //Um das Netzwerk und den Observer zu entlasten, kodieren wir den Boolean in die Zahl. Das geht nur, weil maybePrime immer ungerade ist.
    maybePrime += isLocalPrime ? 0 : 1; //Addiert den Boolean auf die fragliche Primzahl.
    fdWriteMutex.lock();
    tcpiptk::writeMessage(connectedSocketfd, &maybePrime, sizeof(unsigned long long)); //Mit hoher wahrscheinlichkeit nicht Thread-Safe, deshalb der Mutex.
    fdWriteMutex.unlock();
}


