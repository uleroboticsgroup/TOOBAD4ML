#include <stdio.h>
void echo(){
char buffer[256];
printf("Type your input:");
gets(buffer);
char str1[10];
char str2[6];
strncat(str1, str2, 6);
printf("Input given: %s", buffer);
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 5,1;5,12