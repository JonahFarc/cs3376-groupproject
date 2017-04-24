#Makefile for Semester Project Deliverable 2
#Two-step compilation
#Created 4/23/2017

SHELL = /bin/sh
OBJS_SERVER = $(patsubst %.o, obj/%.o, echo_s.o log_s.o server_functions.o)
OBJS_CLIENT = $(patsubst %.o, obj/%.o, echo_c.o client_functions.o)
LDFLAGS = -o 
CPPFLAGS = -Wall -g -std=gnu99 -Iinclude -c
CC = gcc

all: echo_s echo_c

echo_s: $(OBJS_SERVER)
	$(CC) $(LDFLAGS) echo_s $(OBJS_SERVER)

echo_c: $(OBJS_CLIENT)
	$(CC) $(LDFLAGS) echo_c $(OBJS_CLIENT)	

obj/%.o: src/%.c 
	$(CC) $(CPPFLAGS) -o $@ $<

clean:
	rm -f core echo_s echo_c obj/*.o
