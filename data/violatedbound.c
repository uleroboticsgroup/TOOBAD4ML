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
    strings[-25] = 'x';
    *(x + 270 - 290) = 'x';
    *(x + 25) = 'x';
    *(x - 29) = 'x';
    *(x + 220 + 50) = 'x';
	x[25] = 'c';

}

/// ###BEGIN_VULNERABLE_LINES###

/// 16,2;16,11

/// 17,5;17,20

/// 18,5;18,24  

/// 19,5;19,17

/// 20,5;20,17

/// 21,5;21,23

/// 22,2;22,10