#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXLINE 1000

// List of noise words to exclude
const char *noise_words[] = {
    "the", "and", "a", "an", "of", "to", "in", "is", "it", "that", "with", "as",
    "for", "was", "on", "at", "by", "which"
};
#define NOISE_COUNT (sizeof(noise_words) / sizeof(noise_words[0]))

// Simple binary tree node to store words and list of line numbers
typedef struct LineNode {
    int lineno;
    struct LineNode *next;
} LineNode;

typedef struct WordNode {
    char *word;
    LineNode *lines;
    struct WordNode *left;
    struct WordNode *right;
} WordNode;

// Function prototypes
int getword(char *word, int lim);
int is_noise_word(const char *word);
WordNode *add_word(WordNode *node, char *word, int lineno);
void add_line(LineNode **head, int lineno);
void print_tree(WordNode *node);
void free_tree(WordNode *node);
void free_lines(LineNode *head);

int main() {
    char line[MAXLINE];
    char word[MAXWORD];
    int lineno = 0;
    WordNode *root = NULL;

    printf("Enter text (Ctrl+D to end):\n");

    while (fgets(line, MAXLINE, stdin) != NULL) {
        lineno++;
        char *p = line;
        while (*p) {
            // Skip non-alpha chars
            while (*p && !isalpha(*p))
                p++;
            if (!*p)
                break;
            int i = 0;
            // Get a word limited by MAXWORD-1
            while (p[i] && isalpha(p[i]) && i < MAXWORD - 1) {
                word[i] = tolower(p[i]);
                i++;
            }
            word[i] = '\0';
            p += i;
            // Add to tree if not noise word
            if (!is_noise_word(word))
                root = add_word(root, word, lineno);
        }
    }

    printf("\nCross-reference (words and line numbers):\n");
    print_tree(root);

    free_tree(root);
    return 0;
}

int is_noise_word(const char *word) {
    for (size_t i = 0; i < NOISE_COUNT; i++) {
        if (strcmp(word, noise_words[i]) == 0)
            return 1;
    }
    return 0;
}

WordNode *add_word(WordNode *node, char *word, int lineno) {
    int cond;
    if (node == NULL) {
        node = malloc(sizeof(WordNode));
        node->word = strdup(word);
        node->left = node->right = NULL;
        node->lines = NULL;
        add_line(&node->lines, lineno);
    } else if ((cond = strcmp(word, node->word)) == 0) {
        add_line(&node->lines, lineno);
    } else if (cond < 0) {
        node->left = add_word(node->left, word, lineno);
    } else {
        node->right = add_word(node->right, word, lineno);
    }
    return node;
}

void add_line(LineNode **head, int lineno) {
    LineNode *curr = *head;
    while (curr != NULL) {
        if (curr->lineno == lineno)  // Already recorded line number for this word
            return;
        if (curr->next == NULL)
            break;
        curr = curr->next;
    }
    LineNode *newnode = malloc(sizeof(LineNode));
    newnode->lineno = lineno;
    newnode->next = NULL;
    if (curr == NULL)  // first line node
        *head = newnode;
    else
        curr->next = newnode;
}

void print_tree(WordNode *node) {
    if (node == NULL)
        return;
    print_tree(node->left);
    printf("%s: ", node->word);
    for (LineNode *ln = node->lines; ln != NULL; ln = ln->next) {
        printf("%d ", ln->lineno);
    }
    printf("\n");
    print_tree(node->right);
}

void free_lines(LineNode *head) {
    while (head) {
        LineNode *temp = head;
        head = head->next;
        free(temp);
    }
}

void free_tree(WordNode *node) {
    if (node == NULL)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node->word);
    free_lines(node->lines);
    free(node);
}

