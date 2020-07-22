#include <stdio.h>

struct Coordinate {
   char x[3];
   int y;
   char* strings;
};
union Data {
   int i;
   float f;
   char y[20];
};

int main() {
	struct Coordinate list[256];
    union Data list2[256];
    int a[2][2];
    int b[2];
	struct Coordinate coord; 
    union Data data;

	coord.x[1] = 'c';
	data.y[1] = 'c';
    list[1].x[1] = 'c';
    list2[1].y[1] = 'c';
    a[1][1] = 1;
    b[1] = 1;
    printf("2");
}

/// ###BEGIN_VULNERABLE_LINES###

/// 22,2;22,15

/// 23,2;23,14

/// 24,5;24,20

/// 25,5;25,21

/// 26,5;26,15

/// 27,5;27,12

/// 28,5;28,15