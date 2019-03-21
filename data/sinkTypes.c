#include <stdio.h>
#include <string.h>

#define PASSLEN 8
#define SIZE_OK(x) ((x) < (7) ? (1) : (0))
#define ALIAS 0
#define MAX 15

struct Persons{
  char name[40];
  int age;
};


int main() {

 
  // 1. String copy
  char str1[200];
  char str2[200];
  strcpy(str1,"To be ");
  strcpy(str2,"or not to be");
  strncpy(str2, str1, sizeof(str2));

  // 2. String concatenation
  strcat(str1, str2);
  strncat(str1, str2, 6);

  puts(str1);
  puts(str2);

  // 3. Memory alteration
  struct Persons person;
  char myname[] = "Pierre de Fermat";
  memcpy(person.name, myname, strlen(myname)+1);
  person.age = 46;
  printf("person_copy: %s, %d \n", person.name, person.age);

  char dest[] = "oldstring";
  const char src[]  = "newstring";
  printf("Before memmove dest = %s, src = %s\n", dest, src);
  memmove(dest, src, 9);
  printf("After memmove dest = %s, src = %s\n", dest, src);

  // 4. Formatted string output
  char buffer[50]; 
  int a = 10, b = 20, c; 
  c = a + b; 
  sprintf(buffer, "Sum of %d and %d is %d", a, b, c); 
  printf("%s", buffer); 

  char buffer2[50]; 
  char* bu = "geeksforgeeks";  
  int j = snprintf(buffer2, 6, "%s\n", bu); 
  printf("string:\n%s\ncharacter count = %d\n", buffer2, j); 

  // 5. Unformatted string input 
  char passwd[PASSLEN] = {0};
  gets(passwd);

  char buf[MAX]; 
  fgets(buf, MAX, stdin); 

  // 6. Formatted string input
  scanf("%s", passwd);
  puts(passwd);

  int day, year;
  char weekday[20], month[20], dtm[100];
  strcpy( dtm, "Saturday March 25 1989" );
  sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );
  printf("%s %d, %d = %s\n", month, day, year, weekday );

  // 7. Array element writes
  char *ch;
  *ch = ';';

/// ###BEGIN_VULNERABLE_LINES###

// strcpy
/// 21,3;21,23

// strncpy
/// 23,3;23,35

// strcat
/// 26,3;26,20

// strncat
/// 27,3;27,24

// memcpy
/// 35,3;35,47

// memmove
/// 42,3;42,23

// sprintf
/// 49,3;49,52

// snprintf
/// 54,3;54,43

// gets
/// 59,3;59,14

// fgets
/// 62,3;62,24

// scanf
/// 65,3;65,21

// sscanf
/// 71,3;71,60

// Array writes
/// 76,3;76,9

}



