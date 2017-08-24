//Adrian
#pragma once
#include "LinkedList.hpp"

using namespace std;

/*Eigentlich war geplant, fuer jede Primzahl eine eigene Node in der LinkList zu erzeugen. In der Praxis hat sich allerdings herausgestellt,
dass jede Node einen gigantischen Overhad hat (14gb Ram => ca. 480.000.000 64Bit-Primzahlen). Jetzt kommen wir mit dem Array auf ca. 1.900.000.000 64Bit-Primzahlen.

Weiter Optimieren koennte man in dem man die ersten Primzahlen, welche den 32Bit-Zahlenbereich noch nicht ueberschritten haben, als unsigned int und nicht als unsigned long long speichert.
Außerdem muesste die Variable "primeArrayFuellstand" nicht in jeder Node einzelnd gespeichert sein. Einmal für das komplette Programm wuerde reichen.*/

/*Initialisiert die erste Node und Speichert die ertste Primzahl. Die Node muss vorher deklariert sein.*/
void LinkedList::initNode(struct LinkedList *last, unsigned long long n) {
	last->data = PrimeArray::initPrimeArray();
	(*last).data->primeArray[0] = n;
	last->primeArrayFuellstand = 1;
	last->next = NULL; //Bei der letzten Node immer NULL, ansonsten die Weitersprung-Adresse zur naechste Node.
}

/*Speichert die Primzahl entweder in der letzten Node, oder in einer neuen Node, wenn die letzte voll ist.*/
LinkedList* LinkedList::addNode(struct LinkedList *last, unsigned long long n) {
	if (last->primeArrayFuellstand > 999999) { //Prueft, ob das Array in der letzten Node schon voll ist.
		LinkedList *newNode = new LinkedList;
		newNode->data = PrimeArray::initPrimeArray();
		newNode->data->primeArray[0] = n;
		newNode->primeArrayFuellstand = 1;
		newNode->next = NULL;
		if (last->next == NULL) {
			last->next = newNode;
		}
		return newNode; //Gibt die Adresse der neuen letzten Node zurueck.
	}
	else
	{
		(*last).data->primeArray[last->primeArrayFuellstand] = n;
		last->primeArrayFuellstand++;
		return last; //Gibt die Adresse der letzten Node zurueck.
	}
}
