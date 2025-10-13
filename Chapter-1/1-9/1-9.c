#include <stdio.h>

int main() {
    int c, lastWasBlank = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!lastWasBlank) {
                putchar(c);
                lastWasBlank = 1;
            }
        } else {
            putchar(c);
            lastWasBlank = 0;
        }
    }
    return 0;
}

