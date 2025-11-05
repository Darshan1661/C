#include <stdio.h>

#define MAXLINE 1000  // maximum input line length

// Function prototypes
int getline_custom(char s[], int lim);
void reverse(char s[]);

// main: read a line, reverse it, print it
int main() {
    char line[MAXLINE];

    while (getline_custom(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }
    return 0;
}

// getline_custom: read a line into s, return its length
int getline_custom(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {    // include newline if present
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

// reverse: reverse string s in place
void reverse(char s[]) {
    int i, j;
    char temp;

    // find length of string
    for (i = 0; s[i] != '\0'; ++i)
        ;
    
    // if last character is '\n', ignore it for reversal
    if (i > 0 && s[i - 1] == '\n')
        i--;

    j = 0;
    --i;  // set i to last valid index before '\0'
    while (j < i) {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
        ++j;
        --i;
    }
}

