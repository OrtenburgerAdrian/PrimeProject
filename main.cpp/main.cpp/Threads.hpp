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
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"
class Threads
{
public:
	static void start(std::string initiator, int numOfWorker) {

		switch (nuberOfWorker) {
		case 32:
		{ static std::thread t32(Worker::thread_calculate); }
		case 31:
		{ static std::thread t31(Worker::thread_calculate); }
		case 30:
		{ static std::thread t30(Worker::thread_calculate); }
		case 29:
		{ static std::thread t29(Worker::thread_calculate); }
		case 28:
		{ static std::thread t28(Worker::thread_calculate); }
		case 27:
		{ static std::thread t27(Worker::thread_calculate); }
		case 26:
		{ static std::thread t26(Worker::thread_calculate); }
		case 25:
		{ static std::thread t25(Worker::thread_calculate); }
		case 24:
		{ static std::thread t24(Worker::thread_calculate); }
		case 23:
		{ static std::thread t23(Worker::thread_calculate); }
		case 22:
		{ static std::thread t22(Worker::thread_calculate); }
		case 21:
		{ static std::thread t21(Worker::thread_calculate); }
		case 20:
		{ static std::thread t20(Worker::thread_calculate); }
		case 19:
		{ static std::thread t19(Worker::thread_calculate); }
		case 18:
		{ static std::thread t18(Worker::thread_calculate); }
		case 17:
		{ static std::thread t17(Worker::thread_calculate); }
		case 16:
		{ static std::thread t16(Worker::thread_calculate); }
		case 15:
		{ static std::thread t15(Worker::thread_calculate); }
		case 14:
		{ static std::thread t14(Worker::thread_calculate); }
		case 13:
		{ static std::thread t13(Worker::thread_calculate); }
		case 12:
		{ static std::thread t12(Worker::thread_calculate); }
		case 11:
		{ static std::thread t11(Worker::thread_calculate); }
		case 10:
		{ static std::thread t10(Worker::thread_calculate); }
		case 9:
		{ static std::thread t9(Worker::thread_calculate); }
		case 8:
		{ static std::thread t8(Worker::thread_calculate); }
		case 7:
		{ static std::thread t7(Worker::thread_calculate); }
		case 6:
		{ static std::thread t6(Worker::thread_calculate); }
		case 5:
		{ static std::thread t5(Worker::thread_calculate); }
		case 4:
		{ static std::thread t4(Worker::thread_calculate); }
		case 3:
		{ static std::thread t3(Worker::thread_calculate); }
		case 2:
		{ static std::thread t2(Worker::thread_calculate); }
		case 1:
		case 0:
		{ static std::thread t1(Worker::thread_calculate); }

		}
	}

private:

};