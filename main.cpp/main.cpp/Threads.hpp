//Adrian
//Fuer diese .hpp gibt es keine .cpp Datei.
#pragma once
#include "Worker.hpp"
#include "MultiCore.hpp"
#include <thread>
#include "PeerWorker.hpp"

class Threads
{
public:
	/*
	Startet die uebergebene Anzahl an Worker-Threads, und laesst diese die richtige Ramen-Funktion ausfuehren.

	@ numOfWorker : Die Anzahl der Threads welche gestartet werden sollen; wenn numOfWorker=0, dann wird trozdem einer gestartet (max. 32 Threads).
	@ initiator : Ein String, welcher bestimmt, welche Rahmenfunktion von den Threads ausgefuert werden soll ("worker"/"multiCore"/"peerWorker").
	*/


	static void start(std::string initiator, int numberOfWorker) {
		if (initiator == "worker")
		{
			switch (numberOfWorker) {
			case 32:
			{ static std::thread t32(Worker::thread_calculate); }
			case 31:
			{ static std::thread t31(Worker::thread_calculate); }
			case 30:
			{ static std::thread t30(Worker::thread_calculate); }
			case 29:
			{ static std::thread t29(Worker::thread_calculate); }
			case 28:
			{ static std::thread t28(Worker::thread_calculate); }
			case 27:
			{ static std::thread t27(Worker::thread_calculate); }
			case 26:
			{ static std::thread t26(Worker::thread_calculate); }
			case 25:
			{ static std::thread t25(Worker::thread_calculate); }
			case 24:
			{ static std::thread t24(Worker::thread_calculate); }
			case 23:
			{ static std::thread t23(Worker::thread_calculate); }
			case 22:
			{ static std::thread t22(Worker::thread_calculate); }
			case 21:
			{ static std::thread t21(Worker::thread_calculate); }
			case 20:
			{ static std::thread t20(Worker::thread_calculate); }
			case 19:
			{ static std::thread t19(Worker::thread_calculate); }
			case 18:
			{ static std::thread t18(Worker::thread_calculate); }
			case 17:
			{ static std::thread t17(Worker::thread_calculate); }
			case 16:
			{ static std::thread t16(Worker::thread_calculate); }
			case 15:
			{ static std::thread t15(Worker::thread_calculate); }
			case 14:
			{ static std::thread t14(Worker::thread_calculate); }
			case 13:
			{ static std::thread t13(Worker::thread_calculate); }
			case 12:
			{ static std::thread t12(Worker::thread_calculate); }
			case 11:
			{ static std::thread t11(Worker::thread_calculate); }
			case 10:
			{ static std::thread t10(Worker::thread_calculate); }
			case 9:
			{ static std::thread t9(Worker::thread_calculate); }
			case 8:
			{ static std::thread t8(Worker::thread_calculate); }
			case 7:
			{ static std::thread t7(Worker::thread_calculate); }
			case 6:
			{ static std::thread t6(Worker::thread_calculate); }
			case 5:
			{ static std::thread t5(Worker::thread_calculate); }
			case 4:
			{ static std::thread t4(Worker::thread_calculate); }
			case 3:
			{ static std::thread t3(Worker::thread_calculate); }
			case 2:
			{ static std::thread t2(Worker::thread_calculate); }
			case 1:
			case 0:
			{ static std::thread t1(Worker::thread_calculate); }
			}
		}
		else if (initiator == "multiCore") {
			switch (numberOfWorker) {
			case 32:
			{ static std::thread t32(MultiCore::threadprog); }
			case 31:
			{ static std::thread t31(MultiCore::threadprog); }
			case 30:
			{ static std::thread t30(MultiCore::threadprog); }
			case 29:
			{ static std::thread t29(MultiCore::threadprog); }
			case 28:
			{ static std::thread t28(MultiCore::threadprog); }
			case 27:
			{ static std::thread t27(MultiCore::threadprog); }
			case 26:
			{ static std::thread t26(MultiCore::threadprog); }
			case 25:
			{ static std::thread t25(MultiCore::threadprog); }
			case 24:
			{ static std::thread t24(MultiCore::threadprog); }
			case 23:
			{ static std::thread t23(MultiCore::threadprog); }
			case 22:
			{ static std::thread t22(MultiCore::threadprog); }
			case 21:
			{ static std::thread t21(MultiCore::threadprog); }
			case 20:
			{ static std::thread t20(MultiCore::threadprog); }
			case 19:
			{ static std::thread t19(MultiCore::threadprog); }
			case 18:
			{ static std::thread t18(MultiCore::threadprog); }
			case 17:
			{ static std::thread t17(MultiCore::threadprog); }
			case 16:
			{ static std::thread t16(MultiCore::threadprog); }
			case 15:
			{ static std::thread t15(MultiCore::threadprog); }
			case 14:
			{ static std::thread t14(MultiCore::threadprog); }
			case 13:
			{ static std::thread t13(MultiCore::threadprog); }
			case 12:
			{ static std::thread t12(MultiCore::threadprog); }
			case 11:
			{ static std::thread t11(MultiCore::threadprog); }
			case 10:
			{ static std::thread t10(MultiCore::threadprog); }
			case 9:
			{ static std::thread t9(MultiCore::threadprog); }
			case 8:
			{ static std::thread t8(MultiCore::threadprog); }
			case 7:
			{ static std::thread t7(MultiCore::threadprog); }
			case 6:
			{ static std::thread t6(MultiCore::threadprog); }
			case 5:
			{ static std::thread t5(MultiCore::threadprog); }
			case 4:
			{ static std::thread t4(MultiCore::threadprog); }
			case 3:
			{ static std::thread t3(MultiCore::threadprog); }
			case 2:
			{ static std::thread t2(MultiCore::threadprog); }
			case 1:
			case 0:
			{ static std::thread t1(MultiCore::threadprog); }
			}
		}
		else if (initiator == "peerWorker") {
			switch (numberOfWorker) {
			case 32:
			{ static std::thread t32(PeerWorker::threadprog); }
			case 31:
			{ static std::thread t31(PeerWorker::threadprog); }
			case 30:
			{ static std::thread t30(PeerWorker::threadprog); }
			case 29:
			{ static std::thread t29(PeerWorker::threadprog); }
			case 28:
			{ static std::thread t28(PeerWorker::threadprog); }
			case 27:
			{ static std::thread t27(PeerWorker::threadprog); }
			case 26:
			{ static std::thread t26(PeerWorker::threadprog); }
			case 25:
			{ static std::thread t25(PeerWorker::threadprog); }
			case 24:
			{ static std::thread t24(PeerWorker::threadprog); }
			case 23:
			{ static std::thread t23(PeerWorker::threadprog); }
			case 22:
			{ static std::thread t22(PeerWorker::threadprog); }
			case 21:
			{ static std::thread t21(PeerWorker::threadprog); }
			case 20:
			{ static std::thread t20(PeerWorker::threadprog); }
			case 19:
			{ static std::thread t19(PeerWorker::threadprog); }
			case 18:
			{ static std::thread t18(PeerWorker::threadprog); }
			case 17:
			{ static std::thread t17(PeerWorker::threadprog); }
			case 16:
			{ static std::thread t16(PeerWorker::threadprog); }
			case 15:
			{ static std::thread t15(PeerWorker::threadprog); }
			case 14:
			{ static std::thread t14(PeerWorker::threadprog); }
			case 13:
			{ static std::thread t13(PeerWorker::threadprog); }
			case 12:
			{ static std::thread t12(PeerWorker::threadprog); }
			case 11:
			{ static std::thread t11(PeerWorker::threadprog); }
			case 10:
			{ static std::thread t10(PeerWorker::threadprog); }
			case 9:
			{ static std::thread t9(PeerWorker::threadprog); }
			case 8:
			{ static std::thread t8(PeerWorker::threadprog); }
			case 7:
			{ static std::thread t7(PeerWorker::threadprog); }
			case 6:
			{ static std::thread t6(PeerWorker::threadprog); }
			case 5:
			{ static std::thread t5(PeerWorker::threadprog); }
			case 4:
			{ static std::thread t4(PeerWorker::threadprog); }
			case 3:
			{ static std::thread t3(PeerWorker::threadprog); }
			case 2:
			{ static std::thread t2(PeerWorker::threadprog); }
			case 1:
			case 0:
			{ static std::thread t1(PeerWorker::threadprog); }
			}
		}
	}
};
