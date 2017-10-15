//Adrian
#pragma once
#include "IsItAPrime.hpp"

bool IsItAPrime::isItAPrime(unsigned long long prime) {
	LinkedList * primOP = head; //Repraesentiert eine Node, aus welcher das PrimeArray besteht. Pro Node ein Array mit 1.000.000 Feldern. Hier wird primOP mit der Adresse der ersten Node initialisiert.
	int i = 0; //Repraesentiert die Stelle des PrimeArrays, an welcher sich der Thread gerade befindet.
	unsigned long long divisor = 2; //der Teiler

	/*Eine Sperre, welche verhindert, dass sich der Server zuviele Zahlen gleichzeitig merken muss und dadurch Leistung einbueßt.
	Kein Thread kann weiter als 500.000 bzw. 250.000 ungrade Zahlen vor die letze Primzahl rechnen. So muss der Server höchstens 250.000 Zahlen verwalten.*/
	//Zusätzliche Anmerkung: Der Observer ist nun davon Abhängig, dass diese Zahl nicht größer als 250.000 ist.
	static const unsigned long long maxDifference = 250000;
	while ((maxPrime + maxDifference * 2) < prime) {}

	/*Eine weitere Sperre, so koennen keine Zahlen geprueft werden, welche groeszer als das doppelte der bis jetzt groeszten gespeicherten Primzahl sind.
	Dies ist zu beginn des Programmes wichtig.
	Zusätzlich vehindert die Sperre, dass die Worker-Threads auf das PrimeArray zugreifen, bevor es initialisiert ist.*/
	while (maxPrime * 2 < prime) {}

	/*Die Beiden Sperren sorgen auch dafuer, dass der Algorithmus nicht ans Ende der LinkedList kommen kann.*/

	/*Der eigentliche Algorithmus, welcher durch die Nodes mit ihren Arrays iteriert.*/
	while (divisor * divisor <= prime) {
		if (prime % divisor == 0) { return false; } // Wenn true, dann ist "prime" definitv keine Primzahl.


		if (i > 999999){ //In diesem Fall muss zur nächsten Node gewechselt werden.

			primOP = primOP->next;
			i = 0;
			divisor = primOP->data->primeArray[i];
		}
		else {
			divisor = primOP->data->primeArray[i];
			i++;
		}
	}
	return true;
};
