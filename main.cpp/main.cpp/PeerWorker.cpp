#include "PeerWorker.hpp"
#include "Threads.hpp"


void PeerWorker::run() {
	unsigned long long test;
	while (true)
	{
	test = (*wl).getNextTest; 
	(*wl).setResult(test, IsItAPrime::isItAPrime(test));
	}
}

void PeerWorker::threadprog() {
	Threads::start("peerWorker", numberOfWorker);
}