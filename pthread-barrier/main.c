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
    fprintf(stderr, "[FINE] Thread spawned\n");
    sleep(count++);
    int ret = mybarrier_wait(barrier);
    if (ret == 0) {
        fprintf(stderr, "[FINE] Thread awake\n");
    } else {
        fprintf(stderr, "[WARNING] Failed to barrier thread (MAX == 3)\n");
    }

    return NULL;
}

int test_not_enough() { // will wait forever.
    pthread_t threads[2];
    barrier = mybarrier_init(3);
    for (int i = 0; i < 2; ++i) {
        if (pthread_create(&threads[i], NULL, thread, NULL) != 0) {
            perror("Failed to created pthread");
            return 1;
        }
    }

    mybarrier_destroy(barrier);
    fprintf(stderr, "[FINE] Barrier destroyed\n");
    sleep(2);
    return 0;
}

int test_max() { // will barrier up to 3 and the 4th will fail the barrier.
    pthread_t threads[4];
    barrier = mybarrier_init(3);
    for (int i = 0; i < 4; ++i) {
        if (pthread_create(&threads[i], NULL, thread, NULL) != 0) {
            perror("Failed to created pthread");
            return 1;
        }
    }

    mybarrier_destroy(barrier);
    fprintf(stderr, "[FINE] Barrier destroyed\n");
    sleep(5);
    return 0;
}

int test_destroy() { // will wait forever.
    barrier = mybarrier_init(3);
    mybarrier_destroy(barrier);
}

int test_destroy2() { // will exit immediately.
    barrier = mybarrier_init(0);
    mybarrier_destroy(barrier);
}

int main(void) {

    test_max();
    // test_not_enough();
    // test_destroy();
    // test_destroy2();

    return 0;
}