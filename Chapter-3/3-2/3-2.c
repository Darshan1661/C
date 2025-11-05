#include <stdio.h>

// Convert special characters into escape sequences during copy from t to s
void escape(char s[], const char t[]) {
    int i = 0, j = 0;
    char c;
    while ((c = t[i++]) != '\0') {
        switch (c) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\b':
                s[j++] = '\\';
                s[j++] = 'b';
                break;
            case '\r':
                s[j++] = '\\';
                s[j++] = 'r';
                break;
            case '\f':
                s[j++] = '\\';
                s[j++] = 'f';
                break;
            case '\\':
                s[j++] = '\\';
                s[j++] = '\\';
                break;
            default:
                s[j++] = c;
                break;
        }
    }
    s[j] = '\0';
}

// Convert escape sequences in t into real characters while copying to s
void unescape(char s[], const char t[]) {
    int i = 0, j = 0;
    char c;
    while ((c = t[i++]) != '\0') {
        if (c == '\\') {
            c = t[i++];
            switch (c) {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                case 'b':
                    s[j++] = '\b';
                    break;
                case 'r':
                    s[j++] = '\r';
                    break;
                case 'f':
                    s[j++] = '\f';
                    break;
                case '\\':
                    s[j++] = '\\';
                    break;
                default:
                    // If unknown escape, copy literally
                    s[j++] = '\\';
                    s[j++] = c;
                    break;
            }
        } else {
            s[j++] = c;
        }
    }
    s[j] = '\0';
}

int main() {
    char original[] = "Line1\nLine2\tTabbed\\Backslash\bBackspace";
    char escaped[200];
    char unescaped[200];

    escape(escaped, original);
    printf("Escaped: %s\n", escaped);

    unescape(unescaped, escaped);
    printf("Unescaped: %s\n", unescaped);

    return 0;
}

