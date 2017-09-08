#pragma once
#if defined __linux__
#include <semaphore.h>
#endif
#include <mutex>

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
            //blockTCPRead should always be FALSE if this function is called.
            if(!blockTCPRead){
                return (blockWorker);
            }
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
};

class WorkList{
    public:
        WorkList(int lengthOfList);
        unsigned long long iTCPReadNumber;
        int listLength;
        int iThreadMax;
        int iTCPWrite;
        int iTCPRead;

#if defined __linux__
        sem_t semWrite;
        sem_t semRead;
#endif
        std::mutex mutexReplaceThread;

        void TCPWrite(char byte);
        char TCPRead();

        unsigned long long getNextTest();
        void setResult(unsigned long long number, bool isNonPrime);

    private:
        WorkListElement data[];

        unsigned long long indexToNumber(int index);
        int numberToIndex(unsigned long long number);
};
