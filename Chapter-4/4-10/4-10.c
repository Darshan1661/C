#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 1000
#define MAXOP 100
#define NUMBER '0'

int sp = 0;
double val[100];
double variables[26];
double last_printed = 0.0;
int var_assign = -1;

void push(double f) {
    if (sp < 100)
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

void mathfunc(char s[]) {
    double op2;
    if (strcmp(s, "sin") == 0)
        push(sin(pop()));
    else if (strcmp(s, "exp") == 0)
        push(exp(pop()));
    else if (strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    } else
        printf("error: %s not supported\n", s);
}

int getop(char *line, int *index, char s[]) {
    int i = 0;
    int c;

    // Skip whitespace
    while (line[*index] == ' ' || line[*index] == '\t') {
        (*index)++;
    }

    c = line[*index];
    if (c == '\0')  // end of line
        return EOF;

    s[i++] = c;
    s[i] = '\0';
    (*index)++;

    if (!isdigit(c) && c != '.' && c != '-' && !isalpha(c)) // operator
        return c;

    if (isalpha(c)) {
        // collect function name or variable
        while (isalpha(line[*index])) {
            s[i++] = line[*index];
            (*index)++;
        }
        s[i] = '\0';
        return s[0];
    }

    if (c == '-' && !isdigit(line[*index]) && line[*index] != '.') // minus operator
        return c;

    // collect number (integer and fraction)
    while (isdigit(line[*index])) {
        s[i++] = line[*index];
        (*index)++;
    }

    if (line[*index] == '.') {
        s[i++] = line[*index];
        (*index)++;
        while (isdigit(line[*index])) {
            s[i++] = line[*index];
            (*index)++;
        }
    }

    s[i] = '\0';
    return NUMBER;
}

int main() {
    char line[MAXLINE];
    char s[MAXOP];
    int type, idx;
    double op2;
    int var_index;

    printf("Reverse Polish Calculator (type 'q' to quit):\n");

    while (fgets(line, MAXLINE, stdin) != NULL) {
        idx = 0;
        while ((type = getop(line, &idx, s)) != EOF) {
            if (type == NUMBER) {
                push(atof(s));
            } else if (islower(type)) {
                var_index = type - 'a';
                if (var_assign == -1) {
                    push(variables[var_index]);
                } else {
                    variables[var_assign] = pop();
                    var_assign = -1;
                }
            } else {
                switch (type) {
                    case '=':
                        var_assign = (int)pop();
                        if (!islower(var_assign)) {
                            printf("error: invalid variable name\n");
                            var_assign = -1;
                        } else {
                            var_assign -= 'a';
                        }
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
                    case '\n':
                        break;
                    case 'q':
                        return 0;
                    default:
                        if (isalpha(type))
                            mathfunc(s);
                        else
                            printf("error: unknown command %s\n", s);
                        break;
                }
            }
        }
        if (sp > 0) {
            last_printed = pop();
            printf("\t%.8g\n", last_printed);
            push(last_printed);
        }
    }
    return 0;
}

