# Programming Assignment #2
#
# author: Gregory Maldonado
# email : gmaldonado@cs.binghamton.edu
# date  : 2024-06-24
# web   : https://cs.binghamton.edu/~gmaldonado/
#
# Graduate student @ Thomas J. Watson College of Engineering and Applied
# Sciences, Binghamton University.

TARGET=run-mapreduce
CFLAGS=-Wall
CC=gcc

all: $(TARGET)
	
$(TARGET): main.o mapreduce.o usr_functions.o 
	$(CC) $(CFLAGS) -o $@ main.o mapreduce.o usr_functions.o
	
main.o: main.c mapreduce.h usr_functions.h
	$(CC) $(CFLAGS) -c main.c
		
mapreduce.o: mapreduce.c mapreduce.h common.h 
	$(CC) $(CFLAGS) -c $*.c
	
usr_functions.o: usr_functions.c usr_functions.h common.h
	$(CC) $(CFLAGS) -c $*.c
	
clean:
	$(RM) -rf *.o *.a $(TARGET)
	$(RM) -r build

.PHONY: zip
zip:
	mkdir -p build
	zip build/proj2_gmaldonado.zip usr_functions.c usr_functions.h \
	mapreduce.c mapreduce.h common.h Makefile README.md *.txt