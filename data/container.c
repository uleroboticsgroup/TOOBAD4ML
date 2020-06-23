#include <stdio.h>

struct Coordinate {
   int x;
   int y;
   char* strings;
};

int main(int argc) {
	char x[256];
    char* s;
    int i;
	struct Coordinate coord; 
	
	char* strings = coord.strings;
	strings[1] = 'c';
}

/// ###BEGIN_VULNERABLE_LINES###

/// 14,2;14,12