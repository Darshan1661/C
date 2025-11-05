#include <stdio.h>

#define MAXLINE 1000   // maximum input line size
#define LIMIT 80       // minimum length to print

int my_getline(char line[], int maxline);

/* main: print all lines longer than 80 characters */
int main(void) {
    int len;             // current line length
    char line[MAXLINE];  // current input line

    while ((len = my_getline(line, MAXLINE)) > 0) {
        if (len > LIMIT) // print only if longer than 80 characters
            printf("%s", line);
    }
    return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;  // store newline
        ++i;
    }

    s[i] = '\0';    // null-terminate string
    return i;       // return line length
}

