
class tcpiptk{
    static void closeListeningSocket(void);
    static void closeConnectedSocket(void);
    static void closeEstablishedSocket(void);
    public:
    static int createSocket (int portno);
    static int connectSocket (char* hostname, int portno);
    static std::string getMessage(int sockfd);
    static int writeMessage(int sockfd, char *message);
    static char* getMyIP();
};
