#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "observer.hpp"
#include "communicator.hpp"
#include "worker.hpp"

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


