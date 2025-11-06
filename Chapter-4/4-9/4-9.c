#include <stdio.h>

int buf = -2;  // Buffer: -2 means empty, -1 means EOF, >=0 char pushed back

int getch(void) {
    int c;
    if (buf != -2) {
        c = buf;
        buf = -2;
        return c;
    } else {
        return getchar();
    }
}

void ungetch(int c) {
    if (buf != -2) {
        printf("ungetch error: pushback buffer full\n");
        return;
    }
    buf = c;
}

int main() {
    int c;

    // Example usage: push back EOF and test getch behavior
    ungetch(EOF);
    c = getch();
    if (c == EOF) {
        printf("EOF correctly handled on getch()\n");
    } else {
        printf("Error: expected EOF\n");
    }
    c = getch();
    if (c == EOF) {
        printf("EOF returned from getchar after buffer emptied\n");
    }

    return 0;
}

