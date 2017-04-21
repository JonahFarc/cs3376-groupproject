SHELL = /bin/sh
FLAGS = -Wall -g
CC = g++

all:    	server client

server:     server.cpp server_functions.cpp
	$(CC) $(FLAGS) -o $@ server.cpp

client:		client.cpp client_functions.cpp
	$(CC) $(FLAGS) -o $@ client.cpp	

clean:
	rm server client 
