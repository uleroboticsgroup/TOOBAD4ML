#include <stdio.h>
void echo(){
char c = 'c';
char buffer[256];
char buffer2[256];
if(strlen(buffer2) < 500) {
strcpy(buffer, buffer2);
if(strlen(buffer) < 500) {
strcpy(buffer, buffer2);
if(strlen(buffer) < 500) {
strcpy(buffer, buffer2);
}
}
}
printf("Input given: %s", buffer);
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 7,1;7,23

/// 9,1;9,23

/// 11,1;11,23
