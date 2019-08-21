#include <stdio.h>
void echo(){
char c = 'c';
char buffer[256];
char buffer2[256];
if(*buffer == 0) {
if(buffer[0] > 0) {
strcpy(buffer2, buffer);
if(&buffer > 0) {
strcpy(buffer2, buffer);
}
}
buffer2[257] = c;
}
if(*buffer2 > 0) {
strcpy(buffer2, buffer);
}

printf("Input given: %s", buffer);
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 10,1;10,23

/// 8,1;8,23

/// 16,1;16,23

