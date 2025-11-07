#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 1000    // max lines to be sorted

char *lineptr[MAXLINES];
int compare(const void*, const void*);

int numeric = 0;    // 1 for numeric sort
int reverse = 0;    // 1 for reverse order

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

int numcmp(const char *, const char *);

int main(int argc, char *argv[]) {
    int nlines;    // number of input lines read

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;
        else if (strcmp(argv[i], "-r") == 0)
            reverse = 1;
        else {
            fprintf(stderr, "Usage: %s [-n] [-r]\n", argv[0]);
            return 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        fprintf(stderr, "input too big to sort\n");
        return 1;
    }

    // Use qsort with compare function
    qsort(lineptr, nlines, sizeof(char *), compare);

    writelines(lineptr, nlines);
    return 0;
}

int compare(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    int res;

    if (numeric)
        res = numcmp(s1, s2);
    else
        res = strcmp(s1, s2);

    return reverse ? -res : res;
}

int numcmp(const char *s1, const char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int readlines(char *lineptr[], int maxlines) {
    int len;
    char *p;
    char line[1000];
    int nlines = 0;

    while (fgets(line, sizeof(line), stdin)) {
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        if (nlines >= maxlines) {
            return -1;
        } else {
            p = malloc(len + 1);
            if (p == NULL)
                return -1;
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

