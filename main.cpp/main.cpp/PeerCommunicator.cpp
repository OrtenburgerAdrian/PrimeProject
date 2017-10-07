#include "PeerCommunicator.hpp"
#include "Log.hpp"

#include "vector"
#include "thread"
#include <unistd.h>
#include <sys/socket.h>

#define PORT 30000
#define PRIMESPERPEER 5

static int previousPeerSocketfd;
static int nextPeerSocketfd;
static std::string previousPeerIP, nextPeerIP, lastPeerIP;

//Benoetigt der letzte Peer...
static int peerCounter; //Zum durchzählen aller Peers.

//Abfrage (von IPs)
std::string PeerCommunicator::ask(std::string question){
    std::string answer;
    std::cout << question + ":\n>";
    getline(std::cin, answer);
    return answer;
}

//Verbindungsprotokoll
void PeerCommunicator::run(int mode){ //Modes: 0=FirstPeer; 1=MiddlePeer(s); 2=LastPeer
    int incomingSocket = tcpiptk::createSocket(PORT);
    switch(mode){
    case 0:
        // Der erste Communicator benötigt zunächst keine Verbindung, erwartet aber 2 eingehende...
        nextPeerSocketfd = tcpiptk::acceptConnection(incomingSocket);
        previousPeerSocketfd = tcpiptk::acceptConnection(incomingSocket);
        tcpiptk::closeSocket(incomingSocket);

        //Durchzählen: Der erste Peer fängt an mit "1".
        peerCounter = 1;
        printf("Durchzählen: %i\n", peerCounter);
        tcpiptk::writeMessage(nextPeerSocketfd, &peerCounter, sizeof(int));
    break;
    case 1:
        previousPeerIP = ask("Please enter the IP of the previous peer");
        previousPeerSocketfd = tcpiptk::connectSocket(previousPeerIP.c_str(), PORT);
        nextPeerSocketfd = tcpiptk::acceptConnection(incomingSocket);
        tcpiptk::closeSocket(incomingSocket);

        //Durchzählen: Die mittleren Peers zählen auf.
        tcpiptk::getMessage(previousPeerSocketfd, &peerCounter, sizeof(int));
        peerCounter++;
        printf("Durchzählen: %i\n", peerCounter);
        tcpiptk::writeMessage(nextPeerSocketfd, &peerCounter, sizeof(int));
    break;
    case 2:
        // Der letzte Communicator muss sich mit dem Ersten UND vorhergehenden Communicator verbinden.
        tcpiptk::closeSocket(incomingSocket);
        previousPeerIP = PeerCommunicator::ask("Please enter the IP of the previous peer");
        previousPeerSocketfd = tcpiptk::connectSocket(previousPeerIP.c_str(), PORT);
        nextPeerIP = PeerCommunicator::ask("Please enter the IP of the first peer");
        nextPeerSocketfd = tcpiptk::connectSocket(nextPeerIP.c_str(), PORT);

        //Durchzählen: der letzte Peer kennt nun die Zahl der Mitglieder.
        tcpiptk::getMessage(previousPeerSocketfd, &peerCounter, sizeof(int));
        peerCounter++;
        printf("Durchzählen beendet: es gibt %i Peers.\n", peerCounter);
    break;
    }

    std::thread transmitter(PeerCommunicator::runPrimeReceiver);
    std::thread receiver(PeerCommunicator::runReceiver, mode);
    runTransmitter(mode);
}

