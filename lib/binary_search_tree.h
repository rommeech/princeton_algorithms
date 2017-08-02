#include <stdio.h>
#include "status_codes.h"

typedef struct bst_node bst_node;

struct bst_node {
    bst_node *left;
    bst_node *right;
    size_t count;
    char *key;
    void *val;
};

typedef struct {
    bst_node *root;
    size_t cnt;
} bst;

bst_node * bst_node_init(char *key, void *val);
bst * bst_init();
status_code bst_put(bst *b, char *key, void *val);
size_t bst_size(bst *b);
void * bst_get(bst *b, char *key);
char * bst_floor(bst *b, char *key);
char * bst_ceiling(bst *b, char *key);
char * bst_min(bst *b);
char * bst_max(bst *b);
void bst_delete_min(bst *b);
void bst_delete(bst *b, char *key);
