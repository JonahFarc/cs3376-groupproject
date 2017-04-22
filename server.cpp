#include "server_functions.cpp"

int main(int argc, char *argv[])
{
	switch (argc)
		{
			case 2:
				if (fork() == 0) startServer(9999, echoResult_tcp, log);
				if (fork() == 0)
					startServer(atoi(argv[1]), echoResult_tcp, echoResult_udp);
				break;
			case 3:
				if (fork() == 0) startServer(9999, echoResult_tcp, log);
				if (fork() == 0)
					startServer(atoi(argv[1]), echoResult_tcp, echoResult_udp);
				if (fork() == 0)
					startServer(atoi(argv[2]), echoResult_tcp, echoResult_udp);
				break;
			case 4:
				if (fork() == 0) startServer(9999, echoResult_tcp, log);
				if (fork() == 0)
					startServer(atoi(argv[1]), echoResult_tcp, echoResult_udp);
				if (fork() == 0)
					startServer(atoi(argv[2]), echoResult_tcp, echoResult_udp);
				if (fork() == 0)
					startServer(atoi(argv[3]), echoResult_tcp, echoResult_udp);
				break;
			default:
				error("Please provide up to 3 ports to monitor like so: ./server port1 port2 port3 (eg. ./server 1000, 1001, 1002)");
				return 1;
		}
    return 0; 
}
