#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
  char* name;
  char* name2;
  int d = 3;

  strncpy(name, name2, 21);
  strncpy(name, name2, 21 + 2);
  strncpy(name, name2, 21 + sqrt(49));
  strncpy(name, name2, main());
  strncpy(name, name2, d);
  strncpy(name, name2, name[0]);

}
/// ###BEGIN_VULNERABLE_LINES###

/// 10,3;10,26

/// 11,3;11,30

/// 12,3;12,37

/// 13,3;13,30

/// 14,3;14,25

/// 15,3;15,31
