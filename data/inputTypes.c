#include <stdio.h>
#include <string.h>

int main() {


	char buffer[50];

  /*  BAD  */
	gets(buffer);

	if ( gets(buffer) != NULL) {
		gets(buffer);
	}

}


/// ###BEGIN_VULNERABLE_LINES###

/// 10,2;10,13
