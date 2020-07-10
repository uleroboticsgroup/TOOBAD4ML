#include <stdio.h>
#include <math.h>

int main() {
  char name[5] = "AAAA";
  int d = 3;

  name[4] = 'A';
  name[main()] = 'A';
  name[name[0]] = 'A';
  name[1 + 2] = 'A';
  name[(int)(23 + 23 +sqrt(49.0)) + 23] = 'A';
  name[d] = 'A';

  char buffer[50];
	gets(buffer);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 8,3;8,13

/// 9,3;9,18

/// 10,3;10,19

/// 11,3;11,17

/// 12,3;12,43

/// 13,3;13,13
