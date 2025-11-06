#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100

int getword(char *word, int lim) {
    int c;
    char *w = word;
    
    // Skip whitespace
    while (isspace(c = getchar()))
        ;
    
    if (c == EOF)
        return EOF;
    
    *w++ = c;
    *w = '\0';
    
    // Handle preprocessor line starting with '#'
    if (c == '#') {
        while ((c = getchar()) != '\n' && c != EOF)
            ;  // skip to end of line
        return getword(word, lim); // restart for next word
    }
    
    // Handle comments (// or /* */)
    if (c == '/') {
        int next = getchar();
        if (next == '/') {  // single-line comment
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        } else if (next == '*') {  // multi-line comment
            int prev = 0;
            while ((c = getchar()) != EOF) {
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim);
        } else {
            ungetc(next, stdin); // push back the character
            return c;  // just return '/'
        }
    }
    
    // Handle string literal
    if (c == '"' || c == '\'') {
        int quote = c;
        while ((c = getchar()) != EOF && c != quote) {
            if (c == '\\') // escape character
                getchar(); // skip next char
        }
        return getword(word, lim);
    }
    
    // Build an identifier: includes letters, digits, underscores
    if (isalpha(c) || c == '_') {
        while (--lim > 0 && (isalnum(c = getchar()) || c == '_'))
            *w++ = c;
        *w = '\0';
        if (c != EOF)
            ungetc(c, stdin);
        return word[0];
    }
    
    // Otherwise, just return the character (non-identifier)
    *w = '\0';
    return c;
}

int main() {
    char word[MAXWORD];
    int type;

    printf("Enter input (Ctrl+D to end):\n");
    while ((type = getword(word, MAXWORD)) != EOF) {
        printf("Got token starting with '%c': %s\n", type, word);
    }

    return 0;
}

