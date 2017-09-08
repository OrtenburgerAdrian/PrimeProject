#include "WorkList.hpp"
#if defined __linux__
WorkList::WorkList(int lengthOfList){
    listLength = lengthOfList;
    data[listLength] = {false, false};
    sem_init(&semWrite,0,listLength);
    sem_init(&semRead,0,0);

    iTCPReadNumber = 3;
    iThreadMax = 0;
    iTCPWrite = 0; //Index steht auf dem Wert, der noch nicht beschrieben ist.
}


void WorkList::TCPWrite(char byte){
    bool b;
    for(int i = 0; i < 8; i++){
        sem_wait(&semWrite); //use Write-Token
            b = byte & 0x01; //get the first bit
            byte = byte >> 1; //bitshift
            data[iTCPWrite].writeFromMessage(b); //write
            iTCPWrite = (iTCPWrite+1) % listLength; //increment WritePointer
        sem_post(&semRead); //give Read-Token
    }
}

char WorkList::TCPRead(){
    char returnByte = 0;
    bool b;
    for (int i = 0; i < 8 ;i++){
        sem_wait(&semRead); //use Read-Token
            b = data[iTCPRead + i].getResult(); //get bit
            returnByte << 1; //bitshift
            returnByte += b; //add bit
            iTCPRead = (iTCPRead + 1) % listLength; //increment ReadPointer
        sem_post(&semWrite); //give Write-Token
    }
    return returnByte;
}
#endif
void WorkList::setResult(unsigned long long number, bool isNonPrime){
    int index = numberToIndex(number);
    data[index].setResult(isNonPrime);
}

unsigned long long WorkList::getNextTest(){
    mutexReplaceThread.lock();
    int index = (iThreadMax + 1) % listLength;
    while(true){
        if (index != iTCPWrite && data[index].isCheckable()){
            iThreadMax = index;
            data[index].setIsChecking();
            mutexReplaceThread.unlock();
            return indexToNumber(index);
        }else{
            while(index == iTCPWrite){
                //just waitin
            }
            if(data[index].isNotPrime()){
                index = (index+1) % listLength;
            }
        }
    }
}

unsigned long long WorkList::indexToNumber(int index){
    unsigned long long base = iTCPReadNumber;
    int baseIndex = numberToIndex(base);
    index = index > baseIndex ? index : index + listLength;

    return ((index - baseIndex) * 2) + base;
}
int WorkList::numberToIndex(unsigned long long number){
    return ((number-3) / 2) % listLength;
}
