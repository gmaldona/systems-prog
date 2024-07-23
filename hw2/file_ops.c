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
#include <fcntl.h>
#include <dirent.h>
#include <libc.h>
#include <unistd.h>

//==================================================================== 80 ====>>

/** Return number of sym-links in specified directory dir. */
int count_sym_links(const char *d) {
   DIR *dir = opendir(d);
   int count = 0;
   for (struct dirent *dP = readdir(dir); dP; dP = readdir(dir)) {
      const char *name = dP->d_name;

      struct stat *statP;
      char dir_name[strlen(dir) + 1 + strlen(name)];
      sprintf("%s/%s", dir, name);
      stat(dir_name, statP);
      if (S_ISLNK(statP->st_mode))
         count++;
   }
   return count;
}

int main() {

   int fd1;
   if ((fd1 = open("x.dat", O_WRONLY | O_CREAT)) < 0) {
      printf("fd1=%d", fd1);
      return 1;
   }

   int fd2;
   // if ((fd2 = open("x.dat", O_WRONLY|O_CREAT)) < 0) {
   if (dup2(fd1, fd2) < 0) {
      printf("fd2=%d2", fd2);
      return 1;
   }

   char buff[1];
   buff[0] = 'A';
   ssize_t bytes;

   for (int i = 0; i < 6; ++i) {
      if ((bytes = write(fd1, buff, sizeof(char))) < 0) {
         return 1;
      }
   }

   char buff2[1];
   buff2[0] = 'B';
   ssize_t bytes2;

   for (int i = 0; i < 3; ++i) {
      if ((bytes2 = write(fd2, buff2, sizeof(char))) < 0) {
         return 1;
      }
   }

   fprintf(stderr, "%d\n", close(fd1));
   fprintf(stderr, "%d\n", close(fd2));
}

//==================================================================== 80 ====>>