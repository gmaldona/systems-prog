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

mybarrier_t *barrier;
volatile unsigned int count;

void *thread(void *arg) {
    printf("SPAWN\n");
    sleep(count++);
    mybarrier_wait(barrier);
    printf("WAKE\n");
    return NULL;
}

int main(void) {

    pthread_t threads[3];
    barrier = mybarrier_init(3);
    for (int i = 0; i < 3; ++i) {
        if (pthread_create(&threads[i], NULL, thread, NULL) != 0) {
            perror("Failed to created pthread");
            return 1;
        }
    }

    mybarrier_destroy(barrier);
    sleep(3);

    return 0;
}