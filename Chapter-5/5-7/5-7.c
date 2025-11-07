#include <stdio.h>
#include <string.h>

#define MAXLINES 5000      // max number of lines
#define MAXLEN 1000        // max length of any input line

int my_getline(char *s, int lim);

int readlines(char *lines[], char *buf, int maxlines, int bufsize) {
    int len, nlines = 0;
    char line[MAXLEN];
    char *p = buf;
    char *bufend = buf + bufsize;

    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len + 1 > bufend)
            return -1;
        line[len-1] = '\0';  // remove newline
        strcpy(p, line);
        lines[nlines++] = p;
        p += len;
    }
    return nlines;
}

// Renamed getline to my_getline to avoid conflict
int my_getline(char *s, int lim) {
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }

    if (c == '\n')
        *s++ = c;

    *s = '\0';
    return s - start;
}

int main() {
    char *lines[MAXLINES];
    char buffer[MAXLINES * MAXLEN];
    int nlines, i;

    printf("Enter lines (Ctrl+D to end):\n");
    nlines = readlines(lines, buffer, MAXLINES, sizeof(buffer));
    if (nlines < 0) {
        printf("Input too big to process.\n");
        return 1;
    }

    printf("\nRead %d lines:\n", nlines);
    for (i = 0; i < nlines; i++) {
        printf("%s", lines[i]);
    }

    return 0;
}

