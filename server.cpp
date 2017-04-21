#include "server_functions.cpp"

int main(int argc, char *argv[])
{
	if (argc > 4 || argc < 2) {
		error("Please provide up to 3 ports to monitor.");
		return 1;
	}
	if (fork() == 0)
		startServer(9999, echoResult_tcp, log);
	else if (fork() == 0)
		startServer(atoi(argv[1]), echoResult_tcp, echoResult_udp);
	else if (fork() == 0)
		startServer(atoi(argv[2]), echoResult_tcp, echoResult_udp);
	else
		startServer(atoi(argv[3]), echoResult_tcp, echoResult_udp);
    return 0; 
}
