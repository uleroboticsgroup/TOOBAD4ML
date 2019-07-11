#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int main() {
    char cwd[50];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

/// ###BEGIN_VULNERABLE_LINES###

/// 10,9;10,32
 