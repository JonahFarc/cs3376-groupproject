// file: echo_c.c
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: A simple client in the internet domain using TCP/UDP
// The hostname, port number, and protocol are passed as arguments

#include <client_functions.h>

//Sends messages to the server using TCP until terminated -DY
void sendMessageToServer_tcp(int sockfd) 
{
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

//Sends messages to the server using UDP until terminated -DY
void sendMessageToServer_udp(int sockfd, struct sockaddr_in server) 
{
	char buf[256];
	socklen_t clilen = sizeof(struct sockaddr_in);
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

int main(int argc, char *argv[])
{
  	//TD: checks to make sure user has given all arguments
	if (argc != 4)
		error("Please enter the host, port number, and protocol, like so: ./client host port protocol (ex: ./client cs2 30000 udp)");
	//TD: checks for TCP or UDP and sends to appropriate method
	if (strcmp(argv[3], "udp") == 0) 
		clientConnect_udp(argv[1], atoi(argv[2]), sendMessageToServer_udp);
	else if (strcmp(argv[3], "tcp") == 0)
		clientConnect_tcp(argv[1], atoi(argv[2]), sendMessageToServer_tcp);
	else
		error("Please enter the host, port number, and protocol, like so: ./client host port protocol (ex: ./client cs2 30000 udp)");
    return 0;
}
