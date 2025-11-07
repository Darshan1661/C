#include <stdio.h>
#include <string.h>

// strend: return 1 if t occurs at the end of s, else 0
int strend(const char *s, const char *t) {
    int len_s = strlen(s);
    int len_t = strlen(t);

    if (len_t > len_s)
        return 0;

    // Compare the substring of s starting at position len_s - len_t with t
    return strcmp(s + len_s - len_t, t) == 0;
}

// Test program
int main() {
    printf("%d\n", strend("hello world", "world"));  // Output: 1
    printf("%d\n", strend("hello world", "hello"));  // Output: 0
    printf("%d\n", strend("test", "test"));          // Output: 1
    printf("%d\n", strend("test", ""));              // Output: 1 (empty string)
    printf("%d\n", strend("abc", "abcd"));           // Output: 0

    return 0;
}

