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
#include <sys/stat.h>

#include "common.h"
#include "usr_functions.h"

#define ALPHABET_SZ 26
#define ITM_LINE_SZ 16

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
    size_t frequency[26];
    off_t start = lseek(split->fd, 0, SEEK_CUR);
    char read_buff[(split->size - start)];

    memset(frequency, 0, 26 * sizeof(size_t));
    if ((read(split->fd, read_buff, split->size - start)) < 0) {
        perror("Failed to read fd");
        return -1;
    }

    for (off_t i = 0; i < split->size - start; ++i) {
        if ('a' <= read_buff[i] && read_buff[i] <= 'z') {
            ++frequency[read_buff[i] - 'a'];
        } else if ('A' <= read_buff[i] && read_buff[i] <= 'Z') {
            ++frequency[(read_buff[i] + ' ') - 'a'];
        }
    }

    for (int i = 0; i < ALPHABET_SZ; ++i) {
        char write_buff[ITM_LINE_SZ];
        sprintf(write_buff, "%c:%zu\n", i + 'a', frequency[i]);
        if (write(fd_out, write_buff, strlen(write_buff)) < 0 ) {
            perror("Failed to write to fd");
            return -1;
        }
    }

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
    size_t frequency[ALPHABET_SZ];
    memset(frequency, 0, ALPHABET_SZ * sizeof(size_t));
    for (int i = 0; i < fd_in_num; ++i) {
        int fd = *(p_fd_in + i);

        struct stat fd_stat;
        if ((fstat(fd, &fd_stat)) < 0) {
            fprintf(stderr, "[REDUCE fd@%d %d] ", i, fd);
            perror("Failed to stat file");
            return -1;
        }

        char read_buff[fd_stat.st_size];
        if ((read(fd, read_buff, fd_stat.st_size)) < 0) {
            perror("[REDUCE] Failed to read fd");
            return -1;
        }
        size_t pos_s = 0;
        for (size_t pos_e = 0; pos_e < fd_stat.st_size; ++pos_e) {
            if (read_buff[pos_e] == '\n') {
                char  _char = read_buff[pos_s];
                char _freq[16];
                memset(_freq, 0, 16);
                memcpy(_freq, read_buff + pos_s + 2, pos_e - (pos_s + 2));
                char *end;

                size_t freq = strtoll(_freq, &end, 10);
                if (*end == '\0') {
                    // find . -name "*.itm" -print0 | xargs -0 cat | grep a | cut -d':' -f2 | awk '{t=t+$1} END{print t}'
                    frequency[_char - 'a'] += freq;
                } else {
                    return -1;
                }
                pos_s = pos_e + 1;
            }
        }
    }

    for (int i = 0; i < ALPHABET_SZ; ++i) {
        char write_buff[ITM_LINE_SZ];
        sprintf(write_buff, "%c:%zu\n", i + 'a', frequency[i]);
        if (write(fd_out, write_buff, strlen(write_buff)) < 0 ) {
            perror("Failed to write to fd");
            return -1;
        }
    }

    return 0;
}

int add_to(char* payload, char*** lines, size_t len, size_t* lines_sz, size_t* lines_malloced) {
    char** _lines = *lines;

    if (*lines_sz == *lines_malloced) {
        *lines_malloced *= 2;
        char** new_lines = (char**)malloc(sizeof(char*) * (*lines_malloced));
        if (new_lines == NULL) {
            perror("Unable to allocate memory");
            return -1;
        }

        for (int i = 0; i < *lines_sz; ++i) {
            *(new_lines + i) = *(_lines + i);
        }
        free(_lines);
        *lines = new_lines;
        _lines = *lines;
    }

    *(_lines + (*lines_sz)) = (char*) malloc(sizeof(char) * strlen(payload));
    strncpy(*(_lines + (*lines_sz)), payload, len);
    (*lines_sz)++;
    return strlen(payload);
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
    char** lines = (char**) malloc(sizeof(char*) * 8);
    size_t lines_malloced = 8;
    size_t lines_sz = 0;

    off_t start = lseek(split->fd, 0, SEEK_CUR);
    char read_buff[split->size - start];

    if ((read(split->fd, read_buff, split->size - start)) < 0) {
        perror("Failed to read fd");
        return -1;
    }

    size_t pos_s = 0;
    for (off_t pos_e = 0; pos_e < split->size - start; ++pos_e) {
        if (read_buff[pos_e] == '\n') {
            char* buf = (char*)malloc((sizeof(char) * pos_e - pos_s) + 2);
            strncpy(buf, read_buff + pos_s, pos_e - pos_s + 1);
            char* needle = strnstr(buf, (char*)split->usr_data, strlen(buf));
            if (needle != NULL) {
                add_to(buf, &lines, strlen(buf), &lines_sz, &lines_malloced);
            }
            free(buf);
            pos_s = pos_e + 1;
        }
    }

    for (int i = 0; i < lines_sz; ++i) {
        if (write(fd_out, *(lines + i), strlen(*(lines + i))) < 0 ) {
            perror("Failed to write to fd");
            return -1;
        }
    }

    for (int i = 0; i < lines_sz; ++i) {
        free(*(lines + i));
    }
    free(lines);
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
int word_finder_reduce(int * p_fd_in, int fd_in_num, int fd_out) {
    char** lines = (char**) malloc(sizeof(char*) * 8);
    size_t lines_malloced = 8;
    size_t lines_sz = 0;

    for (int i = 0; i < fd_in_num; ++i) {
        int fd = *(p_fd_in + i);

        struct stat fd_stat;
        if ((fstat(fd, &fd_stat)) < 0) {
            fprintf(stderr, "[REDUCE fd@%d %d] ", i, fd);
            perror("Failed to stat file");
            return -1;
        }

        char read_buff[fd_stat.st_size];
        if ((read(fd, read_buff, fd_stat.st_size)) < 0) {
            perror("[REDUCE] Failed to read fd");
            return -1;
        }

        size_t pos_s = 0;
        for (size_t pos_e = 0; pos_e < fd_stat.st_size; ++pos_e) {
            if (read_buff[pos_e] == '\n') {
                char buf[pos_e - pos_s + 1];
                strncpy(buf, read_buff + pos_s, pos_e - pos_s + 1);
                add_to(buf, &lines, pos_e - pos_s + 1, &lines_sz, &lines_malloced);
                pos_s = pos_e + 1;
            }
        }

    }
    for (int i = 0; i < lines_sz; ++i) {
        if (write(fd_out, *(lines + i), strlen(*(lines + i))) < 0 ) {
            perror("Failed to write to fd");
            return -1;
        }
    }

    for (int i = 0; i < lines_sz; ++i) {
        free(*(lines + i));
    }
    free(lines);

    return 0;
}

//==================================================================== 80 ====>>