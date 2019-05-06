#include <stdio.h>
#include <string.h>

int main () {

	// 2. Number of elements Copied within bounds
	char str1[10]; 
	strcpy(str1,"To be ");

	// 3. Array write index within bounds. 
	char array[4] = {'A', 'B', 'C', '\0'};
	array[3] = 'A'; /*BAD*/
	printf("%s\n", array);

	// 4. Format String Precision Within Bounds
	char *str = "QWERYUIOPASDFGHJKLNZXCVBNMQWEQWE";
	char buf[32];
	sprintf(buf, "<%.32s>", str); /*BAD*/

}

/// ###BEGIN_VULNERABLE_LINES###

// 2. Number of elements Copied within bounds
/// 8,2;8,22


// 3. Array write index within bounds.
/// 12,2;12,13

// 4. Format String Precision Within Bounds
/// 18,2;18,29