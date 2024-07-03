/*
 * Homework Assignment #1
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2024-06-24
 * web   : https://cs.binghamton.edu/~gmaldonado/
 *
 * Graduate student @ Thomas J. Watson College of Engineering and Applied
 * Sciences, Binghamton University.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#define printf(format, ...) myprintf(format, __VA_ARGS__)
#define MYMSG(format, ...) do {\
   char* _format = (char *) malloc((sizeof(char) * strlen(format)) +\
                                   (sizeof(char) * strlen(__FILE__)) +\
   /* 37 characters vvvv */        37);/*4 is the extra characters in between*/\
   sprintf(_format, "Original message --> %s:%d: %s",\
                                          __FILE__, __LINE__, format);\
   printf(_format, __VA_ARGS__);\
   free(_format);\
} while (0)

//==================================================================== 80 ====>>

// prototype for II.1.
int str_manip(char * str, char * substr);

// prototype for II.2.
void myprintf(const char * format, ...);

//==================================================================== 80 ====>>
