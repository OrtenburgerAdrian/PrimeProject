//Benjamin
#pragma once
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <atomic>
#include <time.h>

struct WorkListElement{
        bool blockTCPRead;
        bool blockWorker;

        void setIsChecking(){
            blockTCPRead = true;
            blockWorker = true;
        };

        void writeFromMessage(bool b){
            blockTCPRead = b;
            blockWorker = false;
        }

        void setResult(bool isNonPrime){
            blockWorker = !isNonPrime;
            blockTCPRead = false;
        };

        bool getResult(){
            while(blockTCPRead){
                nanosleep((const struct timespec[]){{0, 10L}}, NULL);
            }
            return (blockWorker);
        }

        bool isReadyToSend(){
            return !blockTCPRead && blockWorker;
        };
        bool isCheckable(){
            return blockTCPRead && !blockWorker;
        };
        bool isNotPrime(){
            return !blockTCPRead && !blockWorker;
        };

        //Dasselbe nochmal mit Mutex'n
        /*
        std::mutex blockTCPRead;
        bool blockWorker;

        void setIsChecking(){
            blockTCPRead.lock();
            blockWorker = true;
        };

        void writeFromMessage(bool b){
            if (b){
                blockTCPRead.lock();
            }else{
                blockTCPRead.unlock();
            }
            blockWorker = false;
        }

        void setResult(bool isNonPrime){
            blockWorker = !isNonPrime;
            blockTCPRead.unlock();
        };

        bool getResult(){
            //blockTCPRead should always be FALSE if this function is called.
            blockTCPRead.lock();
            return (blockWorker);
            blockTCPRead.unlock();
        }
        */
};

class WorkList{
    public:
        WorkList(int lengthOfList);
        std::atomic<unsigned long long> iTCPReadNumber;
        int listLength;
        int iThreadMax;
        int iTCPWrite; //Schreibkopf
        //int iTCPRead; //Lesekopf

        sem_t semWrite;
        sem_t semRead;

        std::mutex mutexReplaceThread;

        void TCPWrite(char byte);
        char TCPRead();
        std::vector<unsigned long long> getSecuredPrimes();

        unsigned long long getNextTest();
        void setResult(unsigned long long number, bool isNonPrime);

    private:
        WorkListElement* data;

        unsigned long long indexToNumber(int index);
        int numberToIndex(unsigned long long number);
};
