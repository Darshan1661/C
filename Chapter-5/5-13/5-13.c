#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000       // max lines to store
#define MAXLEN 1000         // max length of each line

char *lineptr[MAXLINES];    // pointers to lines

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int from);

int main(int argc, char *argv[]) {
    int n = 10;   // default number of lines
    if (argc == 2) {
        if (argv[1][0] == '-' && argv[1][1] != '\0') {
            n = atoi(argv[1] + 1);
            if (n <= 0) {
                fprintf(stderr, "invalid number of lines: %s\n", argv[1]);
                return 1;
            }
        } else {
            fprintf(stderr, "usage: %s [-n]\n", argv[0]);
            return 1;
        }
    } else if (argc > 2) {
        fprintf(stderr, "usage: %s [-n]\n", argv[0]);
        return 1;
    }

    int nlines = readlines(lineptr, MAXLINES);
    if (nlines < 0) {
        fprintf(stderr, "error: input too big to process\n");
        return 1;
    }

    int start = (nlines > n) ? nlines - n : 0;
    writelines(lineptr, nlines, start);

    // Free allocated lines
    for (int i = 0; i < nlines; i++)
        free(lineptr[i]);

    return 0;
}

// readlines: read lines, allocate memory, and store pointers
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char line[MAXLEN];

    while (fgets(line, MAXLEN, stdin) != NULL) {
        len = strlen(line);

        // Remove trailing newline if present
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        if (nlines >= maxlines)   // too many lines
            return -1;

        lineptr[nlines] = malloc(len + 1);
        if (lineptr[nlines] == NULL) {
            fprintf(stderr, "error: memory allocation failed\n");
            return -1;
        }

        strcpy(lineptr[nlines], line);
        nlines++;
    }
    return nlines;
}

// writelines: print lines from index 'from' onwards
void writelines(char *lineptr[], int nlines, int from) {
    for (int i = from; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

