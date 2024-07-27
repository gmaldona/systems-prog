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
#include <sys/time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include "mapreduce.h"
#include "common.h"

//==================================================================== 80 ====>>

char DELIMITERS[] = {0x09, 0x0a, 0x32};

/**
 * Finds the end index of a buffer partition.
 *
 * @param _src
 * @param start The starting position of the partition.
 * @param size  The approximate partition size.
 * @return  The end index of the partition slice.
 */
size_t partition(char* src, size_t start, size_t size, size_t LIMIT, bool last) {

    if (last || start + size >= LIMIT) {
        return LIMIT;
    }

    size_t pos = start + size;

    while (pos < LIMIT) {
        if (*(src + pos) == ' ') {
            return pos - 1;
        }
        ++pos;
    }

    return pos;
}

void mapreduce(MAPREDUCE_SPEC * spec, MAPREDUCE_RESULT * result)
{
    DATA_SPLIT*   partitions[spec->split_num];
    size_t partition_indices[spec->split_num]; // inclusive (0, partition_chunk)
    pid_t     partition_pids[spec->split_num];
    int       partition_fout[spec->split_num];

    int fd;
    if ((fd = open(spec->input_data_filepath, O_RDONLY)) < 0) {
        perror("Failed to open file");
        return;
    }

    struct stat fd_stat;
    if ((fstat(fd, &fd_stat)) < 0) {
        perror("Failed to open file");
        return;
    }

    char *src;
    if ((src = (char *)mmap(NULL, fd_stat.st_size, PROT_READ,
                            MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("Failed to map file bytes into memory");
        return;
    }

    size_t pos = 0;
    for (int i = 0; i < spec->split_num; ++i) {
        partitions[i] = mmap(NULL, sizeof(DATA_SPLIT),
                             PROT_READ  | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS, -1, 0);

        if ((partitions[i]->fd = open(spec->input_data_filepath, O_RDONLY)) < 0) {
            printf("[fd %d] ", i);
            perror("Failed to open fd");
        }
        lseek(partitions[i]->fd, pos, SEEK_SET);

        size_t index;
        if (i < spec->split_num - 1) {
            index = partition(src, pos,
                              fd_stat.st_size / spec->split_num,
                              fd_stat.st_size, false);
        } else {
            index = partition(src, pos,
                              fd_stat.st_size / spec->split_num,
                              fd_stat.st_size, true);
        }

        partition_indices[i] = index; // inclusive.
        partitions[i]->size = index;
        pos = index + 1;
    }

    if (munmap(src, fd_stat.st_size) < 0) {
        perror("Failed to unmap memory");
        return;
    }

    if (close(fd) < 0) {
        perror("Failed to close file");
        return;
    }

    struct timeval start, end;

    if (NULL == spec || NULL == result) {
        EXIT_ERROR(ERROR, "NULL pointer!\n");
    }
    
    gettimeofday(&start, NULL);

    // https://stackoverflow.com/questions/876605/multiple-child-process
    for (int i = 0; i < spec->split_num; ++i) {
        if ((partition_pids[i] = fork()) < 0) {
            perror("Failed to fork process");
            return;
        } else if (partition_pids[i] == 0) {
            // worker
            char itm_file[32];
            sprintf(itm_file, "partition-%d.itm", i);
            partition_fout[i] = open(itm_file, O_WRONLY |
                                              O_CREAT  | O_TRUNC, 0644);
            spec->map_func(partitions[i], partition_fout[i]);
            exit(0);
        }
    }

    // wait for all children processes to finish
    int status, waiting_on = spec->split_num;
    pid_t child;
    while (waiting_on > 0) {
       child = wait(&status);
       fprintf(stderr, "[DEBUG] child process %d finished\n", child);
        --waiting_on;
    }

    gettimeofday(&end, NULL);   

    result->processing_time = ( end.tv_sec -  start.tv_sec) * US_PER_SEC +
                              (end.tv_usec - start.tv_usec);

    for (int i = 0; i < spec->split_num; ++i) {
        if (munmap(partitions[i], sizeof(DATA_SPLIT))) {
            perror("Failed to unmap memory for DATA_SPLIT");
        }
    }
}

//==================================================================== 80 ====>>
