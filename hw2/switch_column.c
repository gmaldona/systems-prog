/*
 * CS 551 Homework 2
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2024-07-20
 * web   : https://cs.binghamton.edu/~gmaldonado/
 *
 * Graduate student @ Thomas J. Watson College of Engineering and Applied
 * Sciences, Binghamton University.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

#define EOL   0x0a
#define DELIM 0x20

//==================================================================== 80 ====>>

/**
 * Program spec:
 *
 * The scenario is we have a data file containing multiple rows of contents (rows
 * are  separated  by a  newline  character (\n)). Each  row  contains  multiple
 * records that are  separated by spaces  or tabs. The file does  not contain any
 * holes,  which means  there is no  NULL byte in the  file. You need  to write a
 * program, which switches the two  records in each  row according to the user’s
 * intention,  and appends  the new content  to the  original data file.
 *
 * where path to file specifies  the path to the data file, col_x and col_y are the
 * indices of the two  records (in the same row) that are going to  be switched.
 * Indices of records within each row start  from 1. If the number of records in
 * a row is smaller  than either  col_x  or col_y, then the row  keeps the same.
 *
 * @param col_x
 * @param col_y
 * @return 0 if the columns successfully switched or -1 if failed.
 */
int switch_column(char *path, int col_x, int col_y) {

   int fd;
   if ((fd = open(path, O_RDWR)) < 0) {
      fprintf(stderr, "Failed to open file");
      return -1;
   }

   struct stat fd_stat;
   if (fstat(fd, &fd_stat) < 0) {
      fprintf(stderr, "Failed to retrieve file stat");
      return -1;
   }

   char *src;
   if ((src = (char *)mmap(NULL, fd_stat.st_size, PROT_READ | PROT_WRITE,
                           MAP_SHARED, fd, 0)) == MAP_FAILED) {
      fprintf(stderr, "Failed to map file bytes into memory");
      return -1;
   }

   size_t file_pos = 0;
   size_t col_pos = 0;
   size_t row_st_pos = 0;

   char col_x_buff[64];
   char col_y_buff[64];

   int col_x_pos = 0;
   int col_y_pos = 0;

   while (file_pos <= fd_stat.st_size) {

      if (src[file_pos] == EOL || file_pos == fd_stat.st_size) {

         if (col_x_pos > 0 && col_y_pos > 0) {
            // TODO: MAJOR ASSUMPTION that all cols are equals.
            size_t col_sz = strlen(col_x_buff);

            size_t offset_x = row_st_pos + (col_x * col_sz) + col_x;

            size_t offset_y = row_st_pos + (col_y * col_sz) + col_y;

            memcpy(src + offset_x, col_y_buff, strlen(col_y_buff));
            memcpy(src + offset_y, col_x_buff, strlen(col_x_buff));
         }

         col_pos = 0;
         col_x_pos = 0;
         col_y_pos = 0;
         row_st_pos = file_pos + 1;

      } else if (src[file_pos] == DELIM) {
         ++col_pos;
      } else {
         if (col_pos == col_x) {
            strncpy(col_x_buff + col_x_pos, src + file_pos, sizeof(char));
            ++col_x_pos;
         }
         if (col_pos == col_y) {
            strncpy(col_y_buff + col_y_pos, src + file_pos, sizeof(char));
            ++col_y_pos;
         }
      }

      ++file_pos;
   }

   msync(src, fd_stat.st_size, MS_SYNC);
   if (munmap(src, fd_stat.st_size) < 0) {
      fprintf(stderr, "Failed to unmap memory");
      return -1;
   }

   if (close(fd) < 0) {
      fprintf(stderr, "Failed to close file");
      return -1;
   }

   return 0;
}

int main(int args, char **argv) {

   if (args != 4) {
      fprintf(stdout, "Expected 3 arguments. Provided %d\n", args);
      return -1;
   }

   char *path = argv[1];
   int col_x = atoi(argv[2]);
   int col_y = atoi(argv[3]);

   return switch_column(path, col_x, col_y);
}

//==================================================================== 80 ====>>