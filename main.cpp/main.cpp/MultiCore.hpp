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
extern int numberOfWorker;
extern LinkedList primesList;
extern LinkedList *head;
extern LinkedList* PrimListLast;

static std::mutex timeMutex;
static std::mutex primeMutex;
static std::mutex Calculate;
static std::mutex setMaxPrime;

class MultiCore
{
public:

	static void threadprog();
	static void run();
};
