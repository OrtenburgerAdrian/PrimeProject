#pragma once
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
#include <thread>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "IsItAPrime.hpp"
#include "LinkedList.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "Worker.hpp"
#include "Log.hpp"

#ifdef _WIN32
    #include <dos.h>
    #include <windows.h>
#endif

class Log
{
public:
 static void logerror(std::string Nachricht);
 static void log(unsigned long long prime);
 static void log(std::string Nachricht);
 static void logtime();
private:

};

