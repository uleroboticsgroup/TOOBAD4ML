#include <stdio.h>
void echo(){
char c = 'c';
char buffer[256];
char buffer2[256];
if(strcmp(buffer2, buffer)) {
strcpy(buffer2, buffer);
if(strncmp(buffer, buffer2, 8)) {
strcpy(buffer2, buffer);
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