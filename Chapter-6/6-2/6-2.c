#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXLEN 1000  // max length for variable names

struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

int N = 6;  // default comparison length, can be overridden by command-line argument

// getword prototype
int getword(char *word, int lim);

// tree node insertion sorting by first N chars and full word to find groups
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
void print_groups(struct tnode *p);
void free_tree(struct tnode *p);

int compare_n(const char *s1, const char *s2, int n);

struct tnode* group_head = NULL;

int main(int argc, char *argv[]) {
    char word[MAXWORD];
    struct tnode *root = NULL;

    // Allow N to be passed as command line argument
    if (argc > 1) {
        N = atoi(argv[1]);
        if (N <= 0) {
            fprintf(stderr, "Invalid N value; using default 6\n");
            N = 6;
        }
    }

    // Read words, ignoring strings and comments, collect identifiers
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) || word[0] == '_') {
            root = addtree(root, word);
        }
    }

    // Print groups of variable names that are identical in first N chars but differ later
    print_groups(root);

    free_tree(root);

    return 0;
}

// Recursive comparison for first n chars
int compare_n(const char *s1, const char *s2, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        if (s1[i] == '\0') {  // if one ends earlier
            return 0;
        }
    }
    return 0;
}

struct tnode *talloc(void);
char *strdup_custom(const char *s);

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = strdup_custom(w);
        p->left = p->right = NULL;
    } else {
        // Compare only first N chars first
        cond = compare_n(w, p->word, N);
        if (cond == 0) {
            // Same first N chars: full strcmp to place correctly
            cond = strcmp(w, p->word);
            // Only add different words to tree
            if (cond == 0) {
                return p; // ignore identical word
            }
        }
        if (cond < 0)
            p->left = addtree(p->left, w);
        else
            p->right = addtree(p->right, w);
    }
    return p;
}

void print_groups(struct tnode *p) {
    static char prev_prefix[MAXLEN] = "";
    static int have_group = 0;

    if (p != NULL) {
        print_groups(p->left);
        if (strlen(p->word) >=(size_t) N) {
            // Extract prefix of length N
            char prefix[MAXLEN];
            strncpy(prefix, p->word, N);
            prefix[N] = '\0';

            if (strcmp(prefix, prev_prefix) != 0) {
                if (have_group) {
                    printf("\n");
                }
                printf("Group for prefix \"%s\":\n", prefix);
                strcpy(prev_prefix, prefix);
                have_group = 1;
            }
            printf("  %s\n", p->word);
        }
        print_groups(p->right);
    }
}

void free_tree(struct tnode *p) {
    if (p != NULL) {
        free_tree(p->left);
        free_tree(p->right);
        free(p->word);
        free(p);
    }
}

struct tnode* talloc(void) {
    return (struct tnode*) malloc(sizeof(struct tnode));
}

char* strdup_custom(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}


// Enhanced getword function ignoring strings, comments, and preprocessor lines
int getword(char *word, int lim) {
    int c;
    char *w = word;
    
    // Skip whitespace
    while (isspace(c = getchar()))
        ;
    
    if (c == EOF)
        return EOF;
    
    *w++ = c;
    *w = '\0';
    
    // Handle preprocessor line starting with '#'
    if (c == '#') {
        while ((c = getchar()) != '\n' && c != EOF)
            ;  // skip to end of line
        return getword(word, lim); // restart for next word
    }
    
    // Handle comments (// or /* */)
    if (c == '/') {
        int next = getchar();
        if (next == '/') {  // single-line comment
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        } else if (next == '*') {  // multi-line comment
            int prev = 0;
            while ((c = getchar()) != EOF) {
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim);
        } else {
            ungetc(next, stdin); // push back the character
            return c;  // just return '/'
        }
    }
    
    // Handle string literal
    if (c == '"' || c == '\'') {
        int quote = c;
        while ((c = getchar()) != EOF && c != quote) {
            if (c == '\\') // escape character
                getchar(); // skip next char
        }
        return getword(word, lim);
    }
    
    // Build an identifier: includes letters, digits, underscores
    if (isalpha(c) || c == '_') {
        while (--lim > 0 && (isalnum(c = getchar()) || c == '_'))
            *w++ = c;
        *w = '\0';
        if (c != EOF)
            ungetc(c, stdin);
        return word[0];
    }
    
    // Otherwise, just return the character (non-identifier)
    *w = '\0';
    return c;
}

