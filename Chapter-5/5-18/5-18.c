#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS, ERROR };

int gettoken(void);
void dcl(void);
int dirdcl(void);

int tokentype;                /* type of last token */
char token[MAXTOKEN];         /* last token string */
char name[MAXTOKEN];          /* identifier name */
char datatype[MAXTOKEN];      /* data type = char, int, etc. */
char out[1000];               /* output string */

int main() {
    while (gettoken() != EOF) { /* 1st token on line */
        if (tokentype == ERROR) {
            /* Skip line on error token */
            while (tokentype != '\n' && tokentype != EOF)
                gettoken();
            continue;
        }
        strcpy(datatype, token);    /* is the datatype */
        out[0] = '\0';
        dcl();                     /* parse rest of declaration */
        if (tokentype != '\n')
            printf("syntax error: unexpected token '%s'\n", token);
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl: parse a declarator */
void dcl(void) {
    int ns;
    for (ns = 0; gettoken() == '*'; ) /* count *'s */
        ns++;
    if (!dirdcl())                  /* parse direct declarator */
        return;
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
/* returns 1 on success, 0 on error */
int dirdcl(void) {
    int type;

    if (tokentype == '(') {        /* ( dcl ) */
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            /* Attempt to recover by continuing */
            if (tokentype == ERROR) {
                /* skip to next valid token */
                while (tokentype != ')' && tokentype != '\n' && tokentype != EOF)
                    gettoken();
            }
        } else
            gettoken();  /* get next token after ')' */
    }
    else if (tokentype == NAME)     /* variable name */
        strcpy(name, token);
    else {
        printf("error: expected name or (dcl), got '%s'\n", token);
        return 0; /* failure */
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
    /* put back the last token read if it's not part of declarator */
    return 1;
}

int getch(void);
void ungetch(int);

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')  /* skip blanks */
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
            if (p - token >= MAXTOKEN - 1) {
                printf("error: bracket token too long\n");
                tokentype = ERROR;
                return ERROR;
            }
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getch()))
            if (p - token < MAXTOKEN - 1)
                *p++ = c;
            else {
                printf("error: token too long\n");
                tokentype = ERROR;
                return ERROR;
            }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else if (c == EOF) {
        return tokentype = EOF;
    } else {
        token[0] = c;
        token[1] = '\0';
        return tokentype = c;
    }
}

/* Buffer for getch/ungetch */
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

