#include <stdio.h>
#include <string.h>

int main () {

	// 2. Number of elements Copied within bounds
	char str3[] = "To be or not to be";
  	char str4[4];
  	strncpy(str4, str3, 4); /*BAD*/ // null terminator
  	puts(str4);

	// 3. Array write index within bounds. 
	char array[4] = {'A', 'B', 'C', '\0'};
	array[3] = 'A'; /*BAD*/
	printf("%s\n", array);

	// 4. Format String Precision Within Bounds
	char *str = "QWERYUIOPASDFGHJKLNZXCVBNMQWEQWE";
	char buf[32];
	sprintf(buf, "<%.32s>", str); /*BAD*/

	char buffer[7]; 
    char* s = "geeksforgeeks";  
    snprintf(buffer, 6, "%s\n", s); 
    printf("string:\n%s\n", buffer); 

    char str2[4];
   	printf("Enter name: ");
   	scanf("%5s", str2); /*BAD*/
   	printf("Entered Name: %s\n", str2);

   	// 5. Srting Copy within bounds
   	char str1[4]; 
	strcpy(str1,"To be "); /*BAD*/

}

/// ###BEGIN_VULNERABLE_LINES###

// 2. Number of elements Copied within bounds
/// 9,4;9,25

// 3. Array write index within bounds.
/// 14,2;14,13

// 4. Format String Precision Within Bounds
/// 20,2;20,29

/// 24,5;24,34

/// 29,5;29,22

// 5. Srting Copy within bounds
/// 34,2;34,22