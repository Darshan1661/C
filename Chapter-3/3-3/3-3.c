#include <stdio.h>
#include <ctype.h>

// Helper function to check if characters form a valid range
int valid_range(char start, char end) {
    if (isdigit(start) && isdigit(end)) {
        return start <= end;
    } 
    if (isalpha(start) && isalpha(end)) {
        return start <= end && 
               ((isupper(start) && isupper(end)) || (islower(start) && islower(end)));
    }
    return 0; // Invalid range if types don't match
}

void expand(const char s1[], char s2[]) {
    int i = 0, j = 0;
    char start, end;

    while (s1[i] != '\0') {
        if (s1[i] == '-' && i != 0 && s1[i+1] != '\0') {
            start = s1[i - 1];
            end = s1[i + 1];

            if (valid_range(start, end)) {
                // Expand the range, excluding the start character (already copied)
                for (char c = start + 1; c <= end; c++) {
                    s2[j++] = c;
                }
                i += 2; // skip the end character in s1 loop since already expanded
            } else {
                // Not a valid range, copy '-'
                s2[j++] = s1[i++];
            }
        } else {
            s2[j++] = s1[i++];
        }
    }
    s2[j] = '\0';
}

int main() {
    char s1[][50] = {
        "a-z",
        "A-Z",
        "0-9",
        "a-b-c",
        "a-z0-9",
        "-a-z",
        "a-z-",
        "a-Z",    // invalid range due to case difference
        "5-2",    // invalid numeric range descending
        "x-y-z"
    };

    char s2[200];

    for (int k = 0; k < sizeof(s1) / sizeof(s1[0]); k++) {
        expand(s1[k], s2);
        printf("expand(\"%s\") = \"%s\"\n", s1[k], s2);
    }

    return 0;
}

