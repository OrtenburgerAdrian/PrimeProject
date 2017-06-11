#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
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
#include "IsItAPrime.hpp"
#include "Log.hpp"

#ifdef _WIN32
    #include <dos.h>
    #include <windows.h>
#endif

 bool IsItAPrime::isItAPrime(unsigned long long prime, LinkedList *head) {
	if (prime % 2 == 0) { return false; }
	unsigned long long divisor = 3;
	LinkedList * primOP = head;

	while (divisor * 2 < prime && primOP != NULL) {
		if (prime % divisor == 0) { return false; }

		divisor = primOP->data;
		primOP = primOP->next;
	}
	return true;

};
