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
#include "SingelCore.hpp"
#include "Threads.hpp"
#ifdef _WIN64
#include <dos.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif
#include "MultiCore.hpp"
	 void MultiCore::threadprog() {
		static unsigned long long i = 1;
		unsigned long long i2;
		while (true)
		{
			Calculate.lock();
			i = i + 2;
			i2 = i;
			Calculate.unlock();

			if (IsItAPrime::isItAPrime(i2)) {
				primeMutex.lock();
				PrimListLast = LinkedList::addNode(PrimListLast, i2);
				primeMutex.unlock();
				setMaxPrime.lock();
				if (maxPrime < i2) { maxPrime = i2; }
				setMaxPrime.unlock();
				timeMutex.lock();
				Log::log(i2);
				timeMutex.unlock();

			}
		}
	}



	 void MultiCore::run() {
		std::cout << head << std::endl;
		LinkedList::initNode(head, 3);
		maxPrime = 3;
		numberOfWorker++;
		Threads::start("multiCore", numberOfWorker);
		
	}