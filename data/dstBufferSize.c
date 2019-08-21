#include <stdio.h>
void echo(){
char c = 'c';
char buffer[256];
char buffer2[256];
if(sizeof(buffer) - 3 >= strlen(buffer)) {
if(strlen(buffer2) < 500) {
if(strlen(buffer2) < 500) {
strcpy(buffer, buffer2);
}
}
else{
strcpy(buffer, buffer2);
}
buffer2[257] = c;
}
else{
strcpy(buffer, buffer2);
}
printf("Input given: %s", buffer);
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 9,1;9,23

/// 13,1;13,23

/// 15,1;15,16

/// 18,1;18,23

