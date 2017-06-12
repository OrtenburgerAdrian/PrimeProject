#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"

#ifdef _WIN32
    #include <dos.h>
    #include <windows.h>
#endif

class  IsItAPrime
{ public:
	//Adrian
	static bool isItAPrime(unsigned long long prim, LinkedList *head, int threadNumber);

};
