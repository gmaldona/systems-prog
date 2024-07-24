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
CFLAGS = # -Wall -Wextra -Wconversion -pedantic

default: switch_column oz_demo

switch_column: switch_column.c
	$(CC) $(CFLAGS) switch_column.c -o switch_column

oz_demo: oz_demo.c
	$(CC) $(CFLAGS) oz_demo.c -o oz_demo

.PHONY: zip
zip:
	mkdir -p build
	zip hw2_code_gmaldonado.zip switch_column.c oz_demo.c Makefile

.PHONY: clean
clean:
	$(RM) switch_column oz_demo