//Benjamin
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
#include <vector>

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

/**
*   Der Observer hat zwei Hauptkomponenten neben dem relativ aufwaendigen Initialisierungsprozess:
*       1.  Empfange eingehende Nachrichten.
*       2.  Sammle und werte die Nachrichten aus.
*       3.  Teile den angemeldeten Communicatorn in gleichen Teilen neu gefundene Primzahlen zu.
*   RandomAccessRingBuffer realisiert Punkt 2 zu und gleichzeitig die Kommunikation zwischen Listener- und Tellerthread.
*   Wir nutzen dafuer den Fakt, dass maximal 250.000 Zahlen in Vorraus gerechnet wird und nur ungerade Zahlen behandelt werden.
*   Außerdem können wir für vollständig bearbeitete Zahlen davon ausgehen, dass der Listenerthread nicht mehr darauf zugreift.
*
*   Die implementierung von RandomAccessRingBuffer ermöglicht uns es außerdem die ausgehenden Zahlen zu sortieren!
**/

// Variablen zur Clientpoolverwaltung
static int clientCount;
static int nextCandidateInClientList;
static std::vector<int> clientList;
static fd_set active_fd_set;

/**
 *  Wir speichern die Anzahl der gemeldeten Clients UND wie viele davon true gemeldet haben.
 *  Wir speichern NICHT die Zahl, auf die sich diese Informationen beziehen. - Diese ergibt sich mit der Programmweiten Variable maxPrime.
 *  Client meldet sich int + 1000 UND wenn true int + 1
 *  Rückwärts können wir also auflösen...
 *  Anzahl der zurückgemeldeten Clients: int clients = clientProcessingCounter[maybePrime] / 1000
 *  Anzahl der positiven Rückmeldungen:  int bools = clientProcessingCounter[maybePrime] % 1000
 */
static std::mutex mutex_randomAccessRingBuffer;
static const int randomAccessRingBufferSize = 250000;
static int randomAccessRingBuffer[randomAccessRingBufferSize] = {0};
static int randomAccessRingBufferBaseIndex = 0;
unsigned long long nextNumberToCheck = 3; //nextNuberToCheck ist die Zahl, auf die sich der randomAccessRingBuffer beim BaseIndex bezieht.

void Observer::run(){ //Fragt fehlende Parameter ab.
    int expectedClientCount;
    std::cout << "How many Client do we expect?:\n>";
    std::cin >> expectedClientCount;
    Observer::run(expectedClientCount);
}

void Observer::run(int expectedClientCount) {
    /* Prints the assigned address for each known network interface. */
    tcpiptk::getMyIP();

    /* Create the socket and set it up to accept connections. */
    int sock = tcpiptk::createSocket(PORT);
    if (listen (sock, 1) < 0){
        perror ("listen");
        exit (EXIT_FAILURE);
    }

    /* Initialize the set of active sockets. */
    FD_ZERO (&active_fd_set);
    FD_SET (sock, &active_fd_set);

    /* Waits until everyone is connected. */
    clientCount = 0;
    nextCandidateInClientList = 0;
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

    //Initialisiert die Worker mit einigen Primzahlen.
    unsigned long long prePrime;
    for (int x=2; x<100; x++){
        for (int y=2; y<x; y++){
            if (x % y == 0){
                break;
            }else if (x == y+1){
                prePrime = static_cast<unsigned long long>(x);
                tcpiptk::writeMessage(clientList[nextCandidateInClientList], &prePrime, sizeof(unsigned long long));
                nextCandidateInClientList = (nextCandidateInClientList + 1) % clientCount;
            }
        }
    }

    std::thread listenerThread(Observer::run_listener); //Starte Listenerthread.
    Observer::run_teller();
}

void Observer::run_listener(){
    unsigned long long ull_read;
    bool bool_read;

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
                if (tcpiptk::getMessage(currentFileDescriptor, &ull_read, sizeof(unsigned long long)) == 0){
                    fprintf (stderr, "Server: connection lost.\n");
                    close (currentFileDescriptor);
                    FD_CLR (currentFileDescriptor, &active_fd_set);
                    return;
                }

                bool_read = (ull_read % 2) == 1 ? true : false; //Dekodiert den Boolean aus der Zahl: Wenn die Zahl ungerade ist, dann war der boolean beim Encodieren 0 (also true);
                ull_read -= bool_read ? 0 : 1; //Zieht den boolean von unserer Zahl ab, falls dieser eincodierd wurde. (Ansonsten passiert nichts, weil bool_read 0 ist.)

                printf("Got a Solution: %llu is %sa prime for a  Client.\n", ull_read, bool_read ? "" : "not "); //Nützlich für Tests.

                mutex_randomAccessRingBuffer.lock();
                {
                    //Enkodiert die Information in den randomAccessRingBuffer.
                    int relativeIndex = (ull_read - nextNumberToCheck) / 2;
                    if (relativeIndex >= randomAccessRingBufferSize){ //Eigentlich nur zur Sicherheit. Kann nicht übertreten werden, weil die Clienten nicht über 250k Zahlen über die letzte Primzahl gehen.
                        // Letztes mal sind wir nach einigen Stunden in diese Abfrage gefallen. Wir konnten den Fehler nicht beweisen, deshalb haben wir erstmal das Logging erhöht.
                        printf("lazyBufferOverflow, idiot! - relativeIndex: %i \n", relativeIndex);
                        fprintf (stderr, "lazyBufferOverflow, idiot! \n");
                        return;
                    }

                    int index = (randomAccessRingBufferBaseIndex + relativeIndex) % randomAccessRingBufferSize;
                    randomAccessRingBuffer[index] += bool_read ? 1001 : 1000;
                }
                mutex_randomAccessRingBuffer.unlock();
            }
        }
    }
}

// Interpretiert die vorverarbeiteten Zahlen und versendet die Primzahlen.
void Observer::run_teller(){
    //Hinweis, hier brauchen wir den Mutex NICHT um zu lesen.
    //Wenn sich alle Clienten zurückgemeldet haben, greift der Listenerthread nicht mehr auf die Adresse zu.
    int clientProcessingCounter;
    while(true){
        clientProcessingCounter = randomAccessRingBuffer[randomAccessRingBufferBaseIndex];
        if(static_cast<int>(clientProcessingCounter / 1000) == clientCount){ //Haben sich alle Clienten zurückgemeldet?;
            if((clientProcessingCounter % 1000) == clientCount){ //Haben alle Clienten true gemeldet?
                maxPrime = nextNumberToCheck;
                Log::log(maxPrime);

                printf("I am telling a Client that %llu is definitely a prime number.\n", nextNumberToCheck); //Nützlich für Tests.

                tcpiptk::writeMessage(clientList[nextCandidateInClientList],&nextNumberToCheck,sizeof(unsigned long long));
                nextCandidateInClientList = (nextCandidateInClientList + 1) % clientCount;
            }
            randomAccessRingBuffer[randomAccessRingBufferBaseIndex] = 0; //Löscht den abgefragten Wert (nur zur Sicherheit um unerwartetes Verhalten zu erkennen)
            mutex_randomAccessRingBuffer.lock(); //Wenn wir den Ringbuffer weiterschieben, brauchen wir wieder den Mutex.
                nextNumberToCheck += 2;
                randomAccessRingBufferBaseIndex = ++randomAccessRingBufferBaseIndex % randomAccessRingBufferSize;
            mutex_randomAccessRingBuffer.unlock();
        }
    }
}
