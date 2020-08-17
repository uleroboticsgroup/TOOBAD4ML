#include <stdio.h>
#include <stdlib.h>

int main () {
   char str[25];
   char da[25];
   /* Initial memory allocation */
   da[24] = NULL;
   str[24] = NULL;

   str[20] = da[22];
   return(0);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 11,4;11,19