#include <stdio.h>
#include <stdlib.h>

int main () {
   char *str;
   char da[25];
   str = (char *) malloc(da[2] + 3);
   if(da[11] == '2') {}
   if(strlen(da) == 2) {}
   
   printf("%d", da[1]);
   printf("%d", str[1]);



   str[20] = da[22];
   return(0);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 16,4;16,19