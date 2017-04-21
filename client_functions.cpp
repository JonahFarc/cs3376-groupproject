#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int clientConnect_tcp(char* host, int portno, void callback(int)) {
	int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(host);
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
	if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		error("connect");
	callback(sockfd);
	return 0;
}

int clientConnect_udp(char* host, int portno, void callback(int, sockaddr_in)) {
	int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(host);
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
	callback(sockfd, serv_addr);
	return 0;
}

void sendMessageToServer_tcp(int sockfd) {
	char buf[256];
	while (1) {
    	printf("Please enter the message: ");
    	bzero(buf, 256);
    	fgets(buf, 255, stdin);
    	if (send(sockfd, buf, strlen(buf), 0) < 0)
			error("ERROR writing to socket");
		int response = recv(sockfd, buf, strlen(buf), 0);
		if (response < 0)
			error("ERROR recv");
		else if (response == 0)
			break;
		printf("Recieved echo back: %s", buf);
	}
    close(sockfd);
}

void sendMessageToServer_udp(int sockfd, sockaddr_in server) {
	char buf[256];
	socklen_t clilen = sizeof(sockaddr_in);
	while(1) {
    	printf("Please enter the message: ");
    	bzero(buf, 256);
    	fgets(buf, 255, stdin);
    	if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) < 0)
			error("ERROR writing to socket");
		int response = recvfrom(sockfd, buf, 256, 0, (struct sockaddr*)&server, &clilen);
		if (response < 0) 
			error("ERROR recvfrom");
		else if (response == 0)
			break;
		printf("Recieved echo back: %s", buf);
	}
    close(sockfd);
}