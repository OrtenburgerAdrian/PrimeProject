//Adrian
#pragma once
#include "LinkedList.hpp"

/*Die bis jetzt groe�te gepeicherte Primzahl des ausf�hrenden Prozesses.*/
extern unsigned long long maxPrime;	//def. in main.cpp

/*Die Adresse der ersten Node.*/
extern LinkedList *head;			//def. in main.cpp

class  IsItAPrime
{
public:
	/*
	Diese Funktion gibt "true" zurueck, wenn f�r die zu pruefende Zahl kein ganzzahliger Teiler in der Menge der bekannten Primzahlen gefunden wurde.
	Hier ist wieder anzumerken, dass der Prozess nur eine Teilmenge der Primzahlen kennt, wenn das Programm als Client im Multi-Computing-Prozess l�uft.

	@ prime : Auf prim zupruefende Zahl.
	@ return : True, wenn es keinen Teiler gab, andernfals false.
	*/
	static bool isItAPrime(unsigned long long prim);
};
