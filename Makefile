#Makefile for Semester Project Deliverable 2
#Created 4/20/2017

SHELL = /bin/sh
PROG = echo_s echo_c log_s server_functions client_functions 
CC = gcc
FLAGS = -c -g -Wall
OBJS = echo_s.o echo_c.o log_s.o server_functions.o client_functions.o


all: $(PROG)

echo_s: echo_s.c server_functions.c
	$(CC) $(FLAGS) -o $@.o $@.c
	$(CC) -o $@ $@.o server_functions.o
echo_c: echo_c.c client_functions.c
	$(CC) $(FLAGS) -o $@.o $@.c
	$(CC) -o $@ $@.o client_functions.o
log_s: log_s.c server_functions.c
	$(CC) $(FLAGS) -o $@.o $@.c
	$(CC) -o $@ $@.o server_functions.o
server_functions: server_functions.c server_functions.h
	$(CC) $(FLAGS) -o $@.o $@.c
client_functions: client_functions.c client_functions.h
		$(CC) $(FLAGS) -o $@.o client_functions.c
clean:
	rm -f core $(PROG) $(OBJS) 
