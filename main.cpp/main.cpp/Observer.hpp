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
		//Benni: 
		static void addCommunicator();
		//Benni: 
		static void initCommunicator();
		//Benni: 
		static void deleteCommunicator();
		//Benni: 
		static void startListener();
		//Adrian:
		static int logPrime(unsigned long long a);


	public:
		//Benni: 
		static void run();

	};
