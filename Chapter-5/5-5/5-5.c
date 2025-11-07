#include <stdio.h>

// Copies at most n characters of t to s; pads with '\0' if t is shorter than n.
char *strncpy_(char *s, const char *t, size_t n) {
    char *start = s;
    while (n && (*s++ = *t++))   // Copy up to n chars or until '\0' in t
        n--;
    while (n--)                  // Pad with '\0' if needed
        *s++ = '\0';
    return start;
}

// Appends at most n characters of t to the end of s, then '\0'.
char *strncat_(char *s, const char *t, size_t n) {
    char *start = s;
    while (*s)       // move s to end of string
        s++;
    while (n-- && (*s++ = *t++))  // copy at most n from t
        ;
    if (n != (size_t)-1)          // add '\0' if stopped before copying n chars (i.e., due to '\0' in t)
        *s = '\0';
    return start;
}

// Compares at most n characters; returns <0 if s<t, 0 if s==t, >0 if s>t in first n chars.
int strncmp_(const char *s, const char *t, size_t n) {
    for (; n > 0; s++, t++, n--) {
        if (*s != *t)
            return *(unsigned char *)s - *(unsigned char *)t;
        if (*s == '\0')
            return 0;
    }
    return 0;
}

// Test program
int main() {
    char a[20]; //, b[20]

    // strncpy_
    strncpy_(a, "hello", 10);
    printf("strncpy_: '%s'\n", a); // "hello"

    // strncat_
    strncpy_(a, "abc", 4);         // make a = "abc"
    strncat_(a, "XYZuvw", 3);      // a = "abcXYZ"
    printf("strncat_: '%s'\n", a);

    // strncmp_
    printf("strncmp_('abcd','abce',4) = %d\n", strncmp_("abcd", "abce", 4)); // negative
    printf("strncmp_('abcd','ab',2) = %d\n", strncmp_("abcd", "ab", 2));     // 0
    printf("strncmp_('abc','abc',5) = %d\n", strncmp_("abc", "abc", 5));     // 0

    return 0;
}

