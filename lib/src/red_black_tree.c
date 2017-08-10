#include <stdio.h>
#include <stdlib.h>
#include "../red_black_tree.h"
#include "../sort_utils.h"
#include "../status_codes.h"

/*
gcc lib/src/sort_utils.c lib/src/red_black_tree.c -o bin/test/red_black_tree
*/

//static size_t _size(rbt_node *x);
static rbt_node * _rotate_left  (rbt_node *);
static rbt_node * _rotate_right (rbt_node *);
static void       _flip_colors  (rbt_node *);
static boolean    _is_red       (rbt_node *);
static rbt_node * _put          (rbt_node *x, char *key, void *val);
static rbt_node * _floor        (rbt_node *x, char *key);
static rbt_node * _ceiling      (rbt_node *x, char *key);
static rbt_node * _min          (rbt_node *x);
static rbt_node * _max          (rbt_node *x);
static rbt_node * _delete_min   (rbt_node *x);
static rbt_node * _delete       (rbt_node *x, char *key);

rbt_node * rbt_node_init(char *key, void *val)
{
    rbt_node *n = (rbt_node *)malloc(sizeof(rbt_node));
    if (n == NULL)
        return NULL;
    n->key   = key;
    n->val   = val;
    n->right = NULL;
    n->left  = NULL;
    n->color = RED;
    //n->count = 1;
    return n;
}

rbt * rbt_init()
{
    rbt *b = (rbt *)malloc(sizeof(rbt));
    if (b == NULL)
        return NULL;
    b->cnt  = 0;
    b->root = NULL;
    return b;
}

/* PUT: tricky recursive implementation from Princeton's cource */

status_code rbt_put(rbt *b, char *key, void *val)
{
    b->root = _put(b->root, key, val);
    return OK;
}

static rbt_node * _put(rbt_node *x, char *key, void *val)
{
    if (x == NULL)
        return rbt_node_init(key, val);
    
    int cmp_res = cmp_str(x->key, key);
    
    if      (cmp_res < 0) x->right = _put(x->right, key, val);
    else if (cmp_res > 0) x->left  = _put(x->left , key, val);
    else                  x->val   = val;
    
    if (_is_red(x->right) && !_is_red(x->left))     x = _rotate_left(x);
    if (_is_red(x->left) && _is_red(x->left->left)) x = _rotate_right(x);
    if (_is_red(x->left) && _is_red(x->right))          _flip_colors(x);

    
    //x->count = 1 + _size(x->right) + _size(x->left);
    
    return x;
}

/*
size_t rbt_size(rbt *b)
{
    return _size(b->root);
}

static size_t _size(rbt_node *x)
{
    if (x == NULL) return 0;
    return x->count;
}
*/

void * rbt_get(rbt *b, char *key)
{
    rbt_node *x = b->root;
    while (x != NULL) {
        int cmp_res = cmp_str(x->key, key);
        if      (cmp_res < 0) x = x->right;
        else if (cmp_res > 0) x = x->left;
        else                  return x->val;
    }
    return NULL;
}

char * rbt_floor(rbt *b, char *key)
{
    rbt_node *x = _floor(b->root, key);
    if (x == NULL) return NULL;
    return x->key;
}

static rbt_node * _floor(rbt_node *x, char *key)
{
    if (x == NULL) return NULL;
    int cmp_res = cmp_str(x->key, key);
    //printf("_floor for %s, key=%s, cmp_res=%d\n", x->key, key, cmp_res);
    if (cmp_res == 0) return x;
    if (cmp_res > 0)  return _floor(x->left, key);
    rbt_node *k = _floor(x->right, key);
    if (k != NULL) return k;
    else           return x;
};

char * rbt_ceiling(rbt *b, char *key)
{
    rbt_node *x = _ceiling(b->root, key);
    if (x == NULL) return NULL;
    return x->key;
}

static rbt_node * _ceiling(rbt_node *x, char *key)
{
    if (x == NULL) return NULL;
    int cmp_res = cmp_str(x->key, key);
    //printf("_ceiling for %s, key=%s, cmp_res=%d\n", x->key, key, cmp_res);
    if (cmp_res == 0) return x;
    if (cmp_res < 0)  return _ceiling(x->right, key);
    rbt_node *k = _ceiling(x->left, key);
    if (k != NULL) return k;
    else           return x;
};

char * rbt_min(rbt *b)
{
    rbt_node *x = _min(b->root);
    if (x == NULL) return NULL;
    return x->key;
}

rbt_node * _min(rbt_node *x)
{
    if (x == NULL)       return NULL;
    if (x->left == NULL) return x;
    return _min(x->left);
}

char * rbt_max(rbt *b)
{
    rbt_node *x = _max(b->root);
    if (x == NULL) return NULL;
    return x->key;
}

rbt_node * _max(rbt_node *x)
{
    if (x == NULL)       return NULL;
    if (x->right == NULL) return x;
    return _max(x->right);
}

void rbt_delete_min(rbt *b)
{
    b->root = _delete_min(b->root);
}

rbt_node * _delete_min(rbt_node *x)
{
    if (x == NULL) return NULL;
    if (x->left == NULL) return x->right;
    x->left = _delete_min(x->left);
    //x->count = 1 + _size(x->left) + _size(x->right);
    return x;
}

void rbt_delete(rbt *b, char *key)
{
    b->root = _delete(b->root, key);
}

static rbt_node * _delete(rbt_node *x, char *key)
{
    if (x == NULL)
        return NULL;

    int cmp_res = cmp_str(x->key, key);
    
    if      (cmp_res < 0) x->right = _delete(x->right, key);
    else if (cmp_res > 0) x->left  = _delete(x->left, key);
    else {
        if      (x->right == NULL) return x->left;
        else if (x->left  == NULL) return x->right;
        
        rbt_node *k = x;
        x = _min(k->right);
        x->right = _delete_min(k->right);
        x->left  = k->left;
    }
    //x->count = 1 + _size(x->left) + _size(x->right);
    return x;
}

static rbt_node * _rotate_left  (rbt_node *h)
{
    rbt_node *x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

static rbt_node * _rotate_right (rbt_node *h)
{
    rbt_node *x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

static void _flip_colors(rbt_node *h)
{
    h->left->color  = BLACK;
    h->right->color = BLACK;
    h->color        = RED;
}

static boolean _is_red(rbt_node *h)
{
    if (h != NULL && h->color == RED) return TRUE;
    return FALSE;
}