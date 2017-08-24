//Benjamin
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

extern unsigned long long maxPrime; //def. in main.cpp
extern LinkedList * head; //def. in main.cpp
extern LinkedList * PrimeListLast; //def. in main.cpp

class Communicator
{
public:
	static void run();
    static void run(std::string ip);
	static void sendMessage(unsigned long long maybePrime, bool isLocalPrime);
};
