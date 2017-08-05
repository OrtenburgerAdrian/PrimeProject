//Adrian
#pragma once
#include "LinkedList.hpp"

using namespace std;

/*Eigendlich war geplant, fuer jede Primzahl eine eigene Note in der LinkList zu machen. In der Praksis hat sich allerdings herausgestellt,
dass jede Note einen gigantischen Overhad hat (14gb Ram => ca. 480.000.000 64Bit-Primzahlen). Jetzt mit dem Array kommen wir auf ca. 1.900.000.000 64Bit-Primzahlen.

Weiter Optimiren koennte man in dem man die erten Primzahlen, welche den 32Bit-Zahlenbereich noch nicht ueberschritten haben, als unsigned int und nicht als unsigned long long speichert.
Außerdem muesste die Variable "primeArrayFuellstand" nicht in jeder Note einzelnd gespeichert sein. Einmal für das komplette Programm wuerde reichen.*/

/*Initialisiert die erste Note und Speichert die ertste Primzahl. Die Note muss vorher deklarirt sein.*/
void LinkedList::initNode(struct LinkedList *last, unsigned long long n) {
	last->data = PrimeArray::initPrimeArray();
	(*last).data->primeArray[0] = n;
	last->primeArrayFuellstand = 0;
	last->next = NULL; //Bei der letzten Note immer NULL, ansonsten die Weitersprung-Adresse zur naechste Note.
}

/*Speichert die Primzahl in der letzten Note, bzw. erschafft eine neue Note, wenn die letzte voll ist und speichtet die Primzahl dort.*/
LinkedList* LinkedList::addNode(struct LinkedList *last, unsigned long long n) {
	if (last->primeArrayFuellstand > 999999) { //Prueft ob das Array in der letzten Note schon voll ist.
		LinkedList *newNode = new LinkedList;
		newNode->data = PrimeArray::initPrimeArray();
		newNode->data->primeArray[0] = n;
		newNode->primeArrayFuellstand = 1;
		newNode->next = NULL;
		if (last->next == NULL) {
			last->next = newNode;
		}
		return newNode; //Gibt die Adresse der neuen letzten Note zurueck.
	}
	else
	{
		(*last).data->primeArray[last->primeArrayFuellstand] = n;
		last->primeArrayFuellstand++;
		return last; //Gibt die Adresse der letzten Note zurueck.
	}
}