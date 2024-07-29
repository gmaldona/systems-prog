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
#include "mybarrier.h"

//==================================================================== 80 ====>>

mybarrier_t * mybarrier_init(unsigned int count)
{
    mybarrier_t * barrier = malloc(sizeof(*barrier));
    
	if (NULL == barrier) {
        return NULL;
    }
	
	/* Add your implementation here */
    
    return barrier;	

}

int mybarrier_destroy(mybarrier_t * barrier)
{
	int ret = 0;
	
	/* Add your implementation here */
	
	return ret;
}

int mybarrier_wait(mybarrier_t * barrier)
{
	int ret = 0;
	
	/* Add your implementation here */
	
	return ret;
}

//==================================================================== 80 ====>>


