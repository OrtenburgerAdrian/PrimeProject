#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

int main(int argc, char *argv[]) {


	if (argc <= 1) {
		std::cout << " Inadequate transfer parameters" << std::endl;
	}
	else if (argc > 2) {
		std::cout << " Too many transfer parameters" << std::endl;
	}
	else {
		std::string arg1 = argv[1];
		if (arg1 == "observer") {
			Observer::run();
			std::cout << " run observer.run()" << std::endl;
		}
		else if (arg1 == "communicator") {
			Communicator::run();
			std::cout << " run communicator.run();" << std::endl;
		}
		else {
			std::cout << " Incorrect transfer parameters     " << std::endl;
		}
	}
	while (true)
	{
        std::cout << " Test" << std::endl;
	}

}
