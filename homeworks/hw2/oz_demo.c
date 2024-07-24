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
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

float snapshot(float s_time) {
   return (float)(((float)clock() - s_time) / CLOCKS_PER_SEC * 1000000);
}

//==================================================================== 80 ====>>

int main(void) {
   float gp_time = (float)clock();

   printf("[%f micro-s]\t", snapshot(gp_time));
   printf("Hello, World from grandparent %d!\n", getpid());
   pid_t p_pid;

   if ((p_pid = fork()) < 0) {
      perror("fork parent fail");
      return 1;
   }

   if (p_pid == 0) {
      float p_time = (float)clock();
      pid_t c_pid;
      printf("[%f micro-s]\t", snapshot(p_time));
      printf("Hello, World from parent %d!\n", getpid());
      if ((c_pid = fork()) < 0) {
         perror("fork child fail");
         return 1;
      }

      if (c_pid == 0) {
         float c_time = (float)clock();
         printf("[%f micro-s]\t", snapshot(c_time));
         printf("Hello, World from child %d!\n", getpid());
         while (getppid() != 1) {} // stalling
         printf("[%f micro-s]\t", snapshot(c_time));
         printf("child parent process adopted by init: %d\n", 1);
         printf("[%f micro-s]\t", snapshot(c_time));
         printf("Goodbye, World from child %d!\n", getpid());
      } else {
         sleep(3);
         printf("[%f micro-s]\t", snapshot(p_time));
         printf("Goodbye, World from parent %d!\n", getpid());
      }

   } else {
      sleep(6);
      pid_t wait_ret = wait(NULL);
      printf("[%f micro-s]\t", snapshot(gp_time));
      printf("Grandparent wait return: %d\n", wait_ret);
      printf("[%f micro-s]\t", snapshot(gp_time));
      printf("Goodbye, World from grandparent %d!\n", getpid());
   }

   return 0;
}

//==================================================================== 80 ====>>