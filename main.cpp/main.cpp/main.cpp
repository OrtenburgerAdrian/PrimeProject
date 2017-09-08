//Adrian
#pragma once
#include "LinkedList.hpp"
#include "SingelCore.hpp"
#include "MultiCore.hpp"

#if defined __linux__
#include <unistd.h>
#include "Observer.hpp"
#include "Communicator.hpp"
#endif
//Globale Variablen
int numberOfWorker = 0;						//Anzah der benoetigten Worker-Threads, wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
unsigned long long maxPrime = 1;			//Die groeszte bis jetzt gespeicherte Primzahl, ist für jeden Client-PC unterschiedlich.
LinkedList primesList;						//Repraesentiert die erste Node.
LinkedList *head = &primesList;				//Adresse der ersten Node.
LinkedList* PrimeListLast = &primesList;	//Adresse der letzten Node.
bool moreLog = false;						//Um alle gefundenen Primzahlen mitzuschreiben, braucht viel CPU-Time und Speicherplatz. 

int main(int argc, char *argv[]) {
#if defined __linux__
	numberOfWorker = sysconf(_SC_NPROCESSORS_ONLN) - 1;   // liest die Anzahl der CPU-Core's aus, -1 damit die Comunicator-Threads im besten fall einen eigenen Core bekommen können.
#endif

	std::string arg1 = "";
	int i = 1;
	if (*argv[i] == 'v') { moreLog = true; i++; } //Wenn "v" als parameter uebergeben wird, wird jede erarbeitete Primzahl mitgeschrieben 
	
	switch (*argv[i])
	{
	case 'm': //m = multicore
		std::cout << " run multicore.run();" << std::endl;
		MultiCore::run();
		char zahl;
		while (true) { std::cin >> zahl; } //pausirt den Thread (Betriebssystem unabhaengig), nur die Worker-Threads werden gebraucht
		break;
	case 's': //s = singlecore
		std::cout << " run singelcore.run();" << std::endl;
		SingelCore::run();
		break;
#if defined __linux__
	case 'o': //o = observer
		if (argc == 3) {
			Observer::run(atoi(argv[i + 1]));
		}
		else {
			Observer::run();
		}
		break;
	case 'c': //c = communicator
		Worker::start();
		if (argc == 3) {
			Communicator::run(argv[i + 1]);
		}
		else {
			Communicator::run();
		}
		break;
	case 'p': //p = peer-mode 
		PeerWorker::start();
		PeerCommunicator::run(atoi(argv[i + 1]));
		break;
#endif
	default: 
		std::cout << "Incorrect transfer parameters" << std::endl;
		break;
	}

#if defined _WIN64
	SingelCore::run(); //Um auch auf Windows arbeiten zukönnen, leider geht unsere Netzwerkmomunikation nur mit Linux.
#endif
}