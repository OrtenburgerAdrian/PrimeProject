#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

	void Observer::run() {
		std::cout << " run communicdddddddddddddddddddddddddddator.run();" << std::endl;
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


