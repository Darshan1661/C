#include <stdio.h>

int main(void) {
    int c, next;
    int paren = 0, bracket = 0, brace = 0;  // counters for unmatched delimiters
    enum State {NORMAL, IN_STRING, IN_CHAR, IN_COMMENT, IN_LINE_COMMENT} state = NORMAL;

    while ((c = getchar()) != EOF) {
        switch (state) {
            case NORMAL:
                if (c == '"') {
                    state = IN_STRING;
                } else if (c == '\'') {
                    state = IN_CHAR;
                } else if (c == '/') {
                    next = getchar();
                    if (next == '*') {
                        state = IN_COMMENT;
                    } else if (next == '/') {
                        state = IN_LINE_COMMENT;
                    } else {
                        if (next != EOF)
                            ungetc(next, stdin);
                    }
                } else {
                    if (c == '(') paren++;
                    else if (c == ')') paren--;
                    else if (c == '[') bracket++;
                    else if (c == ']') bracket--;
                    else if (c == '{') brace++;
                    else if (c == '}') brace--;
                }
                break;
                
            case IN_STRING:
                if (c == '\\') {      // escape character inside string
                    getchar();         // skip escaped character
                } else if (c == '"') {
                    state = NORMAL;
                }
                break;
                
            case IN_CHAR:
                if (c == '\\') {      // escape character inside char
                    getchar();         // skip escaped character
                } else if (c == '\'') {
                    state = NORMAL;
                }
                break;
                
            case IN_COMMENT:
                if (c == '*') {
                    next = getchar();
                    if (next == '/') {
                        state = NORMAL;
                    } else if (next != EOF) {
                        ungetc(next, stdin);
                    }
                }
                break;
                
            case IN_LINE_COMMENT:
                if (c == '\n') {
                    state = NORMAL;
                }
                break;
        }
        // Check for negative counters indicating unmatched closing delimiters
        if (paren < 0 || bracket < 0 || brace < 0) {
            printf("Syntax error: unmatched closing delimiter detected.\n");
            return 1;
        }
    }

    // After reading input, check for unmatched opening delimiters
    if (paren > 0)
        printf("Syntax error: missing %d closing parenthesis(es).\n", paren);
    if (bracket > 0)
        printf("Syntax error: missing %d closing bracket(s).\n", bracket);
    if (brace > 0)
        printf("Syntax error: missing %d closing brace(s).\n", brace);
    if (paren == 0 && bracket == 0 && brace == 0)
        printf("No unmatched parentheses, brackets, or braces found.\n");

    return 0;
}

