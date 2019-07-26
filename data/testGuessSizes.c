#include <stdio.h>
int b(int x) {
	return x * 5;
}

int main(int argc) {
	int a = 20*5;
	char x[500];
	char z[a];

	strncpy(z,x, sizeof(52 + 30 +56.2 + sizeof(int)));
}

/// ###BEGIN_VULNERABLE_LINES###

/// 11,2;11,50
