#include <stdio.h>

// Convert uppercase letter to lowercase using conditional expression
int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

int main() {
    char test_chars[] = {'A', 'Z', 'a', 'z', '!', '1'};
    int size = sizeof(test_chars) / sizeof(test_chars[0]);

    for (int i = 0; i < size; i++) {
        char original = test_chars[i];
        char converted = lower(original);
        printf("Original: %c, Lowercase: %c\n", original, converted);
    }

    return 0;
}

