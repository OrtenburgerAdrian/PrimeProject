//Adrian
#pragma once
#include "Worker.hpp"
#include "Threads.hpp"

static std::mutex memcpyMutex;
static std::mutex getCal;

/*Rahmen-Funktion, für die MultiComputing-Worker-Threads; Thread-Sicher*/
void Worker::thread_calculate() {
	memcpyMutex.lock();
	void * msgbuffer = malloc(sizeof(unsigned long long));
	memcpyMutex.unlock();
	static unsigned long long isItAPrime = 1;
	unsigned long long isItAPrime2;
	while (true) {
		getCal.lock();
		isItAPrime = isItAPrime + 2;
		isItAPrime2 = isItAPrime;
		getCal.unlock();

#ifdef __linux__ 
		Communicator::sendMessage(isItAPrime2, IsItAPrime::isItAPrime(isItAPrime2), msgbuffer); //Auf Primzahl pruefen und senden der Zahl, mit der Information, ob der Worker glaubt, dass es eine Primzahl ist oder nicht.
#endif
	}
}
/*Startet die Worker-Threads*/
void Worker::start() {
	Threads::start("worker", numberOfWorker);
}
