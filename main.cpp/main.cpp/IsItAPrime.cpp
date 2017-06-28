#pragma once
//#include <stdio.h>
//#include <string>
//#include <iostream>
//#include <stdlib.h>
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <stdio.h>
//#include <time.h>
//#include <stdio.h>
//#include <time.h>

//#include <iostream>
//#include <stdlib.h>

#include "LinkedList.hpp"
//#include "Observer.hpp"
//#include "Communicator.hpp"
//#include "Worker.hpp"
#include "IsItAPrime.hpp"
//#include "Log.hpp"




bool IsItAPrime::isItAPrime(unsigned long long prime) {
	unsigned long long divisor = 2;
	LinkedList * primOP = head;
	static const unsigned long long maxDifference= 250000;
	while((maxPrime + maxDifference*2) < prime){}
	while(maxPrime*2 < prime){}
	while (divisor * divisor <= prime ) {
		if (prime % divisor == 0) { return false; }
		divisor = primOP->data;
		primOP = primOP->next;
	}
	return true;
};
