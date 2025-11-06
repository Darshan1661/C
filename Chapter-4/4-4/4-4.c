#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number was found
#define MAXVAL 100   // max depth of val stack

int sp = 0;          // next free stack position
double val[MAXVAL];  // value stack

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

void print_top(void) {
    if (sp > 0)
        printf("top element: %.8g\n", val[sp - 1]);
    else
        printf("stack empty\n");
}

void duplicate_top(void) {
    if (sp > 0) {
        double top = val[sp - 1];
        push(top);
    } else {
        printf("stack empty\n");
    }
}

void swap_top(void) {
    if (sp > 1) {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf("not enough elements to swap\n");
    }
}

void clear_stack(void) {
    sp = 0;
}

int getch(void);
void ungetch(int);
int getop(char []);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    printf("Enter expressions, commands:\n");
    printf("(?, d, s, c for print top, duplicate, swap, clear)\n");

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
        case '?': // print top without popping
            print_top();
            break;
        case 'd': // duplicate top element
            duplicate_top();
            break;
        case 's': // swap top two elements
            swap_top();
            break;
        case 'c': // clear stack
            clear_stack();
            break;
        case '\n':
            if (sp > 0)
                printf("\t%.8g\n", val[sp - 1]);
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}

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

int getop(char s[]) {
    int i = 0, c, next;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (c == '-') {
        next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return c;   // minus operator
        } else {
            c = next;
            s[++i] = c;
        }
    }

    if (!isdigit(c) && c != '.')
        return c;       // operator

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

