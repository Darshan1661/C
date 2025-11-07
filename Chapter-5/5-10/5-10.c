#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXVAL 100   // max depth of val stack

int sp = 0;          // next free stack position
double val[MAXVAL];  // value stack

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        fprintf(stderr, "error: stack full, cannot push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        fprintf(stderr, "error: stack empty\n");
        return 0.0;
    }
}

int main(int argc, char *argv[]) {
    double op2;

    if (argc < 2) {
        printf("Usage: %s operand1 operand2 operator ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];

        if (isdigit(arg[0]) || 
            (arg[0] == '-' && isdigit(arg[1]))) {  // number (including negative)
            push(atof(arg));
        } else if (strlen(arg) == 1) {
            switch (arg[0]) {
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
                    else {
                        fprintf(stderr, "error: zero divisor\n");
                        return 1;
                    }
                    break;
                default:
                    fprintf(stderr, "error: unknown operator %s\n", arg);
                    return 1;
            }
        } else {
            fprintf(stderr, "error: invalid argument %s\n", arg);
            return 1;
        }
    }

    if (sp == 1) {
        printf("Result: %g\n", pop());
        return 0;
    } else {
        fprintf(stderr, "error: invalid expression\n");
        return 1;
    }
}

