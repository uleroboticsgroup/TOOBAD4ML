#include <stdio.h>
void echo(){
char c = 'c';
char buffer[256];
char buffer2[256];
if(buffer[0] == 'c') {
buffer2[257] = c;
if(c == 'c') {
buffer2[257] = c;
if(c != 'x') {
buffer2[257] = c;
}
}
}
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 7,1;7,16

/// 9,1;9,16

/// 11,1;11,16

