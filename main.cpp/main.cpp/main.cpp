//Adrian und Benni
#pragma once
#include "LinkedList.hpp"
#include "SingelCore.hpp"
#include "MultiCore.hpp"

#if defined __linux__
#include <unistd.h>
#include "Observer.hpp"
#include "Communicator.hpp"
#endif


int numberOfWorker = 0;						//Anzah der benoetigten Worker-Threads, wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
unsigned long long maxPrime = 1;			//Die groeszte bis jetzt gespeicherte Primzahl, ist f�r jeden Client-PC unterschiedlich.
LinkedList primesList;						//Repraesentiert die erste Node.
LinkedList *head = &primesList;				//Adresse der ersten Node.
LinkedList* PrimeListLast = &primesList;	//Adresse der letzten Node.


int main(int argc, char *argv[]) {

#if defined _WIN64
	numberOfWorker = 8;
#elif __linux__
	numberOfWorker = sysconf(_SC_NPROCESSORS_ONLN) - 1;   // liest die Anzahl der CPU-Core's aus, -1 damit der Comunicator-Thread im besten fall einen eigenen Core bekommen kann.
#endif
	//numberOfWorker = 1; //Uncomment to manually set number of working threads.


#if defined __linux__
	if (argc <= 1) {
		std::cout << " Inadequate transfer parameters" << std::endl;
	}
	else if (argc > 3) {
		std::cout << " Too many transfer parameters" << std::endl;
	}


	std::string arg1 = argv[1];
	if (arg1 == "multicore") {
		MultiCore::run();
		std::cout << " run multicore.run();" << std::endl;
		int zahl;
		while (true) { std::cin >> zahl; }
	}
	else if (arg1 == "singlecore") {
		SingelCore::run();
		std::cout << " run singelcore.run();" << std::endl;
	}
	else if (arg1 == "observer") {
		if (argc == 3) {
			Observer::run(atoi(argv[2]));
		}
		else {
			Observer::run();
		}
	}
	else if (arg1 == "communicator") {
		Worker::start();
		if (argc == 3) {
			Communicator::run(argv[2]);
		}
		else {
			Communicator::run();
		}
	}
	else {
		std::cout << "Incorrect transfer parameters" << std::endl;
	}
	return 0;
#elif _WIN64

	SingelCore::run(); //Um auch auf Windows arbeiten zuk�nnen, leider geht unsere Netzwerkmomunikation nur mit Linux.

#endif
}
