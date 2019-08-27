#include <stdio.h>
struct stru {
    char p[256];
};
union Data {
   int i;
   float f;
   char str[20];
};
void echo(){
char buffer[256];
char* buffer2[256][256];
struct stru nue;
union Data data;
buffer[10] = 'c';
buffer2[257][256] = 'c';
nue.p[8] = 'c';
data.str[0] = 'c';
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 15,1;15,14

/// 16,1;16,21

/// 17,1;17,12

/// 18,1;18,15