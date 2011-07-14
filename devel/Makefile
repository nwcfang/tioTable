#Тестирование функций семейства tioTable
all: myapp

CC=gcc
INCLUDE=./
CFLAGS=-g -Wall

myapp: tioTableBegin.o tioTableRecord.o tioTableEnd.o main.o
	$(CC) -o $@ $(CFLAGS) main.o tioTableBegin.o tioTableRecord.o tioTableEnd.o

main.o: main.c
	$(CC) -o $@ $(CFLAGS) -c -I$(INCLUDE) main.c

tioTableBegin.o: tioTableBegin.c tiotb.h
	$(CC) -o $@ $(CFLAGS) -c -I$(INCLUDE) tioTableBegin.c

tioTableRecord.o: tioTableRecord.c tiotb.h
	$(CC) -o $@ $(CFLAGS) -c -I$(INCLUDE) tioTableRecord.c

tioTableEnd.o: tioTableEnd.c tiotb.h
	$(CC) -o $@ $(CFLAGS) -c -I$(INCLUDE) tioTableEnd.c
clean:
	rm myapp main.o tioTableBegin.o tioTableRecord.o tioTableEnd.o

