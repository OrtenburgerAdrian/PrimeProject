#pragma once
#include "Worker.hpp"
#include "Threads.hpp"

static std::mutex getCal;
void Worker::thread_calculate() {
	static unsigned long long isItAPrime = 1;
	unsigned long long isItAPrime2;
	while(true){
        getCal.lock();
        isItAPrime = isItAPrime + 2;
        isItAPrime2 = isItAPrime;
        getCal.unlock();
#ifdef __linux__
        Communicator::sendMessage(isItAPrime2, IsItAPrime::isItAPrime(isItAPrime2));
#endif
    }
}
void Worker::start() {
	Threads::start("worker",numberOfWorker);
}
