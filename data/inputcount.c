#include <stdio.h>

int main ()
{
  char str2[50];
  char str1[40];


  str1[2] = 'd';
  scanf("%d", &str1);
  *(str1 + 2) = 'd';
  str2[1] = 'd';
  str2[1] = 'd';

  str2[60] = str1[1];

  return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 15,3;15,20
