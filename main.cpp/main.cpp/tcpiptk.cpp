//general import
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sstream>

//specific import
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include "tcpiptk.hpp"

int listeningSocketfd;
int connectedSocketfd;
int establishedSocketfd;
void error(char *msg)
{
    perror(msg);
    exit(1);
}
void tcpiptk::closeSocket(int socketfd){
	if(close(listeningSocketfd)<0){
		error("close listening socket");
	}
}
void tcpiptk::shutdownSocket(int socketfd){
    if(shutdown(socketfd,SHUT_RDWR)<0){
    error("shutdown Socket");
    }
}
void tcpiptk::closeAndShutdownSocket(int socketfd){
    tcpiptk::shutdownSocket(socketfd);
    tcpiptk::closeSocket(socketfd);
}

int tcpiptk::createSocket (int portno){
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     //Öffnet den Socket
     listeningSocketfd = socket(AF_INET, SOCK_STREAM, 0);
     if (listeningSocketfd < 0) {
        error("ERROR opening socket");
     }

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(listeningSocketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		error("ERROR on binding");
	 }
	 return listeningSocketfd;
}
int tcpiptk::connectSocket (char* hostname, int portno){
    struct sockaddr_in serv_addr;
    struct hostent *server;

    connectedSocketfd= socket(AF_INET, SOCK_STREAM, 0);
    if (connectedSocketfd < 0){
        error("ERROR opening socket");
    }
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(connectedSocketfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
	}
	return connectedSocketfd;
}

std::string tcpiptk::getMessage(int establishedSocketfd){
	int n;
    char message[256];
	bzero(message,256);
	n = read(establishedSocketfd,message,255);
	if (n < 0){
		error("ERROR reading from socket");
	}
	std::string str = message;
	return str;
}
int tcpiptk::acceptConnection(int sockfd){
	unsigned int clilen;
	struct sockaddr_in cli_addr;

	listen(sockfd,100);
	clilen = sizeof(cli_addr);
	establishedSocketfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (establishedSocketfd < 0){
		error("ERROR on accept");
	}
	printf("Got a connection *yeah*!\n");
	return establishedSocketfd;
}
int tcpiptk::writeMessage(int sockfd, const void *message, size_t length){
    int n = write(sockfd,message,length);
    if (n < 0){
		error("ERROR writing to socket");
	}
	return n;
}

/* Derivated from "man 3 getifaddrs" */
char* tcpiptk::getMyIP(){
	struct ifaddrs *ifaddr, *ifa;
           int family, s, n;
           char host[NI_MAXHOST];

           if (getifaddrs(&ifaddr) == -1) {
               perror("getifaddrs");
               exit(EXIT_FAILURE);
           }

           /* Walk through linked list, maintaining head pointer so we
              can free list later */
           for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
               if (ifa->ifa_addr == NULL)
                   continue;

               family = ifa->ifa_addr->sa_family;

               /* For an AF_INET* interface address, display the address */

               if (family == AF_INET || family == AF_INET6) {
                   s = getnameinfo(ifa->ifa_addr,
                           (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                                 sizeof(struct sockaddr_in6),
                           host, NI_MAXHOST,
                           NULL, 0, NI_NUMERICHOST);
                   if (s != 0) {
                       printf("getnameinfo() failed: %s\n", gai_strerror(s));
                       exit(EXIT_FAILURE);
                   }

                   printf("%-8s: %s\n", ifa->ifa_name, host);

               }
           }

           freeifaddrs(ifaddr);
}
