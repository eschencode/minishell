#include <stdio.h>

int main() {
    char input[100];
    fgets(input, sizeof(input), stdin);
    printf("Received input: %s\n", input);
    return 0;
}
