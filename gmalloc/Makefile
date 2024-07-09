# CS 551 Project "Memory manager".
#
# author: Gregory Maldonado
# email : gmaldonado@cs.binghamton.edu
# date  : 2024-07-04
# web   : https://cs.binghamton.edu/~gmaldonado/
#
# Graduate student @ Thomas J. Watson College of Engineering and Applied
# Sciences, Binghamton University.

CC 	= gcc
CLAGS = # -Wall -Wextra -Wconversion -pedantic

default: lib

.PHONY: main
main: bitmap.o memory_manager.o
	mkdir -p build
	$(CC) $(CFLAGS) -o build/test_main test_main.c bitmap.c memory_manager.c

bitmap.o: bitmap.c
	$(CC) $(CFLAGS) -c bitmap.c

memory_manager.o: memory_manager.c
	$(CC) $(CFLAGS) -c memory_manager.c

.PHONY: zip
zip:
	zip proj1_gmaldonado.zip bitmap.c common.h interposition.h memory_manager.*

.PHONY: clean
clean:
	$(RM) *.o *.a
	$(RM) -r build