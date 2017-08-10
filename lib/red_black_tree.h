#include <stdio.h>
#include "status_codes.h"

typedef enum {
    BLACK  = 0,
    RED    = 1
} rbt_node_color;

typedef struct rbt_node rbt_node;

struct rbt_node {
    rbt_node        *left;
    rbt_node        *right;
    rbt_node_color  color;
    char            *key;
    void            *val;
};

typedef struct {
    rbt_node *root;
    size_t cnt;
} rbt;

rbt_node * rbt_node_init(char *key, void *val);
rbt * rbt_init();
status_code rbt_put(rbt *b, char *key, void *val);
size_t rbt_size(rbt *b);
void * rbt_get(rbt *b, char *key);
char * rbt_floor(rbt *b, char *key);
char * rbt_ceiling(rbt *b, char *key);
char * rbt_min(rbt *b);
char * rbt_max(rbt *b);
void rbt_delete_min(rbt *b);
void rbt_delete(rbt *b, char *key);
