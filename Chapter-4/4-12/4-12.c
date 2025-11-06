#include <stdio.h>

// Recursive helper to build number string
void itoa_rec(int n, char s[], int *pos) {
    if (n / 10)
        itoa_rec(n / 10, s, pos);
    s[(*pos)++] = (n % 10) + '0';
}

// Recursive itoa converting n to string s
void itoa(int n, char s[]) {
    int pos = 0;
    if (n < 0) {
        s[pos++] = '-';
        // Handle INT_MIN safely
        unsigned int un = (unsigned int)(-(n + 1)) + 1;
        itoa_rec(un, s, &pos);
    } else {
        itoa_rec(n, s, &pos);
    }
    s[pos] = '\0';
}

int main() {
    char s[50];

    itoa(12345, s);
    printf("%s\n", s);

    itoa(-98765, s);
    printf("%s\n", s);

    itoa(0, s);
    printf("%s\n", s);

    itoa(-2147483648, s);  // INT_MIN
    printf("%s\n", s);

    return 0;
}

