#include <stdio.h>
void echo(){
char c = 'c';
char buffer[256];
char buffer2[256];
if(strchr(buffer2, 'c')) {
strcpy(buffer2, buffer);
if(strpbrk(buffer, buffer2)) {
strcpy(buffer2, buffer);
if(memchar(buffer, 'c', 6)) {
strcpy(buffer2, buffer);
}
}
}
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 7,1;7,23

/// 9,1;9,23

/// 11,1;11,23

