#pragma once
#include "LinkedList.hpp"


/*Die bis jetz gr��te gepeicherte Primzahl, ist f�r jeden Client-PC eine andere, da jeder PC nur seine gr��te Zahl kennt.*/
extern unsigned long long maxPrime;	//def. in main.cpp

/*Die Adresse der ersten Note*/
extern LinkedList *head;			//def. in main.cpp


class  IsItAPrime
{ public:
	//Adrian
	/*Diese Funktion gibt "True" zur�ck, wenn die zupr�fende Zahl % jeder zahl in der Linklist nicht 0 ergibt. Andernfals "False". Genauergesagt, 
	wird aufgeh�rt zupr�fen, wenn der Teiler gr��er ist als die Wurzel von der zupr�fende Zahl.*/
	static bool isItAPrime(unsigned long long prim);
};
