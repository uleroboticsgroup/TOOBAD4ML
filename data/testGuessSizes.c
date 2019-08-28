#include <stdio.h>
int b(int x) {
	return x * 5;
}

int main(int argc) {
	int a = 20*5;
	char x[256];
	int z[a];

	x[257] = 'x';
	z[285] = ++a;
	z[285] = 2;
	if (z[0] < x[1]) {
		printf("yes");
	}
}

/// ###BEGIN_VULNERABLE_LINES###

/// 11,2;11,11

/// 12,2;12,13

/// 13,2;13,11

/// 14,6;14,16
