#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

class Communicator
{


public:
	//Benni:
	static void startListener();

	static void run();
};
