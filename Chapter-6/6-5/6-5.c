#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol table node struct (linked list)
struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

struct nlist *lookup(const char *name);
struct nlist *install(const char *name, const char *defn);

// Head of the symbol table linked list
static struct nlist *hashtab = NULL;

// lookup function (simple linear search)
struct nlist *lookup(const char *name) {
    struct nlist *np = hashtab;
    while (np != NULL) {
        if (strcmp(name, np->name) == 0)
            return np;
        np = np->next;
    }
    return NULL;
}

// install function adds name-defn to front of list (simplified)
struct nlist *install(const char *name, const char *defn) {
    struct nlist *np = lookup(name);
    if (np == NULL) {
        np = malloc(sizeof(struct nlist));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        np->next = hashtab;
        hashtab = np;
    } else {
        free(np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

// undef function to remove name and its definition from table
int undef(const char *name) {
    struct nlist *np = hashtab;
    struct nlist *prev = NULL;

    while (np != NULL) {
        if (strcmp(np->name, name) == 0) {
            if (prev == NULL) {
                hashtab = np->next; // Remove head
            } else {
                prev->next = np->next; // Remove middle or last
            }
            free(np->name);
            free(np->defn);
            free(np);
            return 1; // successful removal
        }
        prev = np;
        np = np->next;
    }
    return 0; // name not found
}

// Example test main
int main() {
    install("foo", "bar");
    install("baz", "qux");

    printf("Before undef:\n");
    struct nlist *p = hashtab;
    while (p) {
        printf("%s = %s\n", p->name, p->defn);
        p = p->next;
    }

    undef("foo");

    printf("\nAfter undef:\n");
    p = hashtab;
    while (p) {
        printf("%s = %s\n", p->name, p->defn);
        p = p->next;
    }

    return 0;
}

