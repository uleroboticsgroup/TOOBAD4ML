#include <stdio.h>
void echo(){
char buffer[256];
char buffer2[256];
if(strlen(buffer2) < 500) {
if(strlen(buffer) < 500) {
if(strlen(buffer2) < 500) {
strcpy(buffer, buffer2);
}
}
else{
strcpy(buffer, buffer2);
}
}
else{
gets(buffer);
}
printf("Input given: %s", buffer);
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 8,1;8,23

/// 12,1;12,23

/// 16,1;16,12