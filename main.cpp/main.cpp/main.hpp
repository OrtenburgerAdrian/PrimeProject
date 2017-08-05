#pragma once
//ich bin soooooo stolz auf mich, für die idee mit der main hpp, durch das spielen mit ein und ausklammern, wegen der fehler suche... :D

#include <time.h>
#include <thread>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <mutex>
#include <map>
#include <locale>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <cstdlib>
#include <cerrno>
#include <algorithm>
#include "Worker.hpp"
#include "Threads.hpp"
#include "SingelCore.hpp"
#include "PrimeArray.hpp"
#include "Observer.hpp"
#include "MultiCore.hpp"
#include "Log.hpp"
#include "LinkedList.hpp"
#include "IsItAPrime.hpp"
#include "Communicator.hpp"


#if defined __linux__
#include <unistd.h>
#include "Observer.hpp"
#include "Communicator.hpp"

#endif
