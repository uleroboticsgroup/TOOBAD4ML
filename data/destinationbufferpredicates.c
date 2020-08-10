#include <stdio.h>
#include <stdlib.h>

int main () {
   char *str;
   char da[25];
   str = (char *) malloc(da[2] + 3);
   if(str[11] == '2') {}
   if(strlen(str) == 2) {}
   
   printf("%d", str[1]);
   printf("%d", str[1]);

   gets(da);
   
   str[20] = da[22];
   return(0);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 16,4;16,19