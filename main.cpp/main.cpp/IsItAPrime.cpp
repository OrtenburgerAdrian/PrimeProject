//Adrian
#pragma once
#include "IsItAPrime.hpp"

bool IsItAPrime::isItAPrime(unsigned long long prime) {
	LinkedList * primOP = head; //Repraesentiert die Node, aus welcher das PrimeArray ist. Pro Node ein Array mit 1.000.000 Feldern. Hier wird primOP mit der Adresse der ersten Node initialisiert.
	int i = 0; //Repraesentirt die stelle des PrimeArrays, anwelcher sich der Threat grade befindet.
	unsigned long long divisor = 2; //der Teiler

	/*Eine Sperre, welche verhindert, dass sich der Server zuviele Zahlen gleichzeitig merken muss und datuch Leistung einbueßt.
	Kein Thread kann weiter als 500.000 bzw. 250.000 ungrade Zahlen vor die letze Primzahl rechnen. So muss der Server höchstens 250.000 Zahlen verwalten.*/
	static const unsigned long long maxDifference = 250000;
	while ((maxPrime + maxDifference * 2) < prime) {}

	/*Eine weitere Sperre, so koennen keine Zahlen geprueft werden, welche groeszer als das doppelte der bis jetzt groeszten gespeicherten Primzahl sind, dies ist beim Start des Programmes wichtig,
	am Anfang ist der Rechenaufwand um eine Zahl zupruefen praktisch gleich Null, wesshalb der Server-PC nur so mit Nachrichten beschossen werden wuerde. Um dem entgegen zuwirken ist diese Sperre.*/
	while (maxPrime * 2 < prime) {}

	/*Die Beiden Sperren sorgen auch dafuer, dass der Algoritmuss nicht ans Ende der Linkedlist kommen kann.*/

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
