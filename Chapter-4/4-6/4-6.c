#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100

int sp = 0;          // next free stack position
double val[MAXVAL];  // value stack
double variables[26]; // variables 'a' to 'z'
double last_printed = 0.0;  // variable for most recently printed value
int var_assign = -1; // variable to assign to, -1 means no assignment pending

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

int getch(void);
void ungetch(int);
int getop(char []);

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

int main() {
    int type;
    double op2;
    char s[MAXOP];
    int var_index;

    printf("Enter expressions with variables (a-z), assignment (=), and commands:\n");

    while ((type = getop(s)) != EOF) {
        if (type == NUMBER) {
            push(atof(s));
        } else if (islower(type)) {  // Variable or variable assignment
            var_index = type - 'a';
            if (var_assign == -1) {
                // Push value of variable onto stack
                push(variables[var_index]);
            } else {
                // Assign top value to variable
                variables[var_assign] = pop();
                var_assign = -1;
            }
        } else {
            switch (type) {
                case '=':
                    var_assign = pop(); // Pop variable identifier (ASCII)
                    if (!islower((int)var_assign)) {
                        printf("error: invalid variable name\n");
                        var_assign = -1;
                    } else {
                        var_assign -= 'a'; // convert to index
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
                    } else
                        printf("error: zero divisor for modulus\n");
                    break;
                case '\n':
                    if (sp > 0) {
                        last_printed = pop();
                        printf("\t%.8g\n", last_printed);
                        push(last_printed);
                    }
                    break;
                default:
                    if (isalpha(type))
                        mathfunc(s);
                    else
                        printf("error: unknown command %s\n", s);
                    break;
            }
        }
    }
    return 0;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp < BUFSIZE)
        buf[bufp++] = (char)c;
    else
        printf("ungetch: too many characters\n");
}

int getop(char s[]) {
    int i = 0, c, next;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (isalpha(c)) {
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return s[0];  // Return first letter for variable or function name
    }

    if (c == '-') {
        next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return c;  // minus operator
        } else {
            c = next;
            s[++i] = c;
        }
    }

    if (!isdigit(c) && c != '.')
        return c;

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

