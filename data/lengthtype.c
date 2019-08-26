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
memcpy(buffer, buffer, 2);
memcpy(buffer, buffer, 2+3);
memcpy(buffer, buffer, 2-3);
memcpy(buffer, buffer, 2*3);
memcpy(buffer, buffer, 2/3);
memcpy(buffer, buffer, 2%3);
memcpy(buffer, buffer, da());
memcpy(buffer, buffer, (int) pow(2, 3));
memcpy(buffer, buffer, (int) sqrt(2));
memcpy(buffer, buffer, buffer[2]);
memcpy(buffer, buffer, 2 >> 1);
memcpy(buffer, buffer, 2 << 1);
memcpy(buffer, buffer, 2 + 1 * 3);
}
int main(){
echo();
return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 11,1;11,25

/// 12,1;12,27

/// 13,1;13,27

/// 14,1;14,27

/// 15,1;15,27

/// 16,1;16,27

/// 17,1;17,28

/// 18,1;18,39

/// 19,1;19,37

/// 20,1;20,33

/// 21,1;21,30

/// 22,1;22,30

/// 23,1;23,33

