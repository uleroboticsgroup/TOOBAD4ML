#include <stdio.h>
#include <stdlib.h>


int main () {
   char str1[10], str2[10], str3[10];
   int year;
   FILE * fp;

   fp = fopen ("file.txt", "w+");   
   fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);
   fclose(fp);
   
   return(0);
}


/// ###BEGIN_VULNERABLE_LINES###

/// 10,9;10,32
 