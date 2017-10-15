//Adrian
#pragma once
#include "Worker.hpp"
#include "Threads.hpp"
#include "Communicator.hpp"

#include <unistd.h>

static std::mutex getCal;

/*Enthält den Rahmen, um IsItAPrime als Client/Server-Anwendung auszuführen. Thread-Sicher*/
void Worker::thread_calculate() {
	static unsigned long long isItAPrime = 1;
	unsigned long long isItAPrime2;
	while (true) {
		getCal.lock();
		isItAPrime = isItAPrime + 2;
		isItAPrime2 = isItAPrime;
		getCal.unlock();

		//Auf Primzahl pruefen und senden der Zahl, mit der Information, ob der Worker fuer die Zahl einen gemeinsamen Teiler gefunden hat.
		Communicator::sendMessage(isItAPrime2, IsItAPrime::isItAPrime(isItAPrime2));
    }
}
/*Startet die Worker-Threads*/
void Worker::start() {
	Threads::start("worker", numberOfWorker);
}
