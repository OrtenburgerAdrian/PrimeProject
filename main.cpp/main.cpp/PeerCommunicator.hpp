//Benjamin
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "WorkList.hpp"
#include "tcpiptk.hpp"

extern unsigned long long maxPrime; //def. in main.cpp
extern LinkedList * head; //def. in main.cpp
extern LinkedList * PrimeListLast; //def. in main.cpp
extern WorkList* wl;

class PeerCommunicator
{
    public:
        static void run(int mode); //Initialisiert den Kommunikationsprozess zwischen mehreren Peers.
    protected:
    private:
        static std::string ask(std::string question); //Hilfsfunktion, die genutzt wird um IPs abzufragen.
        static void runReceiver(int mode); //Funktion zur Speisung eines Threads: Empfängt Nachrichten des Vorgängers und speichert die Informationen in der WorkList.
        static void runTransmitter(int mode); //Funktion zur Speisung eines Threads: Holt berechnete Informationen aus der WorkList und sendet sie an den nächsten Peer.
        static void runPrimeReceiver(); ////Funktion zur Speisung eines Threads: Empfängt neue Primzahlen vom letzten Peer und speichert diese in der LinkedList.
};
