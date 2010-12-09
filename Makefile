#Собирает файлы tabl main
all: libi bin/myapp

#LD_LIBRARY_PATH = /home/plus/doc/tabl/
INCLUDE=./include/
CC=gcc
CFLAGS=-g

vpath %.a ./lib
vpath % ./bin
vpath %.h ./include
vpath %.o ./obj
vpath %.c ./src
vpath %.so ./lib

bin/myapp: obj/main.o 
	$(CC) $(CFLAGS) -o $@ -I$(INCLUDE) obj/main.o -L./lib -ltabl -Wl,-rpath,/home/nwcfang/doc/tabl/lib

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c -I$(INCLUDE) src/main.c

libi: obj/tabl.o lib/libtabl.so

obj/tabl.o: src/tabl.c fnbl.h
	$(CC) $(CFLAGS) -o $@ -c -I$(INCLUDE)  src/tabl.c



lib/libtabl.so: obj/tabl.o
	$(CC) $(CFLAGS) -o $@ -shared -fPIC obj/tabl.o

clean:
	rm ./obj/*
	rm ./bin/*
	rm ./lib/*
