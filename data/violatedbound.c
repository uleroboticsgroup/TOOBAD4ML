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
	x[256] = 'c';
    strings[123] = 'x';
}

/// ###BEGIN_VULNERABLE_LINES###

/// 16,2;16,11