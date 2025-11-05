#include <stdio.h>

// Function to check if a character is in string s2
int is_in_string(char c, char s2[]) {
    int i = 0;
    while (s2[i] != '\0') {
        if (c == s2[i]) {
            return 1; // character found in s2
        }
        i++;
    }
    return 0; // character not found
}

// Function to delete from s1 any character that matches any character in s2
void squeeze(char s1[], char s2[]) {
    int i, j;
    i = j = 0;

    while (s1[i] != '\0') {
        if (!is_in_string(s1[i], s2)) {
            s1[j++] = s1[i];
        }
        i++;
    }

    s1[j] = '\0';
}

int main() {
    char s1[] = "hello world";
    char s2[] = "ole";

    printf("Original s1: %s\n", s1);
    printf("Characters to delete (s2): %s\n", s2);

    squeeze(s1, s2);

    printf("Modified s1 after squeeze: %s\n", s1);

    return 0;
}

