#Makefile for Semester Project Deliverable 2
#Created 4/20/2017

SHELL = /bin/sh
PROG = server_functions client_functions log_s echo_s echo_c  
CC = gcc
FLAGS = -c -g -Wall -std=c99
OBJS = echo_s.o echo_c.o log_s server_functions.o client_functions.o

all: $(PROG)

echo_s: echo_s.c server_functions.c log_s.c
	$(CC) $(FLAGS) -o $@.o $@.c
	$(CC) -o $@ $@.o server_functions.o log_s.o
echo_c: echo_c.c client_functions.c
	$(CC) $(FLAGS) -o $@.o $@.c
	$(CC) -o $@ $@.o client_functions.o
log_s: log_s.c
	$(CC) $(FLAGS) -o $@.o $@.c
server_functions: server_functions.c
	$(CC) $(FLAGS) -o $@.o $@.c
client_functions: client_functions.c
	$(CC) $(FLAGS) -o $@.o $@.c
clean:
	rm -f core $(PROG) $(OBJS) 
