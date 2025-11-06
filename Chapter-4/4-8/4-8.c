#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int buf = 0;  // single-character pushback buffer (0 means empty)

int getch(void) {
    int c;
    if (buf != 0) {
        c = buf;
        buf = 0;
        return c;
    } else {
        return getchar();
    }
}

void ungetch(int c) {
    if (buf != 0) {
        printf("ungetch error: pushback buffer full\n");
        exit(1);
    }
    buf = c;
}

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]) {
    int i = 0, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-') 
        return c;  // operator or command

    if (c == '-') {
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return c;  // minus operator
        } else {
            c = next;
            s[++i] = c;
        }
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

// A simple main to demonstrate getop usage and pushback
int main() {
    char s[MAXOP];
    int type;

    printf("Enter input to test getop (Ctrl+D to end):\n");

    while ((type = getop(s)) != EOF) {
        if (type == NUMBER)
            printf("Number: %s\n", s);
        else
            printf("Operator or command: %c\n", type);
    }

    return 0;
}

