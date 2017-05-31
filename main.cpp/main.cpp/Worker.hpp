#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

class Worker
{

	void start();
	void worker();
	void setTestingInt();
	void stop();
	void getTestingInt();
	void isActive();

public:

};


