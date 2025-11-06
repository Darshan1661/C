#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>  

int getch(void);
void ungetch(int);

int getop(char []);
void push(double);
double pop(void);

#define MAXOP 100  // max size of operand or operator
#define NUMBER '0' // signal that a number was found

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0) {
                int i2 = (int)op2;
                int i1 = (int)pop();
                push(i1 % i2);
            } else {
                printf("error: zero divisor for modulus\n");
            }
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

// Implement stack operations here
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full\n");
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// getop: get next operator or numeric operand, supports negative numbers
int getop(char s[]) {
    int i = 0, c;

    // Skip spaces
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    // Handle negative numbers
    if (c == '-') {
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return c; // minus operator
        }
        c = next;
        s[++i] = c;
    }

    if (!isdigit(c) && c != '.')
        return c; // operator

    // Collect integer part
    while (isdigit(s[++i] = c = getch()))
        ;

    // Collect fraction part
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

// Buffer for ungetch
char buf = 0;

int getch(void) {
    int c;
    if (buf != 0) {
        c = buf;
        buf = 0;
        return c;
    }
    return getchar();
}

void ungetch(int c) {
    buf = c;
}

