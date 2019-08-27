#include <stdio.h>
#include <math.h>
int da() {
    return 1;
}
char* getAddress() {char da[256]; return da;}
void echo(){
char c = 'c';
char buffer[256];
char* buffer2[256][256];
*(buffer) = 'c';
*(buffer + 3) = 'x';
*(buffer - 3) = 'x';
*(buffer + 3 * 3) = 'x';
*(buffer + 3 / 3) = 'x';
*(buffer + 2 % 3) = 'x';
*(buffer + da()) = 'x';
*(getAddress()) = 'x';
*(buffer + buffer[2]) = 'x';
*(buffer + (int) (3 >> 1)) = 'x';
*(buffer + (int) (2 << 1)) = 'x';
*(buffer + (int) pow(2,3)) = 'x';
*(buffer + (int)sqrt(3)) = 'x';
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 11,1;11,13

/// 12,1;12,17

/// 13,1;13,17

/// 14,1;14,21

/// 15,1;15,21

/// 16,1;16,21

/// 17,1;17,20

/// 18,1;18,19

/// 19,1;19,25

/// 20,1;20,30

/// 21,1;21,30

/// 22,1;22,30

/// 23,1;23,28