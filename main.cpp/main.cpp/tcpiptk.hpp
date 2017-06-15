
class tcpiptk{
public:
    static void closeSocket(int socketfd);
    static void shutdownSocket(int socketfd);
    static void closeAndShutdownSocket(int socketfd);
    static int createSocket (int portno);
    static int connectSocket (char* hostname, int portno);
    static int acceptConnection(int sockfd);
    static std::string getMessage(int sockfd);
    static int writeMessage(int sockfd, const void *message, size_t length);
    static char* getMyIP();
};
