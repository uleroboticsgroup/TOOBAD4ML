#include <stdio.h>
int b(int x) {
	return x * 5;
}

int main(int argc) {
	char x[256];
    char* s;
    int i;

	x[257] = 'x';
	s = *(x);
	i = printf("%d", x[2]);
	i = printf("%d", 2);
    x[2] = gets(s);
    gets(s);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 11,2;11,11

/// 12,2;12,9

/// 13,2;13,23

/// 14,2;14,20

/// 15,5;15,18

/// 16,5;16,11