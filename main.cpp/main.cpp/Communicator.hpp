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

extern unsigned long long maxPrime; //def. in main.cpp
extern LinkedList * head; //def. in main.cpp
extern LinkedList * PrimeListLast; //def. in main.cpp

class Communicator
{
public:
	static void run(); // Startet den Communicator und fragt die IP des Obervers ab.
    static void run(std::string ip); //Startet den Communicator mit der übergebenen IP.
	static void sendMessage(unsigned long long maybePrime, bool isLocalPrime); //Diese Funktion wird von den Threads genutzt, um dem Observer mitzuteilen, ob eine Zahl für den Prozess eine Primzahl ist oder nicht.
};
