//Adrian
#pragma once
#include "IsItAPrime.hpp"

bool IsItAPrime::isItAPrime(unsigned long long prime) {
	LinkedList * primOP = head; //Repraesentirt die Note, auswelcher das PrimeArray ist. Pro Note ein Array mit 1.000.000 Feldern. Hier wird primOP mit der Adresse der ersten Note initialisiert.
	int i = 0; //Repraesentirt die stelle des PrimeArrays, anwelcher sich der Threat grade befindet.
	unsigned long long divisor = 2; //der Teiler

	/*Eine Sperre, welche verhindert, dass sich der Server zuviele Zahlen gleichzeitig merken muss und datuch lei�tung einbue�t.
	Kein Thread kann weiter als 500.000 bzw. 250.000 ungrade Zahlen vorrausrechen. So muss der Server h�chstens 250.000 Zahlen verwalten.*/
	static const unsigned long long maxDifference = 250000;
	while ((maxPrime + maxDifference * 2) < prime) {}

	/*Eine weitere Sperre, so koennen keine Zahlen geprueft werden, welche groeszer als das doppelte der bis jetzt groeszten gespeicherten Primzahl sind, dies ist beim Start des Programmes wichtig,
	am Anfang ist der Rechenaufwand um eine Zahl zupruefen praktisch gleich Null, wesshalb der Server-PC nur so mit Nachrichten beschossen werden wuerde. Um dem entgegen zuwirken ist diese Sperre.*/
	while (maxPrime * 2 < prime) {}

	/*Die Beiden Sperren sorgen auch dafuer, dass der Algoritmuss nicht ans Ende der Linklist kommen kann.*/

	/*Der eigendliche Algorithmuss, welcher durch die Notes mit ihren Arrays iteriert.*/
	while (divisor * divisor <= prime) {
		if (prime % divisor == 0) { return false; } // Wenn true, dann ist "prime" definitv keine Primzahl.

		i++;
		if (i > primOP->primeArrayFuellstand) {
			primOP = primOP->next;
			i = 0;
			divisor = primOP->data->primeArray[i];
		}
		else {
			divisor = primOP->data->primeArray[i - 1]; //i-1, da i schon inkrementiert wurde.
		}
	}
	return true;


};