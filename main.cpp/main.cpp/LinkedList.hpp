//Adrian
#pragma once
#include "PrimeArray.hpp"
#include <iostream>

struct LinkedList {

	PrimeArray* data; // Start Adresse des PrimArrays (1.000.000 Felder), pro Feld kann eine unsigned long long (64bit) gespeichert werden.
	LinkedList* next;// Adresse der weiterfuehrenden Note, wenn es eine gibt, ansonsten NULL.
	int primeArrayFuellstand;//Zeigt an wie weit das Array bereits beschrieben ist (In jeder Note auﬂer der letzten 1.000.000).

	/*
	Initialisiert die erste Note und Speichert die ertste Primzahl. Die Note muss vorher deklarirt sein.

	@ *last : Adresse der ersten Note, bei der Initialisierung der erten Note ist last=head.
	@ n : Zuspeichernede Zahl.
	@ return : Adresse der letzten Note.
	*/
	static void  initNode(struct LinkedList *last, unsigned long long n);

	/*
	Speichert die Primzahl in der letzten Note, bzw. erschafft eine neue Note, wenn das "PrimeArray" voll ist und speichtet die Primzahl dort.


	@ *last : Adresse der letzten Note
	@ n : Zuspeichernede Zahl.
	@ return : Adresse der letzten Note.
	*/
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
};
