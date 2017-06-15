#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

class Communicator
{

public:
	//Benni:
	static void startListener();

	static void run();

	static void sendMessage(unsigned long long maybePrime, bool isPrime);
};
