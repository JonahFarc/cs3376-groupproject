// file: client_functions.c
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: contains functions necessary for the client

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//SA: Issued when a system call fails. Displays error message and aborts
void error(const char*);

//TD: connects the client for TCP
int clientConnect_tcp(char*, int, void callback(int));

//SA: Handles UDP client connections. Connects to the port# passed in
int clientConnect_udp(char*, int, void callback(int, struct sockaddr_in));
