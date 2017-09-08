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
        static void run(int mode);
        static void sendMessage(unsigned long long maybePrime, bool isLocalPrime);
        static char getMessage();
    protected:
    private:
        static std::string ask(std::string question);
        static void runReceiver(int mode);
        static void runTransmitter(int mode);
        static void runPrimeReceiver(int mode);
};
