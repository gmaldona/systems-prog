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
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>

#include "mybarrier.h"

//==================================================================== 80 ====>>

mybarrier_t * mybarrier_init(unsigned int count)
{
    mybarrier_t * barrier = malloc(sizeof(*barrier));
    
	if (NULL == barrier) {
		perror("Failed to allocate memory");
        return NULL;
    }
	
	barrier->barred_count = count;
	barrier->count = 0;
	if (pthread_mutex_init(&barrier->mutex, NULL) != 0 ) {
		perror("Failed to initialize barrier mutex");
		return NULL;
	}

	if (pthread_cond_init(&barrier->cond, NULL) != 0) {
		perror("Failed to initialize barrier conditional variable");
		return NULL; 
	}

    return barrier;
}

int mybarrier_destroy(mybarrier_t * barrier)
{
	int ret = 0;
	
	pthread_mutex_destroy(&barrier->mutex);
	pthread_cond_destroy(&barrier->cond);
	
	return ret;
}

int mybarrier_wait(mybarrier_t * barrier)
{
	int ret = 0;
	
	pthread_mutex_lock(&barrier->mutex);
	barrier->count++;
	pthread_cond_signal(&barrier->cond);
	pthread_mutex_unlock(&barrier->mutex);

	while (barrier->count < barrier->barred_count) {
		pthread_cond_wait(&barrier->cond, &barrier->mutex);
	}
	
	return ret;
}

//==================================================================== 80 ====>>


