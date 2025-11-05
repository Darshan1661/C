#include <stdio.h>

#define TABSTOP 8   // symbolic parameter: tab stops every 8 columns

int main(void) {
    int c;
    int col = 0;     // current column position

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = TABSTOP - (col % TABSTOP); // calculate spaces to next tab stop
            for (int i = 0; i < spaces; i++) {
                putchar(' ');
                col++;
            }
        } else if (c == '\n') {
            putchar(c);
            col = 0; // reset column at line end
        } else {
            putchar(c);
            col++;
        }
    }
    return 0;
}

