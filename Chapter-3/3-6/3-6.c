#include <stdio.h>

void reverse(char s[]) {
    int i, j;
    char tmp;
    for (i = 0; s[i] != '\0'; i++);
    j = i - 1;

    for (i = 0; i < j; i++, j--) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

void itoa(int n, char s[], int w) {
    int i = 0;
    int sign = n;
    unsigned int num;

    if (sign < 0) {
        num = (unsigned int)(-n);
    } else {
        num = (unsigned int)n;
    }

    // Convert number to string in reverse order
    do {
        s[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    // Pad with blanks on the left to meet minimum width
    while (i < w) {
        s[i++] = ' ';
    }

    s[i] = '\0';
    reverse(s);
}

int main() {
    char s[50];

    itoa(123, s, 8);
    printf("'%s'\n", s);  // padded with blanks on left to width 8

    itoa(-4567, s, 10);
    printf("'%s'\n", s);  // padded to width 10

    itoa(890, s, 2);
    printf("'%s'\n", s);  // no padding needed, width less than number length

    return 0;
}

