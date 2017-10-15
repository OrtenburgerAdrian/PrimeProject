//Benjamin
#include "WorkList.hpp"

/**
 *  Verwaltet Ergebnisse für die Peer-Anwendung.
 *  Die Elemente der Liste und ihre Funktionen sind in der zugehörigen .hpp definiert.
**/

//Constructor
WorkList::WorkList(int lengthOfList){
    listLength = lengthOfList;
    data = (WorkListElement*) malloc(sizeof(WorkListElement)*lengthOfList);
    for (int i = 0; i < lengthOfList; i++){
        data[i] = {false, false};
    }
    sem_init(&semWrite,0,listLength);
    sem_init(&semRead,0,0);

    iTCPReadNumber = 3; //Wert, auf dem der Lesekopf steht.
    iThreadMax = 0; //Index, der dem letzten Thread zugewiesen wurde.
    iTCPWrite = 0; //Index steht auf dem Wert, der als nächstes beschrieben werden soll.
}

//Schreibt die Ergebnisse im Übergebenen Byte an die entsprechende Stelle der WorkList.
void WorkList::TCPWrite(char byte){
    bool b;
    for(int i = 0; i < 8; i++){
        sem_wait(&semWrite); //use Write-Token
            b = byte & 0x01; //get the first bit
            byte = byte >> 1; //bitshift
            //printf("I received the result for %llu ; it's %sa prime for the previous peer.\n", number, b ? "" : "not "); //Nützlich für Tests.
            data[iTCPWrite].writeFromMessage(b); //write
            iTCPWrite = (iTCPWrite+1) % listLength; //increment WritePointer
        sem_post(&semRead); //give Read-Token
    }
}

//Kehrt mit einem Byte mit 8 Ergebnissen zurück. Das könnte aber etwas dauern.
char WorkList::TCPRead(){
    unsigned char returnByte = 0;
    bool b;
    int iTCPRead = WorkList::numberToIndex(iTCPReadNumber);
    for (int i = 0; i < 8 ;i++){
        sem_wait(&semRead); //use Read-Token
            b = data[iTCPRead].getResult(); //Holt das Ergebnis des nächsten Elements. Wartet, falls noch keines vorhanden ist.
            returnByte = returnByte >> 1 ; //bitshift
            if (b){
                returnByte += 0x80; //Schreibt das Einzelergebnis in den Rückgabebuffer.
            }
            iTCPRead = (iTCPRead + 1) % listLength; //increment ReadPointer
            iTCPReadNumber = WorkList::indexToNumber(iTCPRead); //Erhöht den Wert, auf dem der Lesekopf steht.
        sem_post(&semWrite); //give Write-Token
    }
    return returnByte;
}

//Gibt einen Vektor mit den Primzahlen innerhalb der nächsten 8 Ergebnisse zurück. Funktioniert so nur für den letzten Peer.
std::vector<unsigned long long> WorkList::getSecuredPrimes(){
    std::vector<unsigned long long> returnPrimes;
    bool b;
    int iTCPRead = WorkList::numberToIndex(iTCPReadNumber);

    for (int i = 0; i < 8 ;i++){
        sem_wait(&semRead); //use Read-Token
            b = data[iTCPRead].getResult(); //get bit
            if(b){
                returnPrimes.push_back(WorkList::indexToNumber(iTCPRead));
            }
            iTCPRead = (iTCPRead + 1) % listLength; //increment ReadPointer
            iTCPReadNumber = WorkList::indexToNumber(iTCPRead); //Erhöht den Wert, auf dem der Lesekopf steht.
        sem_post(&semWrite); //give Write-Token
    }
    return returnPrimes;
}

//Setzt das Ergebnis der Berechnung eines Threads. NICHT das Ergebnis eines vorherigen Peers
void WorkList::setResult(unsigned long long number, bool isNonPrime){
    //printf("I found the result for %llu ; it's %sa prime for me.\n", number, isNonPrime ? "not " : ""); //Nützlich für Tests.
    int index = numberToIndex(number);
    data[index].setResult(isNonPrime);
}

//Gibt die nächste zu prüfende Zahl zurück. Threadsicher.
unsigned long long WorkList::getNextTest(){
    mutexReplaceThread.lock();
    int index = (iThreadMax + 1) % listLength;

    //Mir ist bewusst, dass eine while(true)-Schleife mit einem inneren return "bad practice" ist. Aber niemand kann mich hindern.
    while(true){
        //Ich benötige den Write-Token, um ihn auf 0 zu prüfen. In diesem Fall steht der Schreibpointer richtigerweise auf dem Readpointer und es kann sicher gelesen werden.
        int iWriteToken;
        sem_getvalue(&semWrite, &iWriteToken);
        if ((index != iTCPWrite || iWriteToken == 0) && data[index].isCheckable()){
            iThreadMax = index;
            data[index].setIsChecking();
            mutexReplaceThread.unlock();
            return indexToNumber(index);
        }else{
            //Entweder kann noch nicht gelesen werden, dann wird gewartet, bis zu prüfende Werte ankommmen.
            while(index == iTCPWrite && iWriteToken != 0){
                nanosleep((const struct timespec[]){{0, 10L}}, NULL); //they see me waitin, they hatin (Ressourcensparendes warten.)
                sem_getvalue(&semWrite, &iWriteToken); //Aktualisiert den Prüfwert "iWriteToken".
            }

            //Wenn der aktuelle Wert ist nicht zu prüfen, dann wird nur der Index inkrementiert.
            if(data[index].isNotPrime()){
                index = (index+1) % listLength;
            }
        }
    }
}

//Errechnet aus dem Index die aktuell repräsentierte Zahl mithilfe des baseIndex
unsigned long long WorkList::indexToNumber(int index){
    unsigned long long base = iTCPReadNumber;
    int baseIndex = numberToIndex(base);
    if(index < baseIndex){
        index = index + listLength;
    }
    return ((index - baseIndex) * 2) + base;
}

//Errechnet den Index aus einer gegebenen Zahl. Interessanterweise funktioniert das rein mathematisch.
int WorkList::numberToIndex(unsigned long long number){
    return ((number-3) / 2) % listLength;
}
