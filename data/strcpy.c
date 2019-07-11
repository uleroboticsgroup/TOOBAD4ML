#include <stdio.h>

int main() {
  char str1[10];
  char str2[6];
  strcpy(str1,"To be ");
  strcpy(str2,"or not to be");
  char name[5] = "AAAA";
  name[5] = 'A';
}


/// ###BEGIN_VULNERABLE_LINES###

/// 6,3;6,23

/// 7,3;7,29

/// 9,3;9,13
