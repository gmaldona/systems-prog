/*
 * CS 551 Project "MapReduce".
 * You don't need to change this file
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2024-07-23
 * web   : https://cs.binghamton.edu/~gmaldonado/
 *
 * Graduate student @ Thomas J. Watson College of Engineering and Applied
 * Sciences, Binghamton University.
 */

#ifndef _USR_FUNCTIONS_H
#define _USR_FUNCTIONS_H

#include "mapreduce.h"

//==================================================================== 80 ====>>s

int letter_counter_map(DATA_SPLIT * split, int fd_out);
int letter_counter_reduce(int * p_fd_in, int fd_in_num, int fd_out);

/* bonus */
int word_finder_map(DATA_SPLIT * split, int fd_out);
int word_finder_reduce(int * p_fd_in, int fd_in_num, int fd_out);

#endif

//==================================================================== 80 ====>>