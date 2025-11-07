#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXFIELDS 10
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort_custom(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int charcmp(char *, char *, int fold, int dir);
int getline_custom(char *, int);

struct fieldopt {
    int start;     // starting field index
    int end;       // ending field index
    int numeric;
    int fold;
    int directory;
    int reverse;
};

struct fieldopt fields[MAXFIELDS];
int nfields = 0;

/* function prototypes */
int fieldcmp(char *s1, char *s2);
void extractfield(char *src, char *dest, int start, int end);

/* main: sort lines with field-based options */
int main(int argc, char *argv[])
{
    int nlines;
    int i;

    // default global options
    struct fieldopt global = {0, 9999, 0, 0, 0, 0};

    // parse arguments
    while (--argc > 0 && (*++argv)[0] == '-') {
        char *p = *argv;
        if (p[1] == 'n') global.numeric = 1;
        else if (p[1] == 'r') global.reverse = 1;
        else if (p[1] == 'f') global.fold = 1;
        else if (p[1] == 'd') global.directory = 1;
        else {
            printf("Invalid flag %s\n", p);
            return 1;
        }
    }

    // parse field specifications like +0 -1
    argv -= nfields; // reset pointer
    for (i = 1; i < argc; i++) {
        if ((*argv)[0] == '+') {
            fields[nfields].start = atoi((*argv) + 1);
            fields[nfields].end = 9999;
            fields[nfields].numeric = global.numeric;
            fields[nfields].fold = global.fold;
            fields[nfields].directory = global.directory;
            fields[nfields].reverse = global.reverse;
            nfields++;
        } else if ((*argv)[0] == '-') {
            if (nfields > 0)
                fields[nfields - 1].end = atoi((*argv) + 1);
        }
        argv++;
    }

    if (nfields == 0) {
        fields[0] = global;
        fields[0].start = 0;
        fields[0].end = 9999;
        nfields = 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        printf("error: input too big to sort\n");
        return 1;
    }

    qsort_custom((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))fieldcmp);
    writelines(lineptr, nlines);

    return 0;
}

/* qsort_custom: generic quicksort */
void qsort_custom(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_custom(v, left, last - 1, comp);
    qsort_custom(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* fieldcmp: compare s1 and s2 by fields */
int fieldcmp(char *s1, char *s2)
{
    char substr1[MAXLEN], substr2[MAXLEN];
    int result = 0;

    for (int i = 0; i < nfields; i++) {
        extractfield(s1, substr1, fields[i].start, fields[i].end);
        extractfield(s2, substr2, fields[i].start, fields[i].end);

        if (fields[i].numeric)
            result = numcmp(substr1, substr2);
        else
            result = charcmp(substr1, substr2, fields[i].fold, fields[i].directory);

        if (fields[i].reverse)
            result = -result;

        if (result != 0)
            return result; // stop at first unequal field
    }

    return 0;
}

/* extractfield: extract substring from start..end field */
void extractfield(char *src, char *dest, int start, int end)
{
    int i = 0, j = 0, field = 0;

    // skip to start field
    while (*src && field < start) {
        if (*src == ' ' || *src == '\t')
            while (*src == ' ' || *src == '\t')
                src++;
        else {
            while (*src && *src != ' ' && *src != '\t')
                src++;
            field++;
        }
    }

    // copy until end field
    while (*src && field < end) {
        if (*src == ' ' || *src == '\t') {
            if (j > 0) break;
        }
        dest[j++] = *src++;
    }

    dest[j] = '\0';
}

/* numcmp: compare strings numerically */
int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1), v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* charcmp: compare strings alphabetically with fold and directory */
int charcmp(char *s1, char *s2, int fold, int dir)
{
    char a, b;

    do {
        if (dir) {
            while (*s1 && !isalnum((unsigned char)*s1) && *s1 != ' ')
                s1++;
            while (*s2 && !isalnum((unsigned char)*s2) && *s2 != ' ')
                s2++;
        }
        a = fold ? tolower((unsigned char)*s1) : *s1;
        b = fold ? tolower((unsigned char)*s2) : *s2;
        s1++;
        s2++;
        if (a != b)
            return a - b;
    } while (a && b);

    return a - b;
}

/* readlines: read all input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = getline_custom(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len + 1)) == NULL)
            return -1;
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

/* writelines: print all lines */
void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
}

/* getline_custom: get line, return length */
int getline_custom(char *s, int lim)
{
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

