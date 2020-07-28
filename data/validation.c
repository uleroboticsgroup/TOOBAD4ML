#include <stdio.h>
#include <stdlib.h>

int main () {
   char *str;
   char da[25];
   /* Initial memory allocation */
//   str = (char *) malloc(*(da));
//   str = (char *) malloc(15);
//   str = (char *) malloc(*(da + 3));
//   str = (char *) malloc(str[2]);
   str = (char *) malloc(da[2] + 3);
   
   if(str[11] == '2') {}
   if(strlen(str) == 2) {}
   str[20] = da[22];
   return(0);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 16,4;16,19