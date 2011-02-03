#Тестирование функций семейства tioTable
#tiotb.c - tioTableBegin
all: myapp

CC=gcc
INCLUDE=./

myapp: tioTableBegin.o main.o
	$(CC) -o $@ main.o tioTableBegin.o

main.o: main.c
	$(CC) -o $@ -c -I$(INCLUDE) main.c

tioTableBegin.o: tioTableBegin.c tiotb.h
	$(CC) -o $@ -c -I$(INCLUDE) tioTableBegin.c

#tioTableEnd.o: tioTableEnd.c tiotb.h
#	$(CC) -o $@ -c tioTableEnd.c

clean:
	rm myapp main.o tioTableBegin.o

