#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS };

int gettoken(void);

int tokentype;         /* type of last token */
char token[1000];  /* last token string */
char out[1000];        /* output string */

int main() {
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
            }
            else if (type == '*') {
                int need_parens = 0;
                if (strstr(out, "function") || strstr(out, "array"))
                    need_parens = 1;
                if (need_parens)
                    snprintf(temp, sizeof(temp), "(*%s)", out);
                else
                    snprintf(temp, sizeof(temp), "*%s", out);
                strcpy(out, temp);
            }
            else if (type == NAME) {
                snprintf(temp, sizeof(temp), "%s %s", token, out);
                strcpy(out, temp);
            }
            else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

int getch(void);
void ungetch(int);

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        *p++ = c;
        while ((*p++ = getch()) != ']')
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getch()))
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        token[0] = c;
        token[1] = '\0';
        return tokentype = c;
    }
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

