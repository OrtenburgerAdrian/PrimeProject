#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

#include "observer.hpp"
#include "communicator.hpp"
#include "worker.hpp"
static int zahl = 0;
void Observer::run() {
	std::cout << " run communicdddddddddddddddddddddddddddator.run();" << std::endl;

	while (zahl <= 100) {
		Observer::logPrime(18446744073709551615);
	}
}

	void Observer::addCommunicator() {

	}
	void Observer::deleteCommunicator() {

	}
	void Observer::startListener() {

	}
	int Observer::logPrime(unsigned long long a) {
		zahl++;
		std::ofstream file;
		file.open("./log1.txt",std::ios::app);
			file << a << std::endl;
			file.close();
		return 0;

	}
	void Observer::initCommunicator() {

	}


