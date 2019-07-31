#include <stdio.h>
int b(int x) {
	return x * 5;
}

int main(int argc) {
	int a = 20*5;
	char x[256];
	char z[a];

	strncpy(x,z, 256);
}

/// ###BEGIN_VULNERABLE_LINES###

/// 11,2;11,18
