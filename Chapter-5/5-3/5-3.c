#include <stdio.h>

// strcat: append string t to the end of s (pointer version)
void strcat_ptr(char *s, const char *t) {
    while (*s)   // move s pointer to end of string s
        s++;
    while ((*s++ = *t++) != '\0')    // copy t to s including '\0'
        ;
}

// Test program
int main() {
    char s[100] = "Hello, ";
    const char *t = "World!";

    strcat_ptr(s, t);
    printf("%s\n", s);  // Output: Hello, World!

    return 0;
}

