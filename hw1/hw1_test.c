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

#include <assert.h>
#include <string.h>

#include "hw1.h"

//==================================================================== 80 ====>>

int hw1_str_test(void) {
   str_manip("aBcAbc@defCba", "ABC");
   return 0;
}


int main(void) {
   assert(hw1_str_test() == 0);
   
   myprintf("This is a %s.\n", "test");
}

//==================================================================== 80 ====>>
