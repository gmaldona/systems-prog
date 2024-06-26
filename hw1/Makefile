# Homework Assignment #1
#
# author: Gregory Maldonado
# email : gmaldonado@cs.binghamton.edu
# date  : 2024-06-24
# web   : https://cs.binghamton.edu/~gmaldonado/
#
# Graduate student @ Thomas J. Watson College of Engineering and Applied
# Sciences, Binghamton University.

CC     = gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic

default: lib

.PHONY: test
test: hw1_test.c
	$(CC) $(CFLAGS) -L. hw1_test.c -lhw1 -o build/test

# https://stackoverflow.com/questions/9853419
lib: hw1_str.o hw1_myprintf.o
	ar rcs libhw1.a hw1_str.o hw1_myprintf.o

hw1_myprintf.o: hw1_myprintf.c
	$(CC) $(CFLAGS) -c hw1_myprintf.c

hw1_str.o: hw1_str.c
	$(CC) $(CFLAGS) -c hw1_str.c

.PHONY: clean
clean:
	$(RM) *.o *.a
	$(RM) -r build