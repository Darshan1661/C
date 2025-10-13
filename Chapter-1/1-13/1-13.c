#include <stdio.h>

#define MAXLEN 20

int main() {
    int c, length = 0;
    int wordlen[MAXLEN] = {0};

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (length > 0 && length < MAXLEN)
                ++wordlen[length];
            length = 0;
        } else {
            ++length;
        }
    }

    for (int i = 1; i < MAXLEN; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < wordlen[i]; j++)
            putchar('*');
        putchar('\n');
    }
    return 0;
}

