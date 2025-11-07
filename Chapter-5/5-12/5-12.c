#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTABSTOPS 100

int tabstops[MAXTABSTOPS];
int ntab = 0;

void generate_tabstops(int m, int n) {
    int pos = m;
    while (ntab < MAXTABSTOPS && pos <= 1000) {  // arbitrary max column limit
        tabstops[ntab++] = pos;
        pos += n;
    }
}

void setup_tabstops(int argc, char *argv[]) {
    int m = 1, n = 8;      // default start and interval
    int shorthand_found = 0;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-m", 2) == 0 && i+1 < argc) {
            m = atoi(argv[++i]);
            shorthand_found = 1;
        } else if (argv[i][0] == '+') {
            n = atoi(argv[i] + 1);
            shorthand_found = 1;
        } else {
            // other tab stops or handle error
        }
    }

    if (shorthand_found) {
        generate_tabstops(m, n);
    } else {
        // default tabs every 8 columns
        for (int i = 0; i < MAXTABSTOPS; i++)
            tabstops[i] = (i + 1) * 8;
        ntab = MAXTABSTOPS;
    }
}

int main(int argc, char *argv[]) {
    setup_tabstops(argc, argv);

    printf("Tab stops:");
    for (int i = 0; i < ntab; i++)
        printf(" %d", tabstops[i]);
    printf("\n");
    return 0;
}

