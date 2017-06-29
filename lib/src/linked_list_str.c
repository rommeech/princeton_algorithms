#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linked_list_str.h"
#include "../rp_libstr.h"

/*
gcc lib/rp_libstr.o lib/src/linked_list_str.c -o bin/test/linked_list
./bin/test/linked_list
*/

int main()
{
    int i;
    char *s1, *s2;

    lnk_list_str *l = ll_str_init();

    for (i = 0; i < 10; i++) {
        sprintf(s1, "str%d", i);
        printf(
            "push %s, is_empty=%s, size=%lu\n",
            s1,
            ll_str_is_empty(l) == TRUE ? "TRUE" : "FALSE",
            ll_str_size(l)
        );
        ll_str_push(l, s1);
    }

    for (i = 0; i < 11; i++) {
        s2 = ll_str_pop(l);
        printf(
            "pop %s, is_empty=%s, size=%lu\n",
            s2,
            ll_str_is_empty(l) == TRUE ? "TRUE" : "FALSE",
            ll_str_size(l)
        );
    }

    return 0;
}

ll_str_node * ll_str_node_init(char * value)
{
    ll_str_node *n = (ll_str_node *) malloc(sizeof(ll_str_node));
    if (n == NULL)
        return NULL;    
    n->item = (char *) malloc(sizeof(char) *  strlen(value));
    if (n->item == NULL) {
        free(n);
        return NULL;
    }
    str_copy(n->item, value);
    return n;
}

lnk_list_str * ll_str_init()
{
    lnk_list_str *l;
    l = (lnk_list_str *) malloc(sizeof(lnk_list_str));
    if (l == NULL)
        return NULL;
    l->size = 0;
    return l;
}

status_code ll_str_push(lnk_list_str *l, char *value)
{
    ll_str_node *n = ll_str_node_init(value);
    if (n == NULL)
        return OUT_OF_MEMORY;
    
    if (l->size > 0)
        n->next = l->first;
    
    l->size++;
    l->first = n;

    return OK;
}

char * ll_str_pop(lnk_list_str * l)
{
    if (l->size == 0)
        return NULL;
    
    ll_str_node *first = l->first;
    char *value = (char *) malloc(sizeof(char) * strlen(first->item));
    if (value != NULL)
        str_copy(value, first->item);
    l->first = first->next;
    l->size--;
    free(first);
    return value;
}

status_code ll_str_is_empty(lnk_list_str * l)
{
    return l->size == 0 ? TRUE : FALSE;
}

size_t ll_str_size(lnk_list_str * l)
{
    return l->size;
}

