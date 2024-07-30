/*
 * CS 551 pthread barrier
 * This file needs to be turned in.	
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2024-07-04
 * web   : https://cs.binghamton.edu/~gmaldonado/
 *
 * Graduate student @ Thomas J. Watson College of Engineering and Applied
 * Sciences, Binghamton University.
 */

#include <stdio.h>
#include<unistd.h>

#include "mybarrier.h"

//==================================================================== 80 ====>>

mybarrier_t* barrier;
volatile unsigned int threads;

void* thread(void* arg) {
   threads++;
   sleep(threads);

   return NULL;
}

int main(void) {

   pthread_t threads[3]; 
   barrier = mybarrier_init(3);
   for (int i = 1; i <= 15; i *= 3) {
      if (pthread_create(&threads[i], NULL, thread, NULL) != 0) {
         perror("Failed to created pthread");
         return 1;
      }
   }

   for (int i = 0; i < 4; ++i) {
      if (pthread_join(threads[i], NULL) != 0) {
         perror("Failed to join pthread");
         return 1;
      }
   }
   // mybarrier_destroy(barrier);

   return 0;
}