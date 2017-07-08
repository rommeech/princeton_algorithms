#include <stdio.h>
#include "../sort_utils.h"
#include "../sort_selection.h"
#include "../rp_libstr.h"

void selection_sort_asc(void **base, size_t n)
{
    return selection_sort(base, n, (int (*)(void *, void *))cmp_asc);
}

void selection_sort_desc(void **base, size_t n)
{
    return selection_sort(base, n, (int (*)(void *, void *))cmp_desc);
}

void selection_sort(void **base, size_t n, int (*comp)(void *, void *))
{
    size_t i, j, k;
    for(i = 0; i < n-1; i++) {
        k = i;
        for (j = i+1; j < n; j++) {
            if ((*comp)(base[k], base[j]) > 0) {
                k = j;
            }
        }
        swap(base, k, i);
    }
}
