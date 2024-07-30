# CS 551 pthread barrier
#
# author: Gregory Maldonado
# email : gmaldonado@cs.binghamton.edu
# date  : 2024-07-04
# web   : https://cs.binghamton.edu/~gmaldonado/
#
# Graduate student @ Thomas J. Watson College of Engineering and Applied
# Sciences, Binghamton University.

TARGET=mybarrier.o
CFLAGS=-Wall -pthread -D PIPE_BUF_MAX=1024
CC=gcc

all: $(TARGET)

.PHONY: main
main: main.c
	mkdir -p build
	$(CC) $(CFLAGS) main.c mybarrier.c -o build/main -pthread
	
mybarrier.o: mybarrier.c mybarrier.h
	$(CC) $(CFLAGS) -c $*.c
	

clean:
	rm -rf *.o *.a $(TARGET)

