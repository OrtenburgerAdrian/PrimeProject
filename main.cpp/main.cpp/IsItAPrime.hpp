#pragma once
#include "LinkedList.hpp"


/*Die bis jetz größte gepeicherte Primzahl, ist für jeden Client-PC eine andere, da jeder PC nur seine größte Zahl kennt.*/
extern unsigned long long maxPrime;	//def. in main.cpp

/*Die Adresse der ersten Note*/
extern LinkedList *head;			//def. in main.cpp


class  IsItAPrime
{ public:
	//Adrian
	/*Diese Funktion gibt "True" zurück, wenn die zuprüfende Zahl % jeder zahl in der Linklist nicht 0 ergibt. Andernfals "False". Genauergesagt, 
	wird aufgehört zuprüfen, wenn der Teiler größer ist als die Wurzel von der zuprüfende Zahl.*/
	static bool isItAPrime(unsigned long long prim);
};
