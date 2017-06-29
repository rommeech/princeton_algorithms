#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../deque_str.h"
#include "../rp_libstr.h"

/*
gcc lib/rp_libstr.o lib/src/deque_str.c -o bin/test/deque_str
./bin/test/deque_str
*/

int main()
{
    int i;
    char *s1, *s2;
    srand(time(NULL));

    deq_str *d = deq_str_init();

/*
    for (i = 0; i < 10; i++) {
        sprintf(s1, "str%d", i);
        printf(
            "add_first %s, is_empty=%s, size=%lu\n",
            s1,
            deq_str_is_empty(d) == TRUE ? "TRUE" : "FALSE",
            deq_str_size(d)
        );
        deq_str_add_first(d, s1);
    }

    for (i = 0; i < 11; i++) {
        s2 = deq_str_remove_last(d);
        printf(
            "remove_last %s, is_empty=%s, size=%lu\n",
            s2,
            deq_str_is_empty(d) == TRUE ? "TRUE" : "FALSE",
            deq_str_size(d)
        );
    }
*/

    for (i = 0; i < 10; i++) {
        if (rand()%2 == 0) {
            sprintf(s1, "str_first_%d", i);
            deq_str_add_first(d, s1);
        }
        else {
            sprintf(s1, "str_last_%d", i);
            deq_str_add_last(d, s1);
        }
        printf(
            "add %s, is_empty=%s, size=%lu\n",
            s1,
            deq_str_is_empty(d) == TRUE ? "TRUE" : "FALSE",
            deq_str_size(d)
        );
    }

    s2 = (char *) malloc(80 * sizeof(char));
    for (i = 0; i < 11; i++) {
        if (rand()%2 == 0) {
            sprintf(s2, "last_%s", deq_str_remove_last(d));
        }
        else {
            sprintf(s2, "first_%s", deq_str_remove_first(d));
        }
        printf(
            "remove %s, is_empty=%s, size=%lu\n",
            s2,
            deq_str_is_empty(d) == TRUE ? "TRUE" : "FALSE",
            deq_str_size(d)
        );
    }

    return 0;
}

deq_str_node * deq_str_node_init(char * value)
{
    deq_str_node *n = (deq_str_node *) malloc(sizeof(deq_str_node));
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

deq_str * deq_str_init()
{
    deq_str *d;
    d = (deq_str *) malloc(sizeof(deq_str));
    if (d == NULL)
        return NULL;
    d->size = 0;
    return d;
}

status_code deq_str_add_first(deq_str *d, char *value)
{
    deq_str_node *n = deq_str_node_init(value);
    if (n == NULL)
        return OUT_OF_MEMORY;
    
    if (d->size > 0) {
        d->first->prev = n;
        n->next = d->first;
    }
    else {
        d->last = n;
    }
    
    d->size++;
    d->first = n;

    return OK;
}

status_code deq_str_add_last(deq_str *d, char *value)
{
    deq_str_node *n = deq_str_node_init(value);
    if (n == NULL)
        return OUT_OF_MEMORY;
    
    if (d->size > 0) {
        d->last->next = n;
        n->prev = d->last;
    }
    else {
        d->first = n;
    }
    
    d->size++;
    d->last = n;

    return OK;
}

char * deq_str_remove_first(deq_str *d)
{
    if (d->size == 0)
        return NULL;
    
    deq_str_node *first = d->first;
    char *value = (char *) malloc(sizeof(char) * strlen(first->item));
    if (value != NULL)
        str_copy(value, first->item);
    d->first = first->next;
    //d->first->prev = NULL;
    d->size--;
    free(first);
    return value;
}

char * deq_str_remove_last(deq_str *d)
{
    if (d->size == 0)
        return NULL;
    
    deq_str_node *last = d->last;
    char *value = (char *) malloc(sizeof(char) * strlen(last->item));
    if (value != NULL)
        str_copy(value, last->item);
    d->last = last->prev;
    //d->last->next = NULL;
    d->size--;
    free(last);
    return value;
}

status_code deq_str_is_empty(deq_str *d)
{
    return d->size == 0 ? TRUE : FALSE;
}

size_t deq_str_size(deq_str *d)
{
    return d->size;
}

