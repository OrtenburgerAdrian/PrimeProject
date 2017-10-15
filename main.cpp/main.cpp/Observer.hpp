//Benjamin
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include <semaphore.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

extern unsigned long long maxPrime;
extern LinkedList * head;
extern LinkedList * PrimeListLast;
extern int numberOfWorker;

class Observer
{
	static void run_listener(); //Funktion, um einen Thread zu speisen. Führt in eine Listenerschleife, die eingehende Nachrichten der Klienten verarbeitet.
	static void run_teller(); //Funktion, um einen Thread zu speisen. Führt in eine Sendeschleife, die gesicherte Primzahlen an Klienten schickt.

public:
	static void run(); // Startet den Observer und fragt die Zahl der erwarteten Klienten ab.
	static void run(int expectedClientCount); //Startet den Observer mit der übergebenen Zahl an Klienten.
};
