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
buffer[2] = 'c';
buffer[2 + 3] = 'x';
buffer[2 - 3] = 'x';
buffer[2 * 3] = 'x';
buffer[2 / 3] = 'x';
buffer[2 % 3] = 'x';
buffer[da()] = 'x';
(getAddress())[8] = 'x';
buffer[buffer[2]] = 'x';
(buffer + buffer[2])[2] = 'x';
(buffer2[2])[2] = 'x';
(buffer + 3)[2] = 'x';
(buffer - 3)[2] = 'x';
(buffer)[2 >> 1] = 'x';
(buffer)[2 << 1] = 'x';
(buffer + 3 * 2)[2] = 'x';
buffer[(int)pow(2,3)] = 'x';
buffer[(int)sqrt(3)] = 'x';
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 11,1;11,17

/// 12,1;12,17

/// 13,1;13,17

/// 14,1;14,17

/// 15,1;15,17

/// 16,1;16,17

/// 17,1;17,16

/// 18,1;18,21

/// 19,1;19,21

/// 20,1;20,27

/// 21,1;21,19

/// 22,1;22,19

/// 23,1;23,19

/// 24,1;24,20

/// 25,1;25,20

/// 26,1;26,23

/// 27,1;27,25

/// 28,1;28,24