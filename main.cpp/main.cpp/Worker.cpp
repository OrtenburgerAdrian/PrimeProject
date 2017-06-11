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
#include <stdlib.h>

#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"

#ifdef _WIN32
    #include <dos.h>
    #include <windows.h>
#endif

void Worker::thread_calculate(int threadNumber) {
	static LinkedList *head = &primesList;
	while (threadNotDelete[threadNumber])
	{
		while (threadActive[threadNumber]) {
			if (IsItAPrime::isItAPrime(threadToCalculate[threadNumber], head)) {
				threadIsPrime[threadNumber] = true;
			}
			threadActive[threadNumber] = false;
		}
	}
}
 void Worker::start() {


	switch (nuberOfWorker) {
	case -1:
		Log::logerror("FEHLER beim lesen der anzahl der CPU-Kerne");
		break;
	default:
	case 15:
	{ static std::thread t14(thread_calculate, 14); }
	case 14:
	{ static std::thread t13(thread_calculate, 13); }
	case 13:
	{ static std::thread t12(thread_calculate, 12); }
	case 12:
	{ static std::thread t11(thread_calculate, 11); }
	case 11:
	{ static std::thread t10(thread_calculate, 10); }
	case 10:
	{ static std::thread t9(thread_calculate, 9); }
	case 9:
	{ static std::thread t8(thread_calculate, 8); }
	case 8:
	{ static std::thread t7(thread_calculate, 7); }
	case 7:
	{ static std::thread t6(thread_calculate, 6); }
	case 6:
	{ static std::thread t5(thread_calculate, 5); }
	case 5:
	{ static std::thread t4(thread_calculate, 4); }
	case 4:
	{ static std::thread t3(thread_calculate, 3); }
	case 3:
	{ static std::thread t2(thread_calculate, 2); }
	case 2:
	{ static std::thread t1(thread_calculate, 1); }
	case 1 || 0:
	{ static std::thread t0(thread_calculate, 0); }

	}
}

void Worker::setTestingInt(unsigned long long prime, int threadNumber) {
	threadToCalculate[threadNumber] = prime;




}
void Worker::stop(int threadNumbe) {
	threadNotDelete[threadNumbe] = false;


}
void Worker::TestingInt(int threadNumbe, unsigned long long prime) {
	threadToCalculate[threadNumbe] = prime;

} unsigned long long Worker::TestingInt(int threadNumbe) {
	return threadToCalculate[threadNumbe];
}
void Worker::Active(int threadNumber, bool activ) {
	threadActive[threadNumber] = activ;
}
bool Worker::Active(int threadNumber) {
	return threadActive[threadNumber];
}