void PeerCommunicator::runReceiver(int mode){
    char m = 0;
    if(mode == 0){
        m--;
        while(true){
            wl->TCPWrite(m);
        }
    }else{
        while(true){
            tcpiptk::getMessage(previousPeerSocketfd, &m, sizeof(m));
            //Hätten wir die Nachricht nicht invertiert, wäre eine 0-Nachricht valide.
            if(((int)m) == 0){ //Wenn 0 empfangen wird, wurde der Socket vom Peer geschlossen.
                printf("Connection to Server lost!");
                close(previousPeerSocketfd);
                return; // :(
            }
            m = m ^ 0xff; //Invertiert das byte, sodass eine leere Nachricht ungültig ist.
            //printByteAsString(m);
            wl->TCPWrite(m);
        }
    }
}
void PeerCommunicator::runTransmitter(int mode){
    char m; //Dingens... Uebergangsparameter für 8 bit. wobei jeder bit anzeigt, ob die Zahl prim ist oder nicht.

    if(mode == 2){ // Der Transmitter unterscheidet nur noch den EndPeer vom Rest.
        static std::vector<int> primeSendList; //Enthält Sockets zu allen Peers, sich selbst eingeschlossen. (Aufsteigend vom ersten zum letzten)
        static int nextPeerForPrime; //Der Index zum naechsten glücklichen Peer, der eine Primzahl bekommen darf.
        int incomingSocket = tcpiptk::createSocket(PORT);

        bool b = true;
        tcpiptk::writeMessage(nextPeerSocketfd, &b, sizeof(b)); //Gibt dem ersten Peer bescheid, dass das Durchzählen beendet ist.

        /* Waits until everyone is connected. */
        int connectionCount = 0;
        nextPeerForPrime = peerCounter-1; //Wir vergeben Primzahlen dann rueckwaerts, damit der erste Peer die hoechste Primzahl hat...
        do{
            /* Connection request on original socket. */
            int newSocket;
            newSocket = tcpiptk::acceptConnection(incomingSocket);
            if (newSocket > 1023){
                printf("Program Error: tcpiptk::acceptConnection() returned %i\n", newSocket);
            }
            //FD_SET (newSocket, &active_fd_set);
            primeSendList.push_back(newSocket);
            connectionCount++;
        }while(connectionCount < (peerCounter));

        //Initialisiert die Worker mit einigen Primzahlen.
        int numberOfStartPrimes = peerCounter * PRIMESPERPEER;
        unsigned long long primArr[numberOfStartPrimes];
        int si = 0;
        int x = 2;
        while(si < numberOfStartPrimes){
            for (int y=2; y<x; y++){
                if (x % y == 0){
                    break;
                }else if (x == y+1){
                    primArr[si] = static_cast<unsigned long long>(x);
                    printf("StartingPrime: %llu \n", primArr[si]);
                    si++;
                }
            }
            x++;
        }
        //Verteilt erste Primzahlen rückwärts
        //unsigned long long primArr[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
        if (peerCounter * PRIMESPERPEER > (sizeof(primArr)/sizeof(*primArr))){
            printf("Zu viele Peers!");
            return; // :((
        }

        int i = 0;
        unsigned long long pr;
        do{
            pr = primArr[i];
            //printf("Sending a Message to %i: %llu is a prime.\n", primeSendList[nextPeerForPrime], pr); //Nützlich für Tests.
            tcpiptk::writeMessage(primeSendList[nextPeerForPrime], &pr, sizeof(pr));
            i++;
            nextPeerForPrime--;
            if (nextPeerForPrime < 0){ nextPeerForPrime = peerCounter - 1; }
        }while(i < peerCounter * PRIMESPERPEER);
        nextPeerForPrime = peerCounter - 1; //Setzt den PeerIndex nochmal zurück.

        //Transmitterschleife des letzten Peers: Sendet fertige Primzahlen reihum an seine Peers.
        std::vector<unsigned long long> returnPrimes;
        unsigned long long currentPrime;
        while(true){
            returnPrimes = wl->getSecuredPrimes();
            for(std::vector<unsigned long long>::iterator it = returnPrimes.begin(); it != returnPrimes.end(); ++it) {
                currentPrime = *it;
                Log::log(currentPrime); //Logging!
                //printf("Sending a Message to %i: %llu is a prime.\n", primeSendList[nextPeerForPrime], currentPrime); //Nützlich für Tests.
                tcpiptk::writeMessage(primeSendList[nextPeerForPrime], &currentPrime, sizeof(currentPrime));
                //if (currentPrime >= 150){ return;}
                nextPeerForPrime--;
                if(nextPeerForPrime < 0){
                    nextPeerForPrime += peerCounter;
                }
            }
        }
    }else{
        while(true){
            m = wl->TCPRead();
            //printByteAsString(m);
            m = m ^ 0xff; //Invertiert das byte, sodass eine leere Nachricht ungültig ist.
            //printf("Sending a binary Message to %i: %i.\n", nextPeerSocketfd, (int)m); //Nützlich für Tests.
            tcpiptk::writeMessage(nextPeerSocketfd, &m, sizeof(m));
        }
    }
}

void PeerCommunicator::runPrimeReceiver(){
    //Initialisierung ist noch nicht abgeschlossen...
    unsigned long long receivedPrime = 0;
    std::string lastPeerIP = ask("Please enter the IP of the last peer");
    int listeningfd = tcpiptk::connectSocket(lastPeerIP.c_str(), PORT);

    bool linkedListInitialized = false; //Der Umgang mit Adrians LinkedList ist zwar sonderbar, funktioniert aber.
    while(true){
        tcpiptk::getMessage(listeningfd,&receivedPrime,sizeof(unsigned long long)); //Empfängt die Nachricht.
        if(receivedPrime == 0){ //Wenn 0 empfangen wird, wurde der Socket vom letzten Peer geschlossen.
            printf("Connection to Server lost!");
            close(listeningfd);
            return;
        }
        //printf("Got a Message: %llu is a prime.\n", receivedPrime); //Nützlich für Tests.
        if (linkedListInitialized == false){ //Initialisiert die LinkedList...
            LinkedList::initNode(head, receivedPrime);
            linkedListInitialized = true;
        }else{
            PrimeListLast = LinkedList::addNode(PrimeListLast, receivedPrime);
        }
        if(receivedPrime > maxPrime) maxPrime = receivedPrime; //MaxPrime ist in main.cpp definiert und beschreibt die höchste Primzahl, die der Prozess kennt.
        receivedPrime = 0; //Mal gucken was passiert.
    }
}

void PeerCommunicator::printByteAsString (char b){
    int i;
    for (i = 0; i < 8; i++) {
      printf("%d", !!((b << i) & 0x80));
    }
    printf("\n");
}
