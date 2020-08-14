#include <stdio.h>
#include <stdlib.h>

int main () {
   char *str;
   char da[25];
   FILE *fp;

   str = (char *) malloc(da[2] + 3);
   
   fgets(da, 60, fp);
   memcpy(da, str, 60);



   str[20] = da[22];

   return(0);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 16,4;16,19