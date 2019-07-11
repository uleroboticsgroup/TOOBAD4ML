#include <stdio.h>

int main ()
{
  char str2[50];
  char str1[40];

  strncpy ( str1, str2, sizeof(str2) );
  strncpy ( str2, str1, sizeof(str1) );

  char passwd[20] = {0};
  gets(passwd);

  return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 8,3;8,38

/// 9,3;9,38

/// 12,3;12,14
