#include <stdio.h>

struct d {
  char buffer[500];
};

int main() {
  char name[5] = "AAAA";
  if (name[0] == 'A') {
    name[0] = 'C';
    if (name[1] == 'B') {
      name[1] = 'X';
    }
    else {
      name[2] = 'U';
    }
  }
  else {
    name[0] = 'X';
  }

  name[4] = 'A';
  name[5] = 'A';

  char buffer[50];
	gets(buffer);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 6,5;6,15

/// 11,7;11,17

/// 15,5;15,15
