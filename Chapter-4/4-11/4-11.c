#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int getop(char s[]) {
    int i = 0;
    static int buf = 0;  // buffer for one pushed-back char
    int c;

    if (buf != 0) {
        c = buf;
        buf = 0;
    } else {
        c = getchar();
    }

    while (c == ' ' || c == '\t')
        c = getchar();

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-') {
        return c;  // operator or command
    }

    if (c == '-') {
        int next = getchar();
        if (!isdigit(next) && next != '.') {
            buf = next;
            return c;  // minus operator
        }
        c = next;
        s[++i] = c;
    }

    while (isdigit(s[++i] = c = getchar()))
        ;

    if (c == '.')
        while (isdigit(s[++i] = c = getchar()))
            ;

    s[i] = '\0';

    if (c != EOF)
        buf = c;

    return '0';  // signal number found
}

int main() {
    char s[100];
    int type;

    printf("Enter tokens, EOF (Ctrl+D) to end:\n");
    while ((type = getop(s)) != EOF) {
        if (type == '0') {
            printf("Number: %s\n", s);
        } else {
            printf("Operator or command: %c\n", type);
        }
    }
    return 0;
}

