#Makefile для test_tioTable
all: myapp

CC=gcc
INCLUDE=./
CFLAGS=-g -Wall -lcunit

myapp: tioTable.o main.o tioSuites.o tioTests.o
	$(CC) -o $@ $(CFLAGS) main.o tioTable.o tioSuites.o tioTests.o

main.o: main.c
	$(CC) -o $@ $(CFLAGS) -c -I$(INCLUDE) main.c 

tioTable.o: tioTable.c tioTable.h
	$(CC) -o $@ $(CFLAGS) -c -I$(INCLUDE) tioTable.c

tioSuites.o: tioSuites.c tioTable.h
	$(CC) -o $@ $(CFLAGS) -c -I$(INCLUDE) tioSuites.c

tioTests.o: tioTests.c tioTable.h
	$(CC) -o $@ $(CFLAGS) -c -I$(INCLUDE) tioTests.c
clean:
	rm myapp main.o tioTable.o tioSuites.o tioTests.o
