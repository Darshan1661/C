#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 1000

char *lineptr[MAXLINES];

int numeric = 0;
int reverse = 0;
int fold = 0;

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

int numcmp(const char *, const char *);
int foldstrcmp(const char *, const char *);

int compare(const void *, const void *);

int main(int argc, char *argv[]) {
    int nlines;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;
        else if (strcmp(argv[i], "-r") == 0)
            reverse = 1;
        else if (strcmp(argv[i], "-f") == 0)
            fold = 1;
        else {
            fprintf(stderr, "Usage: %s [-n] [-r] [-f]\n", argv[0]);
            return 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        fprintf(stderr, "input too big to sort\n");
        return 1;
    }

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
    else if (fold)
        res = foldstrcmp(s1, s2);
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

int foldstrcmp(const char *s, const char *t) {
    for (; *s != '\0' && *t != '\0'; s++, t++) {
        char cs = tolower((unsigned char)*s);
        char ct = tolower((unsigned char)*t);
        if (cs != ct)
            return cs - ct;
    }
    return tolower((unsigned char)*s) - tolower((unsigned char)*t);
}

int readlines(char *lineptr[], int maxlines) {
    char line[1000];
    int nlines = 0;
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int len = strlen(line);
        if (len > 0 && line[len -1] == '\n')
            line[len - 1] = '\0';

        if (nlines >= maxlines) {
            return -1;
        } else {
            char *p = malloc(len + 1);
            if (!p) {
                fprintf(stderr, "memory allocation failed\n");
                return -1;
            }
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

