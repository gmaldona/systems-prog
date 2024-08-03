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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mybarrier.h"

//==================================================================== 80 ====>>

mybarrier_t *mybarrier_init(unsigned int count) {
    mybarrier_t *barrier = malloc(sizeof(*barrier));

    if (NULL == barrier) {
        perror("Failed to allocate memory");
        return NULL;
    }

    barrier->count = count;
    if (pthread_mutex_init(&barrier->mutex, NULL) != 0) {
        perror("Failed to initialize barrier mutex");
        free(barrier);
        return NULL;
    }

    if (pthread_cond_init(&barrier->cond, NULL) != 0) {
        perror("Failed to initialize barrier conditional variable");
        free(barrier);
        return NULL;
    }

    return barrier;
}

int mybarrier_destroy(mybarrier_t *barrier) {

    if (barrier == NULL) {
        return -1;
    }

    while (barrier->count > 0) {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    }

    pthread_mutex_unlock(&barrier->mutex);
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);

    free(barrier);
    return 0;
}

int mybarrier_wait(mybarrier_t *barrier) {

    if (barrier == NULL) {
        return -1;
    }

    // chance that destroy() deletes both and NULL pointer exception??
    if (&(barrier->mutex) == NULL || &(barrier->cond) == NULL) {
        return -1;
    }

    pthread_mutex_lock(&barrier->mutex);
    // any thread after count will return 0 and not block.
    barrier->count--;
    if (barrier->count > -1) {
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);
    } else {
        pthread_mutex_unlock(&barrier->mutex);
        return -1;
    }

    while (barrier->count > 0) {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    }
    pthread_mutex_unlock(&barrier->mutex);
    return 0;
}

//==================================================================== 80 ====>>


