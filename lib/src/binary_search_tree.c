#include <stdio.h>
#include <stdlib.h>
#include "../binary_search_tree.h"
#include "../sort_utils.h"

/*
gcc lib/src/sort_utils.c lib/src/binary_search_tree.c \
    -o bin/test/binary_search_tree
./bin/test/bst < data/pokemons200dbl.txt
*/

static size_t _bst_size(bst_node *x);
static bst_node * _bst_put        (bst_node *x, char *key, void *val);
static bst_node * _bst_floor      (bst_node *x, char *key);
static bst_node * _bst_ceiling    (bst_node *x, char *key);
static bst_node * _bst_min        (bst_node *x);
static bst_node * _bst_max        (bst_node *x);
static bst_node * _bst_delete_min (bst_node *x);
static bst_node * _bst_delete     (bst_node *x, char *key);

/* int main()
{
} */

bst_node * bst_node_init(char *key, void *val)
{
    bst_node *n = (bst_node *)malloc(sizeof(bst_node));
    if (n == NULL)
        return NULL;
    n->key   = key;
    n->val   = val;
    n->right = NULL;
    n->left  = NULL;
    n->count = 1;
    return n;
}

bst * bst_init()
{
    bst *b = (bst *)malloc(sizeof(bst));
    if (b == NULL)
        return NULL;
    b->cnt  = 0;
    b->root = NULL;
    return b;
}

/*
status_code bst_put(bst *b, char *key, void *val)
{
    bst_node n = b->root;

    if (n == NULL) {
        b->root = bst_node_init(key, val);
    }
    else {
        while (1) {
            if (cmp_str(n->key, key) > 0)
                if (n->right == NULL) {
                    n->right = bst_node_init(key, val);
                    return OK;
                }
                else
                    n = n->right;
            else if (cmp_str(n->key, key) < 0)
                if (n->left == NULL) {
                    n->left = bst_node_init(key, val);
                    return OK;
                }
                else
                    n = n->left;
            else {
                n->val = val;
                return OK;
            }
        }
    }
    
    return OK;
}
*/

/* PUT: clever, but tricky recursive implementation from Princeton's guys */

status_code bst_put(bst *b, char *key, void *val)
{
    b->root = _bst_put(b->root, key, val);
    return OK;
}

static bst_node * _bst_put(bst_node *x, char *key, void *val)
{
    if (x == NULL)
        return bst_node_init(key, val);
    
    int cmp_res = cmp_str(x->key, key);
    
    if      (cmp_res < 0) x->right = _bst_put(x->right, key, val);
    else if (cmp_res > 0) x->left  = _bst_put(x->left , key, val);
    else                  x->val   = val;
    x->count = 1 + _bst_size(x->right) + _bst_size(x->left);
    return x;
}

size_t bst_size(bst *b)
{
    return _bst_size(b->root);
}

static size_t _bst_size(bst_node *x)
{
    if (x == NULL) return 0;
    return x->count;
}

void * bst_get(bst *b, char *key)
{
    bst_node *x = b->root;
    while (x != NULL) {
        int cmp_res = cmp_str(x->key, key);
        if      (cmp_res < 0) x = x->right;
        else if (cmp_res > 0) x = x->left;
        else                  return x->val;
    }
    return NULL;
}

char * bst_floor(bst *b, char *key)
{
    bst_node *x = _bst_floor(b->root, key);
    if (x == NULL) return NULL;
    return x->key;
}

static bst_node * _bst_floor(bst_node *x, char *key)
{
    if (x == NULL) return NULL;
    int cmp_res = cmp_str(x->key, key);
    //printf("_bst_floor for %s, key=%s, cmp_res=%d\n", x->key, key, cmp_res);
    if (cmp_res == 0) return x;
    if (cmp_res > 0)  return _bst_floor(x->left, key);
    bst_node *k = _bst_floor(x->right, key);
    if (k != NULL) return k;
    else           return x;
};

char * bst_ceiling(bst *b, char *key)
{
    bst_node *x = _bst_ceiling(b->root, key);
    if (x == NULL) return NULL;
    return x->key;
}

static bst_node * _bst_ceiling(bst_node *x, char *key)
{
    if (x == NULL) return NULL;
    int cmp_res = cmp_str(x->key, key);
    //printf("_bst_ceiling for %s, key=%s, cmp_res=%d\n", x->key, key, cmp_res);
    if (cmp_res == 0) return x;
    if (cmp_res < 0)  return _bst_ceiling(x->right, key);
    bst_node *k = _bst_ceiling(x->left, key);
    if (k != NULL) return k;
    else           return x;
};

char * bst_min(bst *b)
{
    bst_node *x = _bst_min(b->root);
    if (x == NULL) return NULL;
    return x->key;
}

bst_node * _bst_min(bst_node *x)
{
    if (x == NULL)       return NULL;
    if (x->left == NULL) return x;
    return _bst_min(x->left);
}

char * bst_max(bst *b)
{
    bst_node *x = _bst_max(b->root);
    if (x == NULL) return NULL;
    return x->key;
}

bst_node * _bst_max(bst_node *x)
{
    if (x == NULL)       return NULL;
    if (x->right == NULL) return x;
    return _bst_max(x->right);
}

void bst_delete_min(bst *b)
{
    b->root = _bst_delete_min(b->root);
}

bst_node * _bst_delete_min(bst_node *x)
{
    if (x == NULL) return NULL;
    if (x->left == NULL) return x->right;
    x->left = _bst_delete_min(x->left);
    x->count = 1 + _bst_size(x->left) + _bst_size(x->right);
    return x;
}

void bst_delete(bst *b, char *key)
{
    b->root = _bst_delete(b->root, key);
}

static bst_node * _bst_delete(bst_node *x, char *key)
{
    if (x == NULL)
        return NULL;

    int cmp_res = cmp_str(x->key, key);
    
    if      (cmp_res < 0) x->right = _bst_delete(x->right, key);
    else if (cmp_res > 0) x->left  = _bst_delete(x->left, key);
    else {
        if      (x->right == NULL) return x->left;
        else if (x->left  == NULL) return x->right;
        
        bst_node *k = x;
        x = _bst_min(k->right);
        x->right = _bst_delete_min(k->right);
        x->left  = k->left;
    }
    x->count = 1 + _bst_size(x->left) + _bst_size(x->right);
    return x;
}
