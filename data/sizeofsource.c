#include <stdio.h>
void echo(){
char c = 'c';
char buffer[256];
char buffer2[256];
if(sizeof(buffer) <= 500) {
if(sizeof(buffer) <= 500) {
strcpy(buffer2, buffer);
if(sizeof(buffer) <= 500) {
strcpy(buffer2, buffer);
}
}
}
if(sizeof(buffer2) < 500) {
strcpy(buffer2, buffer);
}
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 8,1;8,23

/// 10,1;10,23

/// 15,1;15,23

