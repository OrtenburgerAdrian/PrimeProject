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
#include <semaphore.h>
#include <thread>
#include <mutex>

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

static int rbuff_size;
static int msg_size;
static void* rbuff;
static sem_t writeSem;
static sem_t readSem;
static std::mutex counterMutex;
static std::mutex getMessageMutex;

static int clientCount;
static int nextCandidateInClientList;
static std::vector<int> clientList;
static fd_set active_fd_set;

/**
 *  Wir speichern die Anzahl der gemeldeten Clients UND wie viele davon true gemeldet haben.
 *  Client meldet sich int + 1000 UND wenn true int + 1
 *  Rückwärts können wir also auflösen...
 *  Anzahl der zurückgemeldeten Clients: int clients = clientProcessingCounter[maybePrime] / 1000
 *  Anzahl der positiven Rückmeldungen:  int bools = clientProcessingCounter[maybePrime] % 1000
 */
static std::map<unsigned long long, int> clientProcessingCounter; //Speichert im int, wie viele Clients sich zu der entsprechenden Zahl gemeldet haben und codiert den Bool mit!

void Observer::run(){
    int expectedClientCount;
    std::cout << "How many Client do we expect?:\n>";
    std::cin >> expectedClientCount;
    Observer::run(expectedClientCount);
}

void Observer::run(int expectedClientCount) {
    void * msgbuffer = malloc(sizeof(unsigned long long));
    int sock;

    /* Create the socket and set it up to accept connections. */
    sock = tcpiptk::createSocket(PORT);
    if (listen (sock, 1) < 0){
        perror ("listen");
        exit (EXIT_FAILURE);
    }

    /* Waits until everyone is connected. */
    clientCount = 0;
    nextCandidateInClientList = 0;

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
        clientList.push_back(newSocket);
        clientCount++;
    }while(clientCount < expectedClientCount);

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
                    nextCandidateInClientList = (nextCandidateInClientList + 1) % clientCount;
                }
            }
        }
    }
    //Initialisiere Ringbuffer
    rbuff_size = 1000000; //...times the size of a message (usually 9 Byte)
    msg_size = sizeof(unsigned long long) + sizeof(bool);
    rbuff = malloc(msg_size * rbuff_size);
    sem_init(&writeSem, 0, rbuff_size);
    sem_init(&readSem, 0, 0);

    std::thread listenerThread(Observer::run_listener);
    Observer::run_teller();
}

void Observer::run_listener(){
    void * msgbuffer = malloc(sizeof(unsigned long long) + sizeof(bool));
    unsigned long long maybePrime;
    bool isLocalPrime;

    void * writePointer = rbuff;

    while (true){
        /* Block until input arrives on one or more active sockets. */
        fd_set read_fd_set = active_fd_set;
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
                    //Schreibe Nachricht in Ringbuffer
                    sem_wait(&writeSem);
                    std::memcpy(writePointer, msgbuffer, sizeof(unsigned long long));
                    writePointer += sizeof(unsigned long long);
                    std::memcpy(writePointer, msgbuffer + sizeof(unsigned long long), sizeof(bool));
                    sem_post(&readSem);
                    writePointer += sizeof(bool);
                    if (writePointer > (rbuff + (msg_size * rbuff_size))){
                        std::cout << "You fucked up, ay!" << std::endl;
                    }
                    if (writePointer == (rbuff + (msg_size * rbuff_size))){
                        writePointer = rbuff;
                    }
                }
            }
        }
    }
}
void Observer::run_teller(){
    void * msgbuffer = malloc(sizeof(unsigned long long));
    unsigned long long primesSecuredUpTo = 1;

    void * readPointer = rbuff;
    unsigned long long ull_read;
    bool bool_read;
    unsigned long long nextCheck;
    nextCheck = primesSecuredUpTo + 2;
    int cpcCounter;
    while(true){
        int msgDelayMax = 400000;
        int msgDelayCount = (maxPrime - 1) * 2;
        msgDelayCount = msgDelayCount > msgDelayMax ? msgDelayMax : msgDelayCount;
        for(int i = 0; i < msgDelayCount; i++){
            sem_wait(&readSem);
            memcpy(&ull_read, readPointer, sizeof(unsigned long long));
            readPointer += sizeof(unsigned long long);
            memcpy(&bool_read, readPointer, sizeof(bool));
            sem_post(&writeSem);
            readPointer += sizeof(bool);
            //printf("Got a Solution: %llu is %sa prime for a  Client.\n", ull_read, bool_read ? "" : "not ");
            if (readPointer > (rbuff + (msg_size * rbuff_size))){
                std::cout << "You fucked up while reading, ay!" << std::endl;
            }
            if (readPointer == (rbuff + (msg_size * rbuff_size))){
                readPointer = rbuff;
            }

            //Encodes the results like documented.
            clientProcessingCounter[ull_read] += bool_read ? 1001 : 1000;
        }

        //Goes through the Data and sends the packets in the right order (std::map is sorting for us)
        cpcCounter = clientProcessingCounter[nextCheck];
        while(static_cast<int>(cpcCounter / 1000) == clientCount){ //Haben sich alle Clienten zurückgemeldet?;
            clientProcessingCounter.erase(nextCheck);
            if((cpcCounter % 1000) == clientCount){ //Haben alle Clienten true gemeldet?
                maxPrime = nextCheck;
                Log::log(nextCheck);
                memcpy(msgbuffer, &nextCheck, sizeof(unsigned long long));
                tcpiptk::writeMessage(clientList[nextCandidateInClientList],msgbuffer,sizeof(unsigned long long));
                nextCandidateInClientList = (nextCandidateInClientList + 1) % clientCount;
            }
            primesSecuredUpTo = nextCheck;
            nextCheck = primesSecuredUpTo + 2;
            cpcCounter = clientProcessingCounter[nextCheck];
        }
    }
}
//#endif
