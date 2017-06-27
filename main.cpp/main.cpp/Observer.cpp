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
#include <cstring>
#include <map>

#ifdef __linux__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#endif

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "tcpiptk.hpp"
#include "Log.hpp"

//#ifdef __linux__
#define PORT    30000
#define MAXMSG  512

void Observer::run(){
    int expectedClientCount;
    std::cout << "How many Client do we expect?:\n>";
    std::cin >> expectedClientCount;
    Observer::run(expectedClientCount);
}
void Observer::run(int expectedClientCount) {
    void * msgbuffer = malloc(sizeof(unsigned long long) + sizeof(bool));
    unsigned long long maybePrime;
    bool isLocalPrime;

    std::map<unsigned long long, int> clientProcessingCounter; //Speichert im int, wie viele Clients sich zu der entsprechenden Zahl gemeldet haben.
    std::map<unsigned long long, bool> preliminaryPrimes; //Speichert vorläufig im Boolean ob die gegebene Zahl eine Primzahl ist oder nicht.
    std::map<unsigned long long, bool> securedPrimes; //Speichert im Boolean, ob die Zahl eine ist, oder nicht.
    unsigned long long primesSecuredUpTo = 1;

    int sock;
    fd_set active_fd_set, read_fd_set;
    socklen_t sizeT;

    /* Create the socket and set it up to accept connections. */
    sock = tcpiptk::createSocket(PORT);
    if (listen (sock, 1) < 0){
        perror ("listen");
        exit (EXIT_FAILURE);
    }

    /* Waits until everyone is connected. */
    int clientCount = 0;
    int nextCandidateInClientList = 0;
    int clientList[expectedClientCount];
    memset(clientList, 0, sizeof(int) * expectedClientCount);

    /* Prints the assigned address for each known network interface. */
    tcpiptk::getMyIP();

    /* Initialize the set of active sockets. */
    FD_ZERO (&active_fd_set);
    FD_SET (sock, &active_fd_set);
    do{
        /* Connection request on original socket. */
        int newSocket;
        newSocket = tcpiptk::acceptConnection(sock);
        if (newSocket > 1023){
            printf("Program Error: tcpiptk::acceptConnection() returned %i\n", newSocket);
        }
        FD_SET (newSocket, &active_fd_set);
        clientList[clientCount] = newSocket;
        clientCount++;
    }while(clientCount < expectedClientCount);
    //close(sock); //Da bin ich mir nicht sicher, ob das nötig ist.

    {//Initialisiert die Worker mit einigen Primzahlen.
        unsigned long long prePrime;
        for (int x=2; x<100; x++){
            for (int y=2; y<x; y++)
            {
                if (x % y == 0){
                    break;
                }else if (x == y+1){
                    prePrime = static_cast<unsigned long long>(x);
                    //Log::log(prePrime);
                    std::memcpy(msgbuffer, &prePrime, sizeof(unsigned long long));
                    tcpiptk::writeMessage(clientList[nextCandidateInClientList],msgbuffer,sizeof(unsigned long long));
                    nextCandidateInClientList = (nextCandidateInClientList + 1) % expectedClientCount;
                }
            }
        }
    }

    struct timeval tout;
    while (1){
        /* Block until input arrives on one or more active sockets. */
        read_fd_set = active_fd_set;
        int selectret = select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
        if (selectret < 0){
            perror ("select");
            exit (EXIT_FAILURE);
        }
        /* Service all the sockets with input pending. */
        for (const int &currentFileDescriptor : clientList){
            if (FD_ISSET (currentFileDescriptor, &read_fd_set)){
                /* Data arriving on an already-connected socket. */
                if (tcpiptk::getMessage(currentFileDescriptor, msgbuffer, sizeof(unsigned long long) + sizeof(bool)) == 0){
                    fprintf (stderr, "Server: connection lost.\n");
                    close (currentFileDescriptor);
                    FD_CLR (currentFileDescriptor, &active_fd_set);
                    return;
                }else{
                    std::memcpy(&maybePrime, msgbuffer, sizeof(unsigned long long));
                    std::memcpy(&isLocalPrime, msgbuffer + sizeof(unsigned long long), sizeof(bool));
                    //printf("Got a Solution: %llu is %sa prime for a  Client.\n", maybePrime, isLocalPrime ? "" : "not ");
                    if(++clientProcessingCounter[maybePrime] == 1 || preliminaryPrimes[maybePrime]){
                        preliminaryPrimes[maybePrime] = isLocalPrime;
                    }
                    if(clientProcessingCounter[maybePrime] == clientCount){
						securedPrimes[maybePrime] = preliminaryPrimes[maybePrime];
						preliminaryPrimes.erase(maybePrime);
						clientProcessingCounter.erase(maybePrime);
                        for(auto it = securedPrimes.begin(); it != securedPrimes.end(); it = securedPrimes.erase(it)){
                            if(it->first == primesSecuredUpTo + 2){
                                primesSecuredUpTo += 2;
                                if(it->second){
                                    maxPrime = it->first;
                                    Log::log(it->first);
                                    //printf("I am telling a Client, that %llu is definitely a prime.\n", it->first);
                                    memcpy(msgbuffer,&(it->first),sizeof(unsigned long long));
                                    tcpiptk::writeMessage(clientList[nextCandidateInClientList],msgbuffer,sizeof(unsigned long long));
                                    nextCandidateInClientList = (nextCandidateInClientList + 1) % expectedClientCount;
                                }
                            }else{
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Observer::addCommunicator() {

}
void Observer::deleteCommunicator() {

}
void Observer::startListener() {

}
void Observer::initCommunicator() {

}
//#endif
