#include <stdio.h>
#include <ctype.h>

int main(void)
{
  char* array;
  array = toupper(array);
  
  char* array2;
  array2 = array;

  char* array3;
  gets(array3);
  return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 7,3;7,24

/// 10,3;10,12

/// 13,3;13,14