/*
 * Homework Assignment #1
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2024-06-24
 * web   : https://cs.binghamton.edu/~gmaldonado/
 *
 * Graduate student @ Thomas J. Watson College of Engineering and Applied
 * Sciences, Binghamton University.
 */

#include <stdarg.h>

#include "hw1.h"

//==================================================================== 80 ====>>

void myprintf(const char * format, ...) {
   size_t fmt_len = strlen(format);
   size_t args    = 0;
   char arg_types[fmt_len]; 
   
   for (size_t i = 0; i < fmt_len; i++) {
      if (format[i] == '%' && i < fmt_len - 1) {
         arg_types[args] = format[i + 1];
         args++;
      } 
   }

   va_list argv;
   va_start(argv, format);
   // https://stackoverflow.com/questions/36881533
   // It first prints user message as a normal printf function would do.
   vprintf(format, argv);
   printf("Argument list:\n");
   for (size_t i = 0; i < args; i++) {
      char type_str = arg_types[i];
      switch (type_str) {
         case 'c': // compiler warning for having   vvv    char?? 
            printf("Char --> %c\n",    va_arg(argv, int));
            break;
         case 'd':
            printf("Integer --> %d\n", va_arg(argv, int));
            break;
         case 's':
            printf("String --> %s\n",  va_arg(argv, char*));
            break;
      }
   }

   // Then it analyzes the user provided variable argument list, and prints them
   // out. Your function only needs to parse the print types of char (%c), 
   // int (%d), and string (%s).
   va_end(argv);
}

/*  >>>>>>>> TEST <<<<<<<< */

// int main(void) {
//    myprintf("This is CS%c%d%s", '-', 551, " Systems Programming.\n");
//    return 0;
// }

//==================================================================== 80 ====>>