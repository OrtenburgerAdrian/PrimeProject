#pragma once
//#include <stdio.h>
//#include <string>
//#include <iostream>
//#include <stdlib.h>
//#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"

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
