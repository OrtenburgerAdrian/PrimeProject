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

#ifdef _WIN64
#include <dos.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

extern unsigned long long maxPrime;
extern int nuberOfWorker;
extern LinkedList primesList;
extern LinkedList *head;
extern LinkedList* PrimListLast;

std::mutex timeMutex;
std::mutex primeMutex;
std::mutex Calculate;
std::mutex setMaxPrime;

class MultiCore
{
public:


	static void threadprog() {
		static unsigned long long i = 3;
		unsigned long long i2;
		while (true)
		{
			Calculate.lock();
			i = i + 2;
			i2 = i;
			Calculate.unlock();

			if (IsItAPrime::isItAPrime(i2)) {
				setMaxPrime.lock();
				if (maxPrime < i2) { maxPrime = i2; }
				setMaxPrime.unlock();
				timeMutex.lock();
				Log::logtime();
				Log::log(i2);
				timeMutex.unlock();
				primeMutex.lock();
				PrimListLast = LinkedList::addNode(PrimListLast, i2);
				primeMutex.unlock();
			}
		}
	}



	static void run() {
		std::cout << head << std::endl;
		LinkedList::initNode(head, 3);
		PrimListLast = LinkedList::addNode(PrimListLast, 5);
		PrimListLast = LinkedList::addNode(PrimListLast, 7);
		maxPrime = 7;
		nuberOfWorker++;
		
		switch (nuberOfWorker) {
		case 15:
		{ static std::thread t14(threadprog); }
		case 14:
		{ static std::thread t13(threadprog); }
		case 13:
		{ static std::thread t12(threadprog); }
		case 12:
		{ static std::thread t11(threadprog); }
		case 11:
		{ static std::thread t10(threadprog); }
		case 10:
		{ static std::thread t9(threadprog); }
		case 9:
		{ static std::thread t8(threadprog); }
		case 8:
		{ static std::thread t7(threadprog); }
		case 7:
		{ static std::thread t6(threadprog); }
		case 6:
		{ static std::thread t5(threadprog); }
		case 5:
		{ static std::thread t4(threadprog); }
		case 4:
		{ static std::thread t3(threadprog); }
		case 3:
		{ static std::thread t2(threadprog); }
		case 2:
		{ static std::thread t1(threadprog); }
		case 1:
		case 0:
		{ static std::thread t0(threadprog); }

		}
	}
};
