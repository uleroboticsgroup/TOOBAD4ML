#include <stdio.h>
#include <string.h>

#define PASSLEN 8
#define SIZE_OK(x) ((x) < (7) ? (1) : (0))
#define ALIAS 0
#define MAX 15

struct Persons{
  char name[2];
  int age;
};


int main() {

 
  // 1. String copy
  char str1[10];
  char str2[6];
  strcpy(str1,"To be ");
  strcpy(str2,"or not to be");
  strncpy(str2, str1, 10);

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
  int a = 10, b = 20, c = 25; 
  sprintf(buffer, "Sum of %d and %d is %d", a, b, c); 
  printf("%s", buffer); 

  char buffer12[50]; 
  char a2[] = "300"; int b2 = 20, c2 = 320; 
  sprintf(buffer12, "Sum of %2.3s and %d is %d", a2, b2, c2); 
  printf("%s", buffer12); 

  char buffer2[11]; 
  char* cadena = "geeksforgeeks";  
  int j = snprintf(buffer2, 6, "%s\n", cadena); 
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
  char name[5] = "AAAA";
  name[5] = 'A';

/// ###BEGIN_VULNERABLE_LINES###

// strcpy
/// 21,3;21,23

// strncpy
/// 23,3;23,25

// strcat
/// 26,3;26,20

// strncat
/// 27,3;27,24

// memcpy
/// 35,3;35,47

// memmove
/// 42,3;42,23

// sprintf
/// 48,3;48,52

// sprintf
/// 53,3;53,60

// snprintf
/// 58,11;58,46

// gets
/// 63,3;63,14

// fgets
/// 66,3;66,24

// scanf
/// 69,3;69,21

// sscanf
/// 75,3;75,60

// Array writes
/// 80,3;80,13

// total 14 sinks

}

/// 51,1;51,7

/// 51,1;51,7

/// 51,1;51,7

/// 51,1;51,7

/// 51,1;51,7

/// 51,1;51,7

/// 51,1;51,7

