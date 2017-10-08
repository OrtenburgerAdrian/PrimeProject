//Adrian
#include "PeerWorker.hpp"
#include "Threads.hpp"


void PeerWorker::threadprog() {
	unsigned long long test;
	while (true)
	{

	test = (*wl).getNextTest();
    //std::cout <<  "I am testing the number: " << test << std::endl;
	(*wl).setResult(test, !IsItAPrime::isItAPrime(test));
	}
}

void PeerWorker::run() {
	Threads::start("peerWorker", numberOfWorker);
}
