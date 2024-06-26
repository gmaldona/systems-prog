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

test: hw1_test.o
	$(CC) $(CFLAGS) -L. -o test hw1_test.o -lhw1

hw1_test.o: hw1_test.c
	$(CC) $(CFLAGS) -I. hw1_test.c

# https://stackoverflow.com/questions/9853419
lib: hw1_str.o
	ar -rcs hw1.a hw1_str.o 

hw1_str.o: hw1_str.c
	$(CC) $(CFLAGS) -c hw1_str.c
