// file: log_s.c
// authors: DY TD SW SA AK JA
// date: 04/20/2017
// purpose: CS 3376 - 502
// description: Log server that communicates with echo_s to log the messages echo_s receives

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
#include <time.h>

//TD: starts the log server (UDP) upon being called on in the server
int startLogServer(int portno)
{
	int sockfd;
	struct sockaddr_in serv_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//TD: prints error if it cannot open the UDP socket
	if(sockfd < 0) error("ERROR OPENING UDP SOCKET FOR LOG SERVER");
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	  error("ERROR BINDIN UDP FOR LOG SERVER");
	//TD: continuous loop that will receieve UDP messages
	udp_loop(sockfd);
	close(sockfd);
}

//TD: handles zombies
void *SigCatcher(int n)
{
	wait3(NULL,WNOHANG,NULL);
}

//SW: loops listens on "portno" and send message to function "writetofile"
void udp_loop(int udp_sockfd)
{
	int n;
	struct sockaddr_in from;
	socklen_t fromlen;
	char buf[1024];
	fromlen = sizeof(struct sockaddr_in);
	while(1)
	{
	   n = recvfrom(udp_sockfd,buf,1024,0,(struct sockaddr *)&from,&fromlen);
	   if(n<0) error("ERROR recvfrom");
			write(1,buf,n);
	   //TD: writes to the echo.log file and passes the message
	   writetofile(buf);
	   if(n<0) error("ERROR sendto");
		     signal(SIGCHLD,SigCatcher);
	}
}

//SW: function to write to file
//function accepts "buf", the message and ip address, and write to file "echo.log"
void writetofile(char buf[1024])
{
	FILE *fw;
	//SW: makes echo.log it if does not exist, append to it if it does
	fw = fopen("echo.log", "a"); 
	time_t ti = time(NULL);
	//SW: get the time 
	struct tm t = *localtime(&ti); 
	fprintf(fw,"%d-%d-%d %d:%d:%d\t%s\n", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, buf); //SW: write date, message, and ipaddress to file
	//SW: save file
	fclose(fw); 
}

