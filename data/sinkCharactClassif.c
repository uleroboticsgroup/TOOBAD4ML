#include <stdio.h>
#include <string.h>

int main () {

	// 2. Number of elements Copied within bounds
	char str1[10]; 
	strcpy(str1,"To be ");

	// 3. Array write index within bounds. 
	char array[4] = {'A', 'B', 'C',  '\0'};
	array[5] = 'A';
	printf("%s\n", array);

}

/// ###BEGIN_VULNERABLE_LINES###

// 2. Number of elements Copied within bounds
/// 8,2;8,22


// 3. Array write index within bounds.
/// 11,2;11,13