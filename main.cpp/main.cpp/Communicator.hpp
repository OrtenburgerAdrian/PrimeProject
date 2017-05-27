#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "observer.hpp"
#include "communicator.hpp"
#include "worker.hpp"

class Communicator
{

	static void startListener();

public:
	static void run();
};