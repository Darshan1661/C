#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTABSTOPS 100
#define DEFAULT_TAB_WIDTH 8

int tabstops[MAXTABSTOPS];
int ntab = 0;  // Number of tab stops

// Parse command line to get tab stops or default
void setup_tabstops(int argc, char *argv[]) {
    if (argc == 1) {
        // No tabs provided; set defaults every 8 columns
        for (int i = 0; i < MAXTABSTOPS; i++)
            tabstops[i] = (i + 1) * DEFAULT_TAB_WIDTH;
        ntab = MAXTABSTOPS;
    } else {
        // Parse provided tab stops as integers
        for (int i = 1; i < argc && i - 1 < MAXTABSTOPS; i++) {
            int pos = atoi(argv[i]);
            if (pos <= 0) {
                fprintf(stderr, "Invalid tab stop: %s\n", argv[i]);
                exit(1);
            }
            tabstops[ntab++] = pos;
        }
    }
}

// Return 1 if column is a tab stop; 0 otherwise
int is_tabstop(int col) {
    for (int i = 0; i < ntab; i++) {
        if (tabstops[i] == col)
            return 1;
        else if (tabstops[i] > col)
            return 0;
    }
    return 0;
}

void detab(FILE *input) {
    int c;
    int col = 0;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\t') {
            // Output spaces until next tab stop
            do {
                putchar(' ');
                col++;
            } while (!is_tabstop(col));
        } else if (c == '\n') {
            putchar(c);
            col = 0;
        } else {
            putchar(c);
            col++;
        }
    }
}

int main(int argc, char *argv[]) {
    setup_tabstops(argc, argv);

    printf("Using %d tab stops: ", ntab);
    for (int i = 0; i < ntab; i++)
        printf("%d ", tabstops[i]);
    printf("\n");

    detab(stdin);
    return 0;
}

