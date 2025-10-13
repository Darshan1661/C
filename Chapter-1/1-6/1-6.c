#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        printf("Value: %d\n", (c != EOF));
    }
    printf("EOF reached, expression gives: %d\n", (c != EOF));
    return 0;
}

