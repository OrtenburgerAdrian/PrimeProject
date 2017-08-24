//Adrian
#pragma once
#include "PrimeArray.hpp"
#include <iostream>

struct LinkedList {

	PrimeArray* data; // Start Adresse des PrimeArrays (1.000.000 Felder), pro Feld kann eine unsigned long long (64bit) gespeichert werden.
	LinkedList* next;// Adresse der weiterfuehrenden Node, wenn es eine gibt, ansonsten NULL.
	int primeArrayFuellstand;//Zeigt an wie weit das Array bereits beschrieben ist (In jeder Node auﬂer der letzten 1.000.000).

	/*
	Initialisiert die erste Node und Speichert die ertste Primzahl. Die Node muss vorher deklarirt sein.

	@ *last : Adresse der ersten Node, bei der Initialisierung der erten Node ist last=head.
	@ n : Zuspeichernede Zahl.
	@ return : Adresse der letzten Node.
	*/
	static void  initNode(struct LinkedList *last, unsigned long long n);

	/*
	Speichert die Primzahl in der letzten Node, bzw. erschafft eine neue Node, wenn das "PrimeArray" voll ist und speichert die Primzahl dort.


	@ *last : Adresse der letzten Node
	@ n : Zu speichernede Zahl.
	@ return : Adresse der letzten Node.
	*/
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
};
