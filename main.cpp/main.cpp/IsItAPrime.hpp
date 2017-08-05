//Adrian
#pragma once
#include "LinkedList.hpp"

/*Die bis jetz groeßte gepeicherte Primzahl; diese ist für jeden Client-PC eine andere, da jeder PC nur seine groeßte Zahl kennt.*/
extern unsigned long long maxPrime;	//def. in main.cpp

/*Die Adresse der ersten Note.*/
extern LinkedList *head;			//def. in main.cpp

class  IsItAPrime
{
public:
	/*
	Diese Funktion gibt "true" zurueck, wenn die zupruefende Zahl modulo jeder zahl in der Linklist welche nicht groeszer ist
	als die Wurzel aus der zupruefende Zahl, nicht 0 ergibt, andernfals "false".

	@ prime : Auf prim zupruefende Zahl.
	@ return : True, wenn es keinen Teiler gab, andernfals false.
	*/
	static bool isItAPrime(unsigned long long prim);
};
