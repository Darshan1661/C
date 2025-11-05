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

void itob(int n, char s[], int b) {
    static char digits[] = "0123456789ABCDEF";
    unsigned int num;
    int i = 0, sign = n;

    if (sign < 0) {
        num = (unsigned int)(-n);  // Consider absolute value for unsigned conversion
    } else {
        num = (unsigned int)n;
    }

    if (num == 0) {
        s[i++] = '0';
    }

    while (num > 0) {
        s[i++] = digits[num % b];
        num /= b;
    }

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

int main() {
    char s[50];

    itob(255, s, 10);
    printf("Decimal: %s\n", s);

    itob(255, s, 16);
    printf("Hexadecimal: %s\n", s);

    itob(-255, s, 2);
    printf("Binary: %s\n", s);

    itob(12345, s, 8);
    printf("Octal: %s\n", s);

    return 0;
}

