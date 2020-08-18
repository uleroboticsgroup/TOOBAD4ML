#include <stdio.h>
int b(int x) {
	return x * 5;
}

int main(int argc) {
	char x[256];
    char* s;
    int i;
    s = *(x);
	
	x[3] = 2;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 12,2;12,9