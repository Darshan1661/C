#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(float *pf) {
    int c, sign;
    float val, power;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            ungetch(c);
            return 0;
        }
        c = next;
    }

    val = 0.0f;
    for (; isdigit(c); c = getch())
        val = 10.0f * val + (c - '0');

    if (c == '.') {
        c = getch();
        power = 1.0f;
        for (; isdigit(c); c = getch()) {
            val = 10.0f * val + (c - '0');
            power *= 10.0f;
        }
        val = val / power;
    }

    *pf = sign * val;

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

int main() {
    float num;
    int ret;

    printf("Enter floating point numbers (non-number to stop):\n");
    while ((ret = getfloat(&num)) != 0) {
        if (ret == EOF)
            break;
        printf("Got number: %f\n", num);
    }
    printf("Input complete or invalid input encountered.\n");
    return 0;
}

