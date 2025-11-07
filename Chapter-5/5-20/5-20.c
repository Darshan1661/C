#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS, QUALIFIER };

int gettoken(void);
void dcl(void);
int dirdcl(void);
void parse_args(void);

int tokentype;                /* type of last token */
char token[MAXTOKEN];         /* last token string */
char name[MAXTOKEN];          /* identifier name */
char datatype[MAXTOKEN];      /* data type = int, char, const int, etc */
char out[1000];               /* output string */

int main() {
    while (gettoken() != EOF) { /* 1st token on line */
        if (tokentype == QUALIFIER) {
            /* accumulate qualifiers */
            strcpy(datatype, token);
            while (gettoken() == QUALIFIER) {
                strcat(datatype, " ");
                strcat(datatype, token);
            }
            // fall through to copy datatype if token was not a qualifier
        } else if (tokentype == NAME) {
            strcpy(datatype, token);
            gettoken();
        } else {
            printf("error: expected datatype or qualifier\n");
            while (tokentype != '\n' && tokentype != EOF)
                gettoken();
            continue;
        }

        out[0] = '\0';
        dcl(); /* parse rest of declaration */

        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; )
        ns++;

    if (!dirdcl()) {
        return;
    }

    while (ns-- > 0)
        strcat(out, " pointer to");
}

int dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
        else
            gettoken();
        if (tokentype == '(') {
            strcat(out, " function taking ");
            parse_args();
            strcat(out, " returning");
        }
    }
    else if (tokentype == NAME) {
        strcpy(name, token);
        gettoken();
    }
    else {
        printf("error: expected name or (dcl)\n");
        return 0;
    }

    while ((type=gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
    return 1;
}

void parse_args(void) {
    /* Simple parser for comma-separated list of types as function args */
    while (tokentype != ')') {
        if (tokentype == QUALIFIER || tokentype == NAME) {
            strcat(out, token);
            gettoken();
        }
        if (tokentype == ',') {
            strcat(out, ", ");
            gettoken();
        }
        else if (tokentype != ')') {
            printf("syntax error in function arguments\n");
            break;
        }
    }
    if (tokentype == ')')
        gettoken(); /* consume ')' */
}

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            return tokentype = '(';
        }
    } else if (c == '[') {
        *p++ = c;
        while ((*p++ = getchar()) != ']')
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getchar()))
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);

        if (strcmp(token, "const") == 0 || strcmp(token, "volatile") == 0)
            return tokentype = QUALIFIER;

        return tokentype = NAME;
    } else {
        token[0] = c;
        token[1] = '\0';
        return tokentype = c;
    }
}

