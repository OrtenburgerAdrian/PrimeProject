//Benjamin
#pragma once
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <atomic>
#include <time.h>

/**
 *  Beschreibt ein Element in der WorkList.
 *  Es werden die 4 Zustände "zu bearbeiten", "wird bearbeitet", "Ergebnis: Keine Primzahl" und "Ergebnis: Unbestimmt." dargestellt.
**/
struct WorkListElement{

        bool blockTCPRead;
        bool blockWorker;

        //Setzt: "wird bearbeitet"
        void setIsChecking(){
            blockTCPRead = true;
            blockWorker = true;
        };

        //Setzt je nach Übergabe: "zu bearbeiten" oder "Ergebnis: Keine Primzahl"
        //Dabei ist es wichtig, dass blockWorker zuletzt gesetzt wird.
        void writeFromMessage(bool b){
            blockTCPRead = b;
            blockWorker = false;
        }

        //Setzt je nach Übergabe: "Ergebnis: Keine Primzahl" oder "Ergebnis: Unbestimmt."
        //Dabei ist es wichtig, dass blockTCPRead zuletzt gesetzt wird.
        void setResult(bool isNonPrime){
            blockWorker = !isNonPrime;
            blockTCPRead = false;
        };

        //Wartet, bis ein Ergebnis feststeht und gibt true für "Ergebnis: Unbestimmt." und false für "Ergebnis: Keine Primzahl"
        bool getResult(){
            while(blockTCPRead){
                nanosleep((const struct timespec[]){{0, 10L}}, NULL);
            }
            return (blockWorker);
        }

        //Um den enthaltenen Wert lesbarer zu machen, folgen ein paar umschließende ausgaben.
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
        WorkList(int lengthOfList); //Konstruktor
        std::atomic<unsigned long long> iTCPReadNumber; //Bestimmt den "Schnitt" in dem Ringbuffer mit dem aktuell niedrigsten relevanten Wert. Die Position des Schnitts ergibt sich mathematisch.
        int listLength;
        int iThreadMax; //Index, der dem letzten Thread zugewiesen wurde.
        int iTCPWrite; //Index steht auf dem Wert, der als nächstes beschrieben werden soll.

        //Klassische Semaphoren um den Ringbuffer synchron zu halten.
        sem_t semWrite;
        sem_t semRead;

        //Wird benötigt, um Threadsicher eine zu berechnende Zahl für einen Workerthread auszugeben.
        std::mutex mutexReplaceThread;

        void TCPWrite(char byte);   //Schreibt die Ergebnisse im Übergebenen Byte an die entsprechende Stelle der WorkList.
        char TCPRead();             //Kehrt mit einem Byte mit 8 Ergebnissen zurück. Sperrt den aufrufenden Thread, bis das Ergebnis vorhanden ist.
        std::vector<unsigned long long> getSecuredPrimes(); //Gibt einen Vektor mit den Primzahlen innerhalb der nächsten 8 Ergebnisse zurück. Funktioniert so nur für den letzten Peer.

        unsigned long long getNextTest(); //Gibt die nächste zu prüfende Zahl zurück. Threadsicher.
        void setResult(unsigned long long number, bool isNonPrime); //Setzt das Ergebnis der Berechnung eines Threads. NICHT das Ergebnis eines vorherigen Peers.

    private:
        WorkListElement* data; //Kopf der Datenstruktur

        unsigned long long indexToNumber(int index); //Errechnet aus dem Index die aktuell repräsentierte Zahl mithilfe von iTCPReadNumber
        int numberToIndex(unsigned long long number); ////Errechnet den Index aus einer gegebenen Zahl. Interessanterweise funktioniert das rein mathematisch.
};
