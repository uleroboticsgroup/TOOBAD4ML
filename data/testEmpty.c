#include <stdio.h>
void echo(){
char buffer[256];
printf("Type your input:");
gets("%s", buffer);
printf("Input given: %s", buffer);
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###
 