CC = g++
CPPFLAGS = -I.

all: main

main: main.o serverevent.o

main.o: main.cpp serverevent.h
serverevent.o: serverevent.cpp

clean:
	rm *.o main
