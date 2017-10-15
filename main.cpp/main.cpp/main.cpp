//Adrian
#include "LinkedList.hpp"
#include "SingelCore.hpp"
#include "MultiCore.hpp"
#include "PeerWorker.hpp"
#include "WorkList.hpp"

#include <unistd.h>
#include "Observer.hpp"
#include "Communicator.hpp"
#include "PeerCommunicator.hpp"

//Globale Variablen
int numberOfWorker = 0;						//Anzah der benoetigten Worker-Threads, wenn numberOfWorker=0, dann wird trotzdem einer gestartet.
unsigned long long maxPrime = 1;			//Die groeszte bis jetzt gespeicherte Primzahl, ist für jeden PC im Cluster unterschiedlich.
LinkedList primesList;						//Repraesentiert die erste Node.
LinkedList *head = &primesList;				//Adresse der ersten Node.
LinkedList* PrimeListLast = &primesList;	//Adresse der letzten Node.
bool moreLog = false;						//Gibt an, ob alle gefundenen Primzahlen mitzuschreiben sind, "true" braucht viel CPU-Time und Speicherplatz.
WorkList* wl;                               //Sonderangefertigte Liste, um im Peer-Modus zu arbeiten. Die Variable ist aus zugriffspolitischen Gründen global.

int main(int argc, char *argv[]) {
	numberOfWorker = sysconf(_SC_NPROCESSORS_ONLN) - 1;   // Liest die Anzahl der CPU-Core's aus, -1 damit die Kommunikationsthreads im besten Fall einen eigenen Core bekommen können.
    //numberOfWorker = 1;

	std::string arg1 = "";
	int i = 1; //Parameteriterator
	if (*argv[i] == 'v') {moreLog = true; i++; } //Wenn "v" als parameter uebergeben wird, wird jede erarbeitete Primzahl mitgeschrieben

	switch (*argv[i])
	{
	case 'm': //m = multicore
		std::cout << " run multicore.run();" << std::endl;
		MultiCore::run();
		char zahl;

		//Die Pause wird benötigt, damit der Main-Thread nicht beendet und die erzeugten Unterthreads mitnimmt. Mit allen anderen Modi wird der Main-Thread weiter verwendet.
		while (true) { std::cin >> zahl; } //Pausiert den Thread unabhängig vom Betriebssystem, weil nur Worker-Threads gebraucht werden.
		break;
	case 's': //s = singlecore
		std::cout << " run singelcore.run();" << std::endl;
		SingelCore::run();
		break;

	case 'o': //o = observer
		if (argc == 3) { //Abkürzungsweiche, um die Zahl der erwarteten Klienten mit den Programmparametern anzugeben.
			Observer::run(atoi(argv[i + 1]));
		}
		else {
			Observer::run();
		}
		break;
	case 'c': //c = communicator
		Worker::start();
		if (argc == 3) { //Abkürzungsweiche, um die IP des Obervers mit den Programmparametern anzugeben.
			Communicator::run(argv[i + 1]);
		}
		else {
			Communicator::run();
		}
		break;
	case 'p': //p = peer-mode
		wl = new WorkList(250000); //Hauptsache erstmal 'ne Zahl hartgecoded...
		PeerWorker::run();
		PeerCommunicator::run(atoi(argv[i + 1]));
		break;

	default:
		std::cout << "Incorrect transfer parameters" << std::endl;
		break;
	}
}
