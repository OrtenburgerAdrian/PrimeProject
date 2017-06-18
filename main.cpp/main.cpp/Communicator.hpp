#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"

extern unsigned long long maxPrime;
extern LinkedList * head;
extern LinkedList * PrimListLast;

class Communicator
{
public:
	static void run();

	static void sendMessage(unsigned long long maybePrime, bool isLocalPrime);
};
