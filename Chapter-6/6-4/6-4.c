#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

// Structure for word and its count
typedef struct WordNode {
    char *word;
    int count;
    struct WordNode *left;
    struct WordNode *right;
} WordNode;

WordNode* add_word(WordNode *node, char *word);
void inorder_collect(WordNode *node, WordNode **arr, int *index);
void free_tree(WordNode *node);
int compare_counts(const void *a, const void *b);
void print_words_by_freq(WordNode *root);

// Function to read words from input
int getword(char *word, int lim);

int main() {
    WordNode *root = NULL;
    char word[MAXWORD];
    int total_words = 0;

    printf("Enter text (Ctrl+D to end):\n");

    while (getword(word, MAXWORD) != EOF) {
        // Convert word to lowercase
        for (int i = 0; word[i]; i++)
            word[i] = tolower(word[i]);
        root = add_word(root, word);
        total_words++;
    }

    if (total_words == 0) {
        printf("No words entered.\n");
        return 0;
    }

    print_words_by_freq(root);

    free_tree(root);
    return 0;
}

WordNode* add_word(WordNode *node, char *word) {
    int cond;
    if (node == NULL) {
        node = malloc(sizeof(WordNode));
        node->word = strdup(word);
        node->count = 1;
        node->left = node->right = NULL;
    } else if ((cond = strcmp(word, node->word)) == 0) {
        node->count++;
    } else if (cond < 0) {
        node->left = add_word(node->left, word);
    } else {
        node->right = add_word(node->right, word);
    }
    return node;
}

void inorder_collect(WordNode *node, WordNode **arr, int *index) {
    if (node == NULL)
        return;
    inorder_collect(node->left, arr, index);
    arr[(*index)++] = node;
    inorder_collect(node->right, arr, index);
}

int compare_counts(const void *a, const void *b) {
    WordNode *wa = *(WordNode **)a;
    WordNode *wb = *(WordNode **)b;
    // Decreasing order of counts
    if (wb->count != wa->count)
        return wb->count - wa->count;
    // If equal counts, alphabetical order
    return strcmp(wa->word, wb->word);
}

void print_words_by_freq(WordNode *root) {
    // Count total distinct words
    int max_words = 1000;  // max distinct words (can be increased)
    WordNode **arr = malloc(max_words * sizeof(WordNode*));
    int index = 0;
    inorder_collect(root, arr, &index);

    qsort(arr, index, sizeof(WordNode *), compare_counts);

    printf("\nWords sorted by frequency:\n");
    for (int i = 0; i < index; i++) {
        printf("%d %s\n", arr[i]->count, arr[i]->word);
    }

    free(arr);
}

void free_tree(WordNode *node) {
    if (node == NULL)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node->word);
    free(node);
}

// Simple getword function reading words separated by non-alphanumeric chars
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while ((c = getchar()) != EOF && !isalnum(c))
        ;

    if (c == EOF)
        return EOF;

    *w++ = c;
    for (; --lim > 0; w++) {
        c = getchar();
        if (!isalnum(c)) {
            if (c != EOF)
                ungetc(c, stdin);
            break;
        }
        *w = c;
    }
    *w = '\0';
    return word[0];
}

