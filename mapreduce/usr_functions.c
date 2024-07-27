/*
 * CS 551 Project "MapReduce".
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2024-07-23
 * web   : https://cs.binghamton.edu/~gmaldonado/
 *
 * Graduate student @ Thomas J. Watson College of Engineering and Applied
 * Sciences, Binghamton University.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "common.h"
#include "usr_functions.h"

#define ALPHABET_SZ 26

//==================================================================== 80 ====>>

/* User-defined map function for the "Letter counter" task.  
   This map function is called in a map worker process.
   @param split: The data split that the map function is going to work on.
                 Note that the file offset of the file descriptor split->fd should
                 be set to the proper position when this map function is called.
   @param fd_out: The file descriptor of the intermediate data file output by the
                  map function.
   @ret: 0 on success, -1 on error.
 */

int letter_counter_map(DATA_SPLIT * split, int fd_out)
{
    fprintf(stderr, "partition size %zu\n", split->size);
    size_t counter[26];
    char read_buff[split->size + 1];

    memset(counter, 0, 26 * sizeof(size_t));
    if ((read(split->fd, read_buff, split->size)) < 0) {
        perror("Failed to read fd");
        return -1;
    }

    for (int i = 0; i < split->size; ++i) {
        if ('a' <= read_buff[i] && read_buff[i] <= 'z') {
            ++counter[read_buff[i] - 'a'];
        } else if ('A' <= read_buff[i] && read_buff[i] <= 'Z') {
            ++counter[(read_buff[i] + ' ') - 'a'];
        }
    }

    for (int i = 0; i < ALPHABET_SZ; ++i) {
        printf("%c: %zu\n", i + 'a', counter[i]);
    }

    for (int i = 0; i < ALPHABET_SZ; ++i) {
        char write_buff[16];
        if (i < ALPHABET_SZ - 1) {
            sprintf(write_buff, "%c: %zu, ", i + 'a', counter[i]);
        } else {
            sprintf(write_buff, "%c: %zu", i + 'a', counter[i]);
        }
        if (write(fd_out, write_buff, strlen(write_buff)) < 0 ) {
            perror("Failed to write to fd");
            return -1;
        }
    }

    close(split->fd);

    return 0;
}

/* User-defined reduce function for the "Letter counter" task.  
   This reduce function is called in a reduce worker process.
   @param p_fd_in: The address of the buffer holding the intermediate data files' file descriptors.
                   The imtermeidate data files are output by the map worker processes, and they
                   are the input for the reduce worker process.
   @param fd_in_num: The number of the intermediate files.
   @param fd_out: The file descriptor of the final result file.
   @ret: 0 on success, -1 on error.
   @example: if fd_in_num == 3, then there are 3 intermediate files, whose file descriptor is 
             identified by p_fd_in[0], p_fd_in[1], and p_fd_in[2] respectively.

*/
int letter_counter_reduce(int * p_fd_in, int fd_in_num, int fd_out)
{
    // add your implementation here ...

    return 0;
}

// Bonus
/* User-defined map function for the "Word finder" task.  
   This map function is called in a map worker process.
   @param split: The data split that the map function is going to work on.
                 Note that the file offset of the file descripter split->fd should be set to the properly
                 position when this map function is called.
   @param fd_out: The file descriptor of the itermediate data file output by the map function.
   @ret: 0 on success, -1 on error.
 */
int word_finder_map(DATA_SPLIT * split, int fd_out)
{
    fprintf(stderr, "Not Implemented");
    return 0;
}

// Bonus
/* User-defined reduce function for the "Word finder" task.  
   This reduce function is called in a reduce worker process.
   @param p_fd_in: The address of the buffer holding the intermediate data files' file descriptors.
                   The imtermeidate data files are output by the map worker processes, and they
                   are the input for the reduce worker process.
   @param fd_in_num: The number of the intermediate files.
   @param fd_out: The file descriptor of the final result file.
   @ret: 0 on success, -1 on error.
   @example: if fd_in_num == 3, then there are 3 intermediate files, whose file descriptor is 
             identified by p_fd_in[0], p_fd_in[1], and p_fd_in[2] respectively.

*/
int word_finder_reduce(int * p_fd_in, int fd_in_num, int fd_out)
{
    fprintf(stderr, "Not Implemented");
    return 0;
}

//==================================================================== 80 ====>>