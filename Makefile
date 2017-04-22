SHELL = /bin/sh
FLAGS = -Wall -g -std=c99
CC = gcc

all:    	echo_s echo_c

echo_s:     echo_s.c server_functions.c log_s.c
	$(CC) $(FLAGS) -o echo_s echo_s.c

echo_c:		echo_c.c client_functions.c
	$(CC) $(FLAGS) -o echo_c echo_c.c	

clean:
	rm echo_s echo_c
