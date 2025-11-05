#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define FOLDLEN 20

int getline_custom(char s[], int lim);
void fold_line(char in[], char out[]);

int main(void) {
    char line[MAXLINE];
    char temp[MAXLINE * 2]; // Bigger to hold folded output per line
    int len;

    while ((len = getline_custom(line, MAXLINE)) > 0) {
        fold_line(line, temp);
        printf("%s\n", temp); // Print each folded line directly
    }
    return 0;
}

// Reads a single input line.
// Returns number of chars read (excluding '\0').
int getline_custom(char s[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n') // keep newline if present
        s[i++] = c;
    s[i] = '\0';
    return i;
}

// Folds line at FOLDLEN after the last blank/tab before the cutoff, or at cutoff if no blank.
void fold_line(char in[], char out[]) {
    int i = 0, j = 0, col = 0, last_space = -1;
    while (in[i] != '\0') {
        out[j] = in[i];
        if (in[i] == ' ' || in[i] == '\t')
            last_space = j;
        col++;
        if (col >= FOLDLEN) {
            if (last_space != -1) {
                out[last_space] = '\n';    // fold at last space
                col = j - last_space;
                last_space = -1;
            } else {
                j++;
                out[j-1] = '\n';           // hard break if no space
                col = 0;
            }
        }
        i++;
        j++;
    }
    out[j] = '\0';
}

