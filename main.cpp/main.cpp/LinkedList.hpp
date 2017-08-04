#pragma once
#include "PrimeArray.hpp"
#include <iostream>

struct LinkedList{

	PrimeArray* data; // Start Adresse des PrimArrays (1.000.000 Felder), pro Feld kann eine  unsigned long long (64bit) gespeichert werden.
	LinkedList* next;// Adresse der weiterführenden Note, wenn es eine gibt, sonst NULL.
	int primeArrayFüllstand;//Zeigt an wie weit das Array bereits beschrieben ist. (In jeder Note außer der letzten 1.000.000)
	
	

	//Adrian
	/*
	Initzialisirt die erste Note und Speichert die ertste Primzahl. Die Note muss vorher deklarirt sein.

	@ *last : Adresse der ersten Note, bei der Initialisierung der erten Note ist last=head
	@ n : zuspeichernede Zahl	
	*/
	static void  initNode(struct LinkedList *last, unsigned long long n);

	//Adrian
	/*
	Speichert die Primzahl in der letzten Note, bzw. erschafft eine neue Note, wenn das "PrimeArray" voll ist und speichtet die Primzahl dort.
	
	@ *last : Adresse der letzten Note
	@ n : zuspeichernede Zahl
	*/
	static LinkedList* addNode(struct LinkedList *last, unsigned long long n);
};
