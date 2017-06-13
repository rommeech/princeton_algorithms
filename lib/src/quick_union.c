#include <stdio.h>
#include <stdlib.h>
#include "../quick_union.h"

/* Lib compile command:
gcc -c lib/src/quick_union.c -o lib/quick_union.o
*/ 

// Init
// Data structure
// Interpretation: id[i] is parent of i.
// Root of i is id[id[id[...id[i]...]]].
quick_union * init_quick_union(size_t length)
{
    size_t i;
    quick_union * qu = (quick_union *) malloc(sizeof(quick_union));
    if (qu == NULL)
        return NULL;
    qu->length = length;
    qu->data = (size_t *) malloc(sizeof(size_t) * qu->length);
    if (qu->data == NULL) {
        free(qu);
        return NULL;
    }
    for (i = 0; i < qu->length; i++) {
        *(qu->data + i) = i;
    }
    return qu;
}

// Get root ID
size_t qu_root(quick_union * qu, size_t a)
{
    // It does not work, refactoring needs!
    //if (a > qu->length)
    //    return OUT_OF_RANGE;
    for (; a != *(qu->data+a); a = *(qu->data+a));
    return a;
}

// Union two entities
// To merge components containing p and q, set the id of p's root to the id of q's root.
rt_code qu_union(quick_union * qu, size_t a, size_t b)
{
    size_t root_a, root_b;
    if (a > qu->length || b > qu->length)
        return OUT_OF_RANGE;
    if (qu_connected(qu, a, b) == FALSE) {
        root_a = qu_root(qu, a);
        root_b = qu_root(qu, b);
        *(qu->data+root_a) = root_b;
    }
    return TRUE;
}

// Check whether two entities connected
// Two elements are connected if both have the same root ID
rt_code qu_connected(quick_union * qu, size_t a, size_t b)
{
    if (a > qu->length || b > qu->length)
        return OUT_OF_RANGE;
    if (a == b)
        return TRUE;
    return qu_root(qu, a) == qu_root(qu, b) ? TRUE : FALSE;
}
