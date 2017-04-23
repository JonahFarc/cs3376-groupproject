// file: server_functions.c
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: Contains functions necessary for the echo server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <arpa/inet.h>

//SA: Issued when a system call fails. Displays error message and aborts
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

//SA: Gets all server TCP forks and terminates them 
void exitTCPServer(int sig) 
{
	static int pids[10] = {0};
	static int counter = 0;
	if (sig < 0) 
	{
		pids[counter] = -sig;
		counter++;
		return;
	}
	for (int i = 0; i < 10; i++) 
		kill(pids[i], SIGTERM);
	exit(0);
}

//TD: initializes the TCP and UDP sockets
void intializeSockets(int *socktcp, int *sockudp) 
{
	if ((*socktcp = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("ERROR opening socket");
	if ((*sockudp = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		error("ERROR opening socket");
}

//SA: Handles initializing the sockaddr_in structure with the port# passed in 
void initializeAddrStruct(struct sockaddr_in *serv_addr, int portno) 
{
	bzero((char *) serv_addr, sizeof(*serv_addr));
	(*serv_addr).sin_family = AF_INET;
	(*serv_addr).sin_addr.s_addr = INADDR_ANY;
	(*serv_addr).sin_port = htons(portno);
}

//SA: Binds all addresses to their respective sockets. Throws error if binding fails
void bindAll(int *sockfd_tcp, int *sockfd_udp, struct sockaddr_in *serv_addr) 
{
	if (bind(*sockfd_tcp, (struct sockaddr *) serv_addr,
		  sizeof(*serv_addr)) < 0) 
		  error("ERROR on binding");
	if (bind(*sockfd_udp, (struct sockaddr *) serv_addr,
		  sizeof(*serv_addr)) < 0) 
		  error("ERROR on binding");
}

//SA: First opens a UDP socket and then handles initializing the socket address structure 
// with the port# passed in
void setupLogServer(int *sockudp, struct sockaddr_in *serv_addr, int portno) 
{
	if ((*sockudp = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		error("ERROR opening socket");
	bzero((char *) serv_addr, sizeof(*serv_addr));
	(*serv_addr).sin_family = AF_INET;
	(*serv_addr).sin_addr.s_addr = INADDR_ANY;
	(*serv_addr).sin_port = htons(portno);
}

//SA: Handles starting the server (utilizing both TCP and UDP). Keeps server alive until a "TERM" command is issued
// then handles safe termination of all server resources 	
int startServer(int portno, int callback_tcp(char[256], int, struct sockaddr_in),
				int callback_udp(char[256], int, struct sockaddr_in)) 
{
	int sockfd_tcp, newsockfd_tcp, sockfd_udp;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int pid_tcp;
	int pid_udp;
	int tempid;
	clilen = sizeof(struct sockaddr_in);
	
	intializeSockets(&sockfd_tcp, &sockfd_udp);

	initializeAddrStruct(&serv_addr, portno);
	
	bindAll(&sockfd_tcp, &sockfd_udp, &serv_addr);

	if ((pid_tcp = fork()) == 0) 
	{
		listen(sockfd_tcp, 5);
		signal(SIGUSR1, exitTCPServer);
		do 
		{	
			if ((newsockfd_tcp = accept(sockfd_tcp, (struct sockaddr*) &cli_addr, &clilen)) < 0)
				error("ERROR on accept");
			bzero(buffer, 256);
			if ((tempid = fork()) == 0) 
			{
				if(recv(newsockfd_tcp, buffer, 256, 0) < 0)
					error("ERROR reading from socket");
				callback_tcp(buffer, newsockfd_tcp, cli_addr);
				exit(0);
			}
			exitTCPServer(-tempid);
		} while (1);
	}
	else if ((pid_udp = fork()) == 0) 
	{
		do 
		{
			bzero(buffer, 256);
			if (recvfrom(sockfd_udp, buffer, 256, 0, (struct sockaddr*) &serv_addr, &clilen) < 0)
				error("recvfrom");
			if (fork() == 0) 
			{
				callback_udp(buffer, sockfd_udp, serv_addr);
				exit(0);
			}
		} while (1);
	}
	char servInput[256] = {0};
	while (strcmp(servInput, "TERM\n") != 0) 
	{
		bzero(servInput, 256);
		fgets(servInput, 255, stdin);
	}
	kill(pid_tcp, SIGUSR1);
	kill(pid_udp, SIGTERM);
	close(sockfd_tcp);
	close(sockfd_udp);
	return 0;
}
