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
#include <sys/types.h>

#include <cstring>

#ifdef __linux__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "tcpiptk.hpp"
#include "Log.hpp"

#ifdef __linux__
#define PORT    30000
#define MAXMSG  512

void Observer::run() {
    /*//Servercode
    int incomingSocketfd = tcpiptk::acceptConnection(tcpiptk::createSocket(initPort)); //Öffnet Lobby, um Ports zu verteilen.
    int newPort = initPort + 1 + communicators.size(); //Ermittelt einen unbenutzten Port.
    std::stringstream ss; //Aufwendigste IntToString conversion ever.
    ss << newPort;
    tcpiptk::writeMessage(incomingSocketfd, ss.str().c_str()); //Schickt den ermittelten Port an den Anfragenden.
    tcpiptk::closeAndShutdownSocket(incomingSocketfd); //Hier müsste der Port neu geöffnet werden und eine Schleife greifen. Aktuell schließe ich noch.
    communicators.push_back(tcpiptk::acceptConnection(tcpiptk::createSocket(newPort))); //Verbindet sich mit dem Client am neuen Port und schreibt die Nachricht in den Vector.
    std::cout << tcpiptk::getMessage(communicators.back()) << std::endl; //Empfängt Testnachricht und gibt diese aus.

    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ){
        puts("Connection accepted");
        fprintf("Connection accepted\n");
        std::cout << "Connection accepted" << std::endl;

        pthread_t sniffer_thread;

        // Copy the value of the accepted socket, in order to pass to the thread
        new_sock = malloc(4);
        *new_sock = client_sock;

        // Create new thread
        if( pthread_create( &sniffer_thread, NULL,  connection_handler, new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }*/

    //extern int make_socket (uint16_t port);
    int sock;
    fd_set active_fd_set, read_fd_set;
    int i;
    //struct sockaddr_in clientname;
    socklen_t sizeT;

    /* Create the socket and set it up to accept connections. */
    sock = tcpiptk::createSocket(PORT);
    if (listen (sock, 1) < 0){
        perror ("listen");
        exit (EXIT_FAILURE);
    }

    /* Initialize the set of active sockets. */
    FD_ZERO (&active_fd_set);
    FD_SET (sock, &active_fd_set);

    while (1){
        /* Block until input arrives on one or more active sockets. */
        read_fd_set = active_fd_set;
        if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
        {
        perror ("select");
        exit (EXIT_FAILURE);
        }

        /* Service all the sockets with input pending. */
        for (i = 0; i < FD_SETSIZE; ++i){
            if (FD_ISSET (i, &read_fd_set)){
                if (i == sock){
                    /* Connection request on original socket. */
                    int newSocket;
                    unsigned int clilen;
                    struct sockaddr_in cli_addr;
                    sizeT = sizeof (cli_addr);
                    newSocket = accept (sock, (struct sockaddr *) &cli_addr, &sizeT);
                    if (newSocket < 0){
                        perror ("accept");
                        exit (EXIT_FAILURE);
                    }
                    fprintf (stderr,
                    "Server: connect from host %s, port %hd.\n",
                    inet_ntoa (cli_addr.sin_addr),
                    ntohs (cli_addr.sin_port));
                    FD_SET (newSocket, &active_fd_set);
                }else{
                    /* Data arriving on an already-connected socket. */
                    void * msgbuffer = malloc(MAXMSG);
                    Observer::read_from_client (msgbuffer, i);
                    if (Observer::read_from_client (msgbuffer, i) == 0){
                        fprintf (stderr,
                        "Server: connection lost.\n");
                        close (i);
                        FD_CLR (i, &active_fd_set);
                    }else{
                        size_t length = sizeof(unsigned long long) + sizeof(bool);
                        unsigned long long maybePrime;
                        bool isPrime;
                        std::memcpy(&maybePrime, msgbuffer, sizeof(unsigned long long));
                        std::memcpy(&isPrime, msgbuffer + sizeof(unsigned long long), sizeof(bool));
                        printf("%llu: %i\n", maybePrime, isPrime);
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
int Observer::read_from_client (void * msgbuffer,int filedes){
    size_t length = sizeof(unsigned long long) + sizeof(bool);
    void * buffer = malloc(length);
    int nbytes;

    nbytes = read (filedes, buffer, length);
    if (nbytes < 0){
        /* Read error. */
        perror ("read");
        exit (EXIT_FAILURE);
    }else{
        std::memcpy(msgbuffer, buffer, length);
    }
    return nbytes;
}


#endif