#Makefile for Semester Project Deliverable 2
#Two-step compilation
#Created 4/23/2017

SHELL = /bin/sh
OBJS_SERVER = $(patsubst %.o, obj/%.o, echo_s.o log_s.o server_functions.o)
OBJS_CLIENT = $(patsubst %.o, obj/%.o, echo_c.o client_functions.o)
LDFLAGS = -o 
CPPFLAGS = -Wall -g -std=c99 -Iinclude -c
CC = gcc

all: echo_s echo_c

<<<<<<< HEAD
echo_s: $(OBJS_SERVER)
	$(CC) $(LDFLAGS) echo_s $(OBJS_SERVER)
=======
echo_s: echo_s.c server_functions.c log_s.c logpo.h
	$(CC) $(FLAGS) -o echo_s echo_s.c
>>>>>>> 8061160764678c01e0641a93ba1f4990b946aa1b

echo_c: $(OBJS_CLIENT)
	$(CC) $(LDFLAGS) echo_c $(OBJS_CLIENT)	

obj/%.o: src/%.c 
	$(CC) $(CPPFLAGS) -o $@ $<

clean:
	rm -f core echo_s echo_c obj/*.o
