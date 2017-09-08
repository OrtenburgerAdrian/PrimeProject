#include "PeerWorker.hpp"
#include "Threads.hpp"


void PeerWorker::threadprog() {
	unsigned long long test;
	while (true)
	{
	test = (*wl).getNextTest();
	(*wl).setResult(test, IsItAPrime::isItAPrime(test));
	}
}

void PeerWorker::run() {
	Threads::start("peerWorker", numberOfWorker);
}
