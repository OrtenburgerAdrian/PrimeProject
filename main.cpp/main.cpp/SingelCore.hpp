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
#include <thread>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"

#ifdef _WIN64
#include <dos.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif


extern int nuberOfWorker;
extern LinkedList primesList;
extern LinkedList *head;
extern LinkedList *PrimListLast;

class SingelCore
{
public:

	bool static isItAPrime(unsigned long long prime, LinkedList *head ) {
		if (prime % 2 == 0) { return false; }
		unsigned long long divisor = 3;
		LinkedList * primOP = head;

		while (divisor * 2 <= prime && primOP != NULL) {
			if (prime % divisor == 0) { return false; }

			divisor = primOP->data;
			primOP = primOP->next;
		}
		return true;
	}

	static void run() {
		static unsigned long long i = 3;
		LinkedList::initNode(head, 3);
		while (true)
		{
			if (isItAPrime(i, head)) {
				Log::logtime();
				PrimListLast = LinkedList::addNode(PrimListLast, i);
				i++;
				i++;
			}
			else {
				i++;
				i++;
			}
		}


	}


private:

};

