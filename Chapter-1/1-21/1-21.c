#include <stdio.h>

#define TABSTOP 8  // Tab stops every 8 columns (symbolic parameter)

int main(void) {
    int c;
    int col = 0;  // Current column position
    int space = 0; // Count of blanks

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            space++;
            if ((col + space) % TABSTOP == 0) {
                putchar('\t');
                col += space;
                space = 0;
            }
        } else {
            // Output any accumulated spaces
            while (space > 0) {
                putchar(' ');
                space--;
                col++;
            }
            putchar(c);
            if (c == '\n') {
                col = 0;
            } else {
                col++;
            }
        }
    }
    return 0;
}

