#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main () {
	// 2. Number of elements Copied within bounds
	char str3[] = "To be or not to be";
  	char str4[4];
  	strncpy(str4, str3, 4); /*BAD*/ // null terminator
  	puts(str4);

  	char str5[] = "To be or not to be";
  	char str6[4];
  	strncpy(str6, str5, sizeof(str6)); /*BAD*/ // null terminator
  	puts(str6);

	// 3. Array write index within bounds. 
	char array[4] = {'A', 'B', 'C', '\0'};
	array[3] = 'A'; /*BAD*/
	printf("%s\n", array);

	char array1[4] = {"REQ"};
  	array1[3] = 'A'; /*BAD*/
  	printf("%s\n", array1);

	// 4. Format String Precision Within Bounds
	char *str = "QWERYUIOPASDFGHJKLNZXCVBNMQWEQWE";
	char buf[32];
	sprintf(buf, "<%.32s>", str); /*BAD*/

	char *str1 = "QWERYUIOPASDFGHJKLNZXCVBNMQWEQWE";
  	char buf1[32];
  	sprintf(buf1, "<%5.12s>", str1); /*BAD*/
    printf("%s\n", buf1);

	char buffer[7]; 
    char* s = "geeksforgeeks";  
    snprintf(buffer, 6, "%s\n", s); 
    printf("string:\n%s\n", buffer); 

    char str2[4];
   	printf("Enter name: ");
   	scanf("%5s", str2); /*BAD*/
   	printf("Entered Name: %s\n", str2);

   	// 5. Srting Copy within bounds
   	char strr[10]; 
	strcpy(strr,"To be "); /*BAD*/

	//8. Is character case Conversion sink
   	char up = 'a';
   	up = toupper(up);
   	printf("%c\n", up);

}

/// ###BEGIN_VULNERABLE_LINES###

// 2. Number of elements Copied within bounds
/// 9,4;9,25

/// 14,4;14,36

// 3. Array write index within bounds.
/// 19,2;19,13

/// 23,4;23,16

// 4. Format String Precision Within Bounds
/// 29,2;29,29

/// 33,4;33,34

/// 38,5;38,34

/// 43,5;43,22

// 5. String Copy within bounds
/// 48,2;48,22

//8. Is character case Conversion sink
/// 52,5;52,20
