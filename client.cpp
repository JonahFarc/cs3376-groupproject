#include "client_functions.cpp"

int main(int argc, char *argv[])
{
	if (argc != 4)
		error("Please enter the host, port number, and protocol, like so: ./client host port protocol (ex: ./client cs2 30000 udp)");
	if (strcmp(argv[3], "udp") == 0)
		clientConnect_udp(argv[1], atoi(argv[2]), sendMessageToServer_udp);
	else if (strcmp(argv[3], "tcp") == 0)
		clientConnect_tcp(argv[1], atoi(argv[2]), sendMessageToServer_tcp);
	else
		error("Please enter the host, port number, and protocol, like so: ./client host port protocol (ex: ./client cs2 30000 udp)");

    return 0;
}
