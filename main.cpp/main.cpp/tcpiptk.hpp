//Benjamin


/**
 *  Mit dieser Komponente wird die Nachrichtenübermittlung abgehandelt.
 *  Diese bietet für die Verbindung und Nachrichtenübermittlung die relativ rohen Methoden "createSocket", "connectSocket", "getMessage" und "writeMessage".
**/

class tcpiptk{
public:
    static std::string getPeerName(int sockfd);
    static void closeSocket(int socketfd);
    static void shutdownSocket(int socketfd);
    static void closeAndShutdownSocket(int socketfd);
    static int createSocket (int portno);
    static int connectSocket (char const * hostname, int portno);
    static int acceptConnection(int sockfd);
    static int getMessage(int establishedSocketfd, void * message, size_t length);
    static int writeMessage(int sockfd, const void *message, size_t length);
    static char* getMyIP();
};
