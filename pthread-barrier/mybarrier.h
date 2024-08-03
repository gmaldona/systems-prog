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

#ifndef _MYBARRIER_H
#define _MYBARRIER_H

#include <pthread.h>
#include <errno.h>

//==================================================================== 80 ====>>

typedef struct _mybarrier_t {
  int count;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} mybarrier_t;

mybarrier_t *mybarrier_init(unsigned int count);
int mybarrier_destroy(mybarrier_t *barrier);
int mybarrier_wait(mybarrier_t *barrier);

#endif //#ifndef _MYBARRIER_H

//==================================================================== 80 ====>>