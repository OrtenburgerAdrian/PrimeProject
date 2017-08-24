//Benjamin
class tcpiptk{
public:
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
