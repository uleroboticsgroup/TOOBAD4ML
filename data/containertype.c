#include <stdio.h>
struct stru {
    char p[256];
};
void echo(){
char buffer[256];
char* buffer2[256][256];
struct stru nue;
buffer[10] = 'c';
buffer2[257][256] = 'c';
nue.p[8] = 'c';
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 9,1;9,14

/// 10,1;10,21

/// 11,1;11,12
