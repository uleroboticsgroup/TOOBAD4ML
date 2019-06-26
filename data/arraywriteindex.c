#include <stdio.h>

int main() {
  char name[5] = "AAAA";
  name[4] = 'A';
  name[5] = 'A';

  char buffer[50];
	gets(buffer);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 5,3;5,13

/// 6,3;6,13

/// 9,2;9,13