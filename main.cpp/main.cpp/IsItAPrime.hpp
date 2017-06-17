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

extern unsigned long long maxPrime;
extern LinkedList primesList;
extern LinkedList *head = &primesList;
extern LinkedList* PrimListLast = head;
class  IsItAPrime
{ public:
	//Adrian
	static bool isItAPrime(unsigned long long prim);

};
