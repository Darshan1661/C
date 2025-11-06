#include <stdio.h>
#include <string.h>

// Helper function to swap characters at positions i and j
void swap(char s[], int i, int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

// Recursive reverse function that reverses s from index i to j
void reverse_recursive(char s[], int i, int j) {
    if (i >= j)
        return;
    swap(s, i, j);
    reverse_recursive(s, i + 1, j - 1);
}

// Wrapper reverse function
void reverse(char s[]) {
    int len = strlen(s);
    reverse_recursive(s, 0, len - 1);
}

// Test program
int main() {
    char s1[] = "hello";
    reverse(s1);
    printf("%s\n", s1);  // Output: "olleh"

    char s2[] = "abcd";
    reverse(s2);
    printf("%s\n", s2);  // Output: "dcba"

    char s3[] = "a";
    reverse(s3);
    printf("%s\n", s3);  // Output: "a"

    char s4[] = "";
    reverse(s4);
    printf("%s\n", s4);  // Output: ""

    return 0;
}

