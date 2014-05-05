
#Makefile for Assignment 2
# WILLIAM WIDMER
CC = g++
CFLAGS = -Wall -g
OBJS = main.o eavltree.o

eavl.out: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o eavl.out
eavltree.o: eavltree.cpp eavltree.h
	$(CC) -c $(CFLAGS) eavltree.cpp
clean:
	rm *.o *.gch *~ eavl.out *#



