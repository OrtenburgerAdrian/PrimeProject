#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

class Observer
{
	//Benni:
	static void addCommunicator();
	//Benni:
	static void initCommunicator();
	//Benni:
	static void deleteCommunicator();
	//Benni:
	static void startListener();



public:
	//Benni:
	static void run();
};
