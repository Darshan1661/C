#include <stdio.h>

#define MAXLINE 1000  // maximum input line length

// Function prototypes
int getline_custom(char line[], int maxline);
void remove_trailing_blanks(char line[]);

int main() {
    char line[MAXLINE];

    while (getline_custom(line, MAXLINE) > 0) {
        remove_trailing_blanks(line);
        // print only non-empty lines
        if (line[0] != '\0')
            printf("%s", line);
    }
    return 0;
}

// getline_custom: reads a line into s, returns length
int getline_custom(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

// remove_trailing_blanks: trims spaces/tabs from the end
void remove_trailing_blanks(char s[]) {
    int i = 0;
    while (s[i] != '\0')     // find end of string
        ++i;
    --i;                     // move to last valid character

    // move backwards to remove blanks/tabs/newline
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
        --i;

    // If we found a valid char, add newline and terminator
    if (i >= 0) {
        s[++i] = '\n';
        s[++i] = '\0';
    } else {
        // Entire line was blank
        s[0] = '\0';
    }
}

