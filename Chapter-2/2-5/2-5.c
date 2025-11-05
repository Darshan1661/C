#include <stdio.h>

// Function to check if character c is in string s2
int is_in_string(char c, char s2[]) {
    int i = 0;
    while (s2[i] != '\0') {
        if (c == s2[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

// Returns the index of first location in s1 where any char from s2 occurs
// Returns -1 if none found
int any(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0') {
        if (is_in_string(s1[i], s2)) {
            return i;
        }
        i++;
    }
    return -1;
}

int main() {
    char s1[] = "hello world";
    char s2[] = "ow";

    int pos = any(s1, s2);

    if (pos >= 0) {
        printf("First matching character found at index %d: '%c'\n", pos, s1[pos]);
    } else {
        printf("No characters from s2 found in s1\n");
    }

    return 0;
}

