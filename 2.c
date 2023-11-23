#include <stdio.h>

int main() {
    char buffer[128];
    fgets(buffer, sizeof(buffer), stdin);
    printf("2 received: %s\n", buffer);
    return 0;
}