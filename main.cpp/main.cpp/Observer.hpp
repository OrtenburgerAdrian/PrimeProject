#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "observer.hpp"
#include "communicator.hpp"
#include "worker.hpp"

	class Observer
	{
		static void addCommunicator();
		static void deleteCommunicator();
		static void startListener();
		static void logPrime();
		static void initCommunicator();

	public:
		static void run();

	};
