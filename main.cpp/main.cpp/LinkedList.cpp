#pragma once
#include "LinkedList.hpp"

using namespace std;

/*Eigendlich war geplant, f�r jede Primzahl eine eigene Note in der LinkList zu machen. In der Praksis hat sich allerdings herausgestellt, 
dass jede Note einen gigantischen Overhad hat (14gb Ram => ca. 480.000.000 64Bit-Primzahlen). Jetzt mit dem Array kommen wir auf ca. 1.900.000.000 64Bit-Primzahlen.

Weiter Optimiren k�nnte man in dem man die erten Primzahlen, welche den 32Bit-Zahlenbereich noch nicht �berschritten haben als unsigned int  und nicht als unsigned long long speichert.
Au�erdem m�sste die Variable "primeArrayF�llstand" nicht in jeder Note einzelnd gespeichert sein. Einmal f�r das komplette Programm w�rde reichen.*/

/*Initzialisirt die erste Note und Speichert die ertste Primzahl. Die Note muss vorher deklarirt sein.*/
void LinkedList::initNode(struct LinkedList *last, unsigned long long n) {

	last->data = PrimeArray::initPrimeArray();
	(*last).data->primeArray[0] = n;
	last->primeArrayF�llstand = 0;  
	last->next = NULL; //Bei der letzten Note immer NULL, ansonsten die Weitersprung-Adresse zur n�chste Note.
}

/*Speichert die Primzahl in der letzten Note, bzw. erschafft eine neue Note, wenn die letzte voll ist und speichtet die Primzahl dort.*/
LinkedList* LinkedList::addNode(struct LinkedList *last, unsigned long long n) {
	if (last->primeArrayF�llstand > 999999) { //Pr�ft ob das Array in der letzten Note schon vol ist.
		LinkedList *newNode = new LinkedList;
		newNode->data = PrimeArray::initPrimeArray();
		newNode->data->primeArray[0] = n;
		newNode->primeArrayF�llstand = 1;
		newNode->next = NULL;
		if (last->next == NULL) {
			last->next = newNode;
		}
		return newNode; //Gibt die Adresse der neuen letzten Note zur�ck.
	}
	else
	{
		(*last).data->primeArray[last->primeArrayF�llstand] = n;
		last->primeArrayF�llstand++;
		return last;
	}

}