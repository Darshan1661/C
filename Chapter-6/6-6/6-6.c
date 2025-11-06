#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXVAL 1000

// Symbol table node for definitions
struct nlist {
    char *name;
    char *defn;
    struct nlist *next;
};

static struct nlist *def_table = NULL;

// Add or update a definition in the table
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    for (np = def_table; np != NULL; np = np->next) {
        if (strcmp(name, np->name) == 0) {
            free(np->defn);
            np->defn = strdup(defn);
            return np;
        }
    }
    np = malloc(sizeof(*np));
    if (!np || !(np->name = strdup(name)) || !(np->defn = strdup(defn)))
        return NULL;
    np->next = def_table;
    def_table = np;
    return np;
}

// Lookup definition by name
char *lookup(char *name) {
    struct nlist *np;
    for (np = def_table; np != NULL; np = np->next) {
        if (strcmp(name, np->name) == 0)
            return np->defn;
    }
    return NULL;
}

// Buffer for getch/ungetch
int buf = EOF;

int getch(void) {
    int c;
    if (buf != EOF) {
        c = buf;
        buf = EOF;
    } else {
        c = getchar();
    }
    return c;
}

void ungetch(int c) {
    buf = c;
}

// Get next word or symbol
int getword(char *word, int lim) {
    int c;
    char *w = word;

    // Skip whitespace
    while (isspace(c = getch()))
        ;

    if (c == EOF)
        return EOF;

    *w++ = c;

    if (isalpha(c) || c == '_') {
        while (--lim > 0) {
            c = getch();
            if (isalnum(c) || c == '_')
                *w++ = c;
            else {
                ungetch(c);
                break;
            }
        }
    } else {
        // Single char token (non-identifier)
    }

    *w = '\0';
    return word[0];
}

// Process input and handle #define directives and substitutions
void process(void) {
    char word[MAXWORD];
    char name[MAXWORD], defn[MAXWORD];
    int c;

    while ((c = getch()) != EOF) {
        if (c == '#') {
            // Possible #define directive
            char directive[MAXWORD];
            int i = 0;
            while ((c = getch()) != EOF && !isspace(c) && i < MAXWORD - 1)
                directive[i++] = c;
            directive[i] = '\0';

            if (strcmp(directive, "define") == 0) {
                // Read name
                while (isspace(c = getch()))
                    ;
                ungetch(c);
                if (getword(name, MAXWORD) == EOF)
                    break;

                // Read rest of line as definition
                int j = 0;
                while ((c = getch()) != EOF && c != '\n' && j < MAXWORD - 1) {
                    defn[j++] = c;
                }
                defn[j] = '\0';

                // Trim trailing spaces from defn
                while (j > 0 && isspace(defn[j - 1])) {
                    defn[--j] = '\0';
                }

                install(name, defn);
                // Skip to next line
                continue;
            } else {
                // Not a define, print the '#' and directive
                printf("#%s", directive);
                while (c != EOF && c != '\n') {
                    c = getch();
                    if (c != EOF)
                        putchar(c);
                }
                putchar('\n');
                continue;
            }
        } else if (isalpha(c) || c == '_') {
            // Identifier or keyword, read rest
            ungetch(c);
            if (getword(word, MAXWORD) == EOF)
                break;
            char* def = lookup(word);
            if (def != NULL)
                printf("%s", def);
            else
                printf("%s", word);
        } else {
            putchar(c);
        }
    }
}

int main() {
    process();
    return 0;
}

