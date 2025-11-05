#include <stdio.h>

#define LIM 1000

int main() {
    char s[LIM];
    int i = 0;
    int c;

    while (i < LIM - 1) {
        c = getchar();
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            break;
        }
        s[i] = c;
        ++i;
    }
    s[i] = '\0'; // null terminate string

    printf("Read line: %s\n", s);
    return 0;
}

