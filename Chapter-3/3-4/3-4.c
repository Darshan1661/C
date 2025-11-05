#include <stdio.h>

void reverse(char s[]) {
    int i, j;
    char tmp;
    for (i = 0, j = 0; s[j] != '\0'; j++);
    j--; // last valid index

    while (i < j) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }
}

// Modified itoa: converts integer n to string s, handles largest negative int
void itoa(int n, char s[]) {
    int i = 0;
    unsigned int num;
    int sign = n;

    if (sign < 0) {
        num = (unsigned int)(-(sign + 1)) + 1; // Correctly handle largest negative
    } else {
        num = (unsigned int)n;
    }

    do {
        s[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

int main() {
    int test_values[] = {123, -123, -2147483648}; // -2147483648 is INT_MIN on 32-bit

    char buffer[50];
    for (int i = 0; i < 3; i++) {
        itoa(test_values[i], buffer);
        printf("itoa(%d) = %s\n", test_values[i], buffer);
    }

    return 0;
}

