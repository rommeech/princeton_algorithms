#include <stdio.h>
#include "../sort_utils.h"
#include "../sort_insection.h"
#include "../rp_libstr.h"

void insertion_sort_asc(void **base, size_t n)
{
    return insertion_sort(base, n, (int (*)(void *, void *))cmp_asc);
}

void insertion_sort_desc(void **base, size_t n)
{
    return insertion_sort(base, n, (int (*)(void *, void *))cmp_desc);
}

void insertion_sort(void **base, size_t n, int (*comp)(void *, void *))
{
    size_t i, j;
    for(i = 1; i < n; i++)
        for (j = i; j > 0; j--)
            if ((*comp)(base[j-1], base[j]) > 0)
                swap(base, j-1, j);
}
