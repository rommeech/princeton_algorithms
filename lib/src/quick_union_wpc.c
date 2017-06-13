#include <stdio.h>
#include <stdlib.h>
#include "../quick_union_wpc.h"

/*
Library compilation:
gcc -c lib/src/quick_union_wpc.c -o lib/quick_union_wpc.o

Weighted quick-union
・Modify quick-union to avoid tall trees.
・Keep track of size of each tree (number of objects).
・Balance by linking root of smaller tree to root of larger tree.

Path compression: just after computing the root of p,
set the id of each examined node to point to that root.

Data structure
Interpretation: id[i] is parent of i.
Root of i is id[id[id[...id[i]...]]].

Maintain extra array sz[i] to count number of objects in the tree rooted at i.
*/

quick_union_wpc * init_quick_union_wpc(size_t length)
{
    size_t i;
    quick_union_wpc * qu = (quick_union_wpc *) malloc(sizeof(quick_union_wpc));
    if (qu == NULL)
        return NULL;
    qu->length = length;
    qu->data = (size_t *) malloc(sizeof(size_t) * qu->length);
    if (qu->data == NULL) {
        free(qu);
        return NULL;
    }
    qu->size = (size_t *) malloc(sizeof(size_t) * qu->length);
    if (qu->size == NULL) {
        free(qu);
        return NULL;
    }
    for (i = 0; i < qu->length; i++) {
        *(qu->data + i) = i;
        *(qu->size + i) = 1;
    }
    return qu;
}

// Get root ID
size_t quwpc_root(quick_union_wpc * qu, size_t a)
{
    // It does not work, refactoring needs!
    //if (a > qu->length)
    //    return OUT_OF_RANGE;
    // Simpler one-pass variant: Make every other node in path point to its
    // grandparent (thereby halving path length).
    while (a != *(qu->data+a)) {
        *(qu->data+a) = *(qu->data+*(qu->data+a));
        a = *(qu->data+a);
    }
    return a;
}

// Union two entities
// To merge components containing p and q, set the id of p's root to the id of q's root.
status_code quwpc_union(quick_union_wpc * qu, size_t a, size_t b)
{
    size_t root_a, root_b;
    if (a > qu->length || b > qu->length)
        return OUT_OF_RANGE;

    if (quwpc_connected(qu, a, b) == FALSE) {
        root_a = quwpc_root(qu, a);
        root_b = quwpc_root(qu, b);

        if (*(qu->size+a) > *(qu->size+b)) {    
            // Size of A is bigget then B's,
            // thus B's root element become A's child element
            // (update ID of B's root to A's root ID)
            *(qu->data+root_b) = root_a;

            // Update size of A's root
            *(qu->size+a) += *(qu->size+b);
        }
        else {
            *(qu->data+root_a) = root_b;
            *(qu->size+b) += *(qu->size+a);
        }
    }
    return TRUE;
}

// Check whether two entities connected
// Two elements are connected if both have the same root ID
status_code quwpc_connected(quick_union_wpc * qu, size_t a, size_t b)
{
    if (a > qu->length || b > qu->length)
        return OUT_OF_RANGE;
    if (a == b)
        return TRUE;
    return quwpc_root(qu, a) == quwpc_root(qu, b) ? TRUE : FALSE;
}
