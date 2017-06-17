#pragma once
#include "Worker.hpp"
#include "Threads.hpp"

std::mutex getCal;
void Worker::thread_calculate() {
	static unsigned long long isItAPrime =1;
	unsigned long long isItAPrime2;
	getCal.lock();
	isItAPrime = isItAPrime + 2;
	isItAPrime2 = isItAPrime;
	getCal.unlock();
	if (IsItAPrime::isItAPrime(isItAPrime2)) {
		Communicator::sendMessage(isItAPrime2, true);
	}
	else
	{
		Communicator::sendMessage(isItAPrime2, false);
	}
}
void Worker::start() {
	Threads::start("worker",nuberOfWorker);
}
