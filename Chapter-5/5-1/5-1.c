#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int next = getch();
        if (!isdigit(next)) {
            ungetch(next);
            ungetch(c);
            return 0;
        }
        c = next;
    }

    int val = 0;
    for (; isdigit(c); c = getch())
        val = 10 * val + (c - '0');
    *pn = sign * val;

    if (c != EOF)
        ungetch(c);

    return c;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

// Test main to demonstrate getint
int main() {
    int n, ret;
    printf("Enter integers (non-integer to stop):\n");
    while ((ret = getint(&n)) != 0) {
        if (ret == EOF)
            break;
        printf("Got integer: %d\n", n);
    }
    printf("Input ended or invalid integer encountered.\n");
    return 0;
}

