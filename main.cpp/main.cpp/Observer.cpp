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
    rbuff_size = 1000000; //...times the size of a message (usually 8 Byte)
    msg_size = sizeof(unsigned long long);
    rbuff = malloc(msg_size * rbuff_size);
    sem_init(&writeSem, 0, rbuff_size);
    sem_init(&readSem, 0, 0);

    std::thread listenerThread(Observer::run_listener);
    Observer::run_teller();
}

void Observer::run_listener(){
    void * msgbuffer = malloc(sizeof(unsigned long long));
    //unsigned long long maybePrime;
    //bool isLocalPrime;

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
                if (tcpiptk::getMessage(currentFileDescriptor, msgbuffer, sizeof(unsigned long long)) == 0){
                    fprintf (stderr, "Server: connection lost.\n");
                    close (currentFileDescriptor);
                    FD_CLR (currentFileDescriptor, &active_fd_set);
                    return;
                }else{
                    //Schreibe Nachricht in Ringbuffer
                    sem_wait(&writeSem);
                        std::memcpy(writePointer, msgbuffer, sizeof(unsigned long long));
                    sem_post(&readSem);

                    writePointer += sizeof(unsigned long long);

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

    void * readPointer = rbuff;
    unsigned long long ull_read;
    bool bool_read;
    unsigned long long nextCheck = 3;
    int cpcCounter;

    /**
     *  Wir speichern die Anzahl der gemeldeten Clients UND wie viele davon true gemeldet haben.
     *  Client meldet sich int + 1000 UND wenn true int + 1
     *  Rückwärts können wir also auflösen...
     *  Anzahl der zurückgemeldeten Clients: int clients = clientProcessingCounter[maybePrime] / 1000
     *  Anzahl der positiven Rückmeldungen:  int bools = clientProcessingCounter[maybePrime] % 1000
     */
    //static std::map<unsigned long long, int> clientProcessingCounter; //Speichert im int, wie viele Clients sich zu der entsprechenden Zahl gemeldet haben und codiert den Bool mit!
    int lazyRingBufferSize = 250000;
    int lazyRingBuffer[lazyRingBufferSize] = {0}; //wird quasi als Ringbuffer benutzt.
    int lazyRingBufferBaseIndex = 0;

    /**
        Innerhalb dieser Schleife gibt es zwei Teile, die im Wechsel durchlaufen:
            1. Die Vorverarbeitung der gespeicherten Daten aus dem echten Ringbuffer, die vom TCP/IP-Empfänger geschrieben wird.
            2. Das Interpretieren der vorverarbeiteten Zahlen und versenden der Primzahlen.
    **/
    while(true){
        //int msgDelayMax = 400000;
        //int msgDelayCount = (maxPrime - 1) * 2;
        //msgDelayCount = msgDelayCount > msgDelayMax ? msgDelayMax : msgDelayCount; //msgDelayCount beschränkt die Anzahl der Nachrichten die in einer Iteration gelesen werden. Anfangs ist das Notwendig.
        //for(int i = 0; i < msgDelayCount; i++){
        int readSemValue;
        do{
            sem_wait(&readSem);
                memcpy(&ull_read, readPointer, sizeof(unsigned long long));
            sem_post(&writeSem);

            readPointer += sizeof(unsigned long long);

            bool_read = (ull_read % 2) == 1 ? true : false; //Decodierd den Boolean aus der Zahl: Wenn die Zahl ungerade ist, dann war der boolean beim Encodieren 0 (also true);
            ull_read -= bool_read ? 0 : 1; //Zieht den boolean von unserer Zahl ab, falls dieser eincodierd wurde. (Ansonsten passiert nichts, weil bool_read 0 ist.)


            //printf("Got a Solution: %llu is %sa prime for a  Client.\n", ull_read, bool_read ? "" : "not ");
            if (readPointer > (rbuff + (msg_size * rbuff_size))){
                std::cout << "You fucked up while reading, ay!" << std::endl;
            }
            if (readPointer == (rbuff + (msg_size * rbuff_size))){
                readPointer = rbuff;
            }

            //Encodes the results like documented.
            //clientProcessingCounter[ull_read] += bool_read ? 1001 : 1000;
            int index = lazyRingBufferBaseIndex + ((ull_read - nextCheck) / 2); //Funktioniert, weil beide Zahlen ungerade sind.

            if (index >= (lazyRingBufferSize + lazyRingBufferBaseIndex)){ //Wenn der Index zu groß wird, haben wir verkackt. Probieren wir es erstmal ohne Semaphor...
                fprintf (stderr, "lazyBufferOverflow, idiot!");
                return;
            }

            index = index % lazyRingBufferSize; //beachtet die "echte" Grenze des Buffers.
            lazyRingBuffer[index] += bool_read ? 1001 : 1000;

            sem_getvalue(&readSem, &readSemValue);
        }while(readSemValue > 0);



        //Goes through the Data and sends the packets in the right order (std::map is sorting for us)
        //cpcCounter = clientProcessingCounter[nextCheck];
        cpcCounter = lazyRingBuffer[lazyRingBufferBaseIndex];
        while(static_cast<int>(cpcCounter / 1000) == clientCount){ //Haben sich alle Clienten zurückgemeldet?;
            //clientProcessingCounter.erase(nextCheck);
            lazyRingBuffer[lazyRingBufferBaseIndex] = 0;
            if((cpcCounter % 1000) == clientCount){ //Haben alle Clienten true gemeldet?
                maxPrime = nextCheck;
                Log::log(maxPrime);
                //memcpy(msgbuffer, &nextCheck, sizeof(unsigned long long));
                tcpiptk::writeMessage(clientList[nextCandidateInClientList],&nextCheck,sizeof(unsigned long long));
                nextCandidateInClientList = (nextCandidateInClientList + 1) % clientCount;
            }
            nextCheck += 2;
            lazyRingBufferBaseIndex = ++lazyRingBufferBaseIndex % lazyRingBufferSize;
            cpcCounter = lazyRingBuffer[lazyRingBufferBaseIndex];
            //cpcCounter = clientProcessingCounter[nextCheck];
        }
    }
}
//#endif
