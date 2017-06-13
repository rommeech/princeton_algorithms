#include <stdio.h>
#include <stdlib.h>
#include "../quick_find.h"

// Init
quick_find * init_quick_find(size_t length)
{
    size_t i;
    quick_find * qf = (quick_find *) malloc(sizeof(quick_find));
    if (qf == NULL)
        return NULL;
    qf->length = length;
    qf->data = (size_t *) malloc(sizeof(size_t) * qf->length);
    if (qf->data == NULL) {
        free(qf);
        return NULL;
    }
    for (i = 0; i < qf->length; i++) {
        *(qf->data + i) = i;
    }
    return qf;
}

// Union two entities
// TODO: remove debug outputs before go live
rt_code qf_union(quick_find * qf, size_t a, size_t b)
{
    size_t i, qf_a, qf_b;
    //printf("qf_union: a=%lu, qf[a]=%lu, b=%lu, qf[b]=%lu\n", a, *(qf->data+a), b, *(qf->data+b));
    if (a > qf->length || b > qf->length)
        return OUT_OF_RANGE;
    if (qf_connected(qf, a, b) == FALSE) {
        qf_a = *(qf->data+a);
        qf_b = *(qf->data+b);
        for (i = 0; i < qf->length; i++) {
            //printf("qf_union: loop i=%lu, qf[i]=%lu\n", i, *(qf->data+i));
            if (*(qf->data+i) == qf_a)
                *(qf->data+i) = qf_b;
        }
    }
    return TRUE;
}

// Check whether two entities connected
rt_code qf_connected(quick_find * qf, size_t a, size_t b)
{
    if (a > qf->length || b > qf->length)
        return OUT_OF_RANGE;
    return *(qf->data+a) == *(qf->data+b) ? TRUE : FALSE;
}
