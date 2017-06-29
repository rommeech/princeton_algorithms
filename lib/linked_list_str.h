#include "status_codes.h"

typedef struct ll_str_node ll_str_node;

struct ll_str_node {
    ll_str_node * next;
    char * item;
};

typedef struct {
    ll_str_node * first;
    size_t size;
} lnk_list_str;

lnk_list_str * ll_str_init();
status_code ll_str_push(lnk_list_str *, char * value);
char * ll_str_pop(lnk_list_str *);
status_code ll_str_is_empty(lnk_list_str *);
size_t ll_str_size(lnk_list_str *);

ll_str_node * ll_str_node_init(char * value);
