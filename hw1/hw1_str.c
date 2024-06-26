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

#include <ctype.h>

#include "hw1.h"

//==================================================================== 80 ====>>
int str_manip(char * str, char * substr) {
   // Your function should be able to handle erroneous input arguments.
   if (str == NULL || substr == NULL) {
      printf("[ERROR] The string or substring is NULL. Both need to be non-null");
      return -1;
   }
   
   size_t str_len    = strlen(str);
   size_t substr_len = strlen(substr);
   
   if (str_len < substr_len) {
      printf("[ERROR] The length of the substring is greater than the string length.\n");
      return 1;
   } 
   
   // It first prints out the str provided;
   printf("str %s\n", str);

   char * _str = (char*) malloc(sizeof(char) * str_len + 1);
   for (size_t i = 0; i < str_len; i++) {
      _str[i] = (char) tolower(str[i]);
   }

   // Then it prints out a new string that is a combination of str and the
   // reversed str, with all the upper case letters converted to lower case 
   // letters.
   size_t newStr_len = str_len * 2 + 1;
   char* newStr      = (char*) malloc(sizeof(char) * newStr_len);
   strncpy(newStr, _str, str_len);

   size_t j = 0;
   for (size_t i = str_len - 1; i >= 0 && i <= newStr_len; i--) {
      newStr[str_len + j] = _str[i];
      j++;
   }
   printf("newstr %s\n", newStr);

   // Then it prints out the substr provided
   printf("substr %s\n", substr);

   char* _substr = (char *) malloc(sizeof(char) * substr_len + 1);
   for (size_t i = 0; i < substr_len; i++) {
      _substr[i] = (char) tolower(substr[i]);
   }
   
   // Finally your function should print out the number of occurrences of substr
   // (ignoring cases) in the new string printed out. The occurrences should be 
   // counted overlapped, e.g., the number of occurrences of ”aba” in ”ababa” 
   // should be 2. Remember to handle empty string properly.
   size_t matches = 0;
   for (size_t i = 0; i < newStr_len; i++) {
      if (i < newStr_len - substr_len) {
         char* newStr_comp = (char*) malloc(sizeof(char) * substr_len);
         strncpy(newStr_comp, newStr + i, substr_len);
         if (strcmp(newStr_comp, _substr) == 0) { matches++; }
         free(newStr_comp);
      } else { break; }
   }
   printf("occurences %zu\n", matches);

   // Your function should return 0 upon success, and -1 if the operations fail
   // (in this case, the error message should be output to the screen).
   return 0;
}

/*  >>>>>>>> TEST <<<<<<<< */
// int main(void) {
//    str_manip("aBcAbc@defCba", "ABC");
//    return 0;
// }

//==================================================================== 80 ====>>
