#include <stdio.h>
#include <ctype.h>

int htoi(char s[]) {
    int i = 0;
    int n = 0;
    int digit;

    // Skip optional "0x" or "0X"
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    }

    for (; s[i] != '\0'; ++i) {
        if (isdigit(s[i])) {
            digit = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            digit = s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            digit = s[i] - 'A' + 10;
        } else {
            // Invalid character encountered
            break;
        }
        n = 16 * n + digit;
    }

    return n;
}

int main() {
    char hex1[] = "0x1A3F";
    char hex2[] = "7b";
    char hex3[] = "0Xabc";
    char hex4[] = "123";

    printf("htoi(\"%s\") = %d\n", hex1, htoi(hex1));
    printf("htoi(\"%s\") = %d\n", hex2, htoi(hex2));
    printf("htoi(\"%s\") = %d\n", hex3, htoi(hex3));
    printf("htoi(\"%s\") = %d\n", hex4, htoi(hex4));

    return 0;
}

