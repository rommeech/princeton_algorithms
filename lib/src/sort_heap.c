#include <stdio.h>
#include "../sort_utils.h"
#include "../sort_heap.h"

static void hs_sink(void **data, size_t n, size_t k, int (*comp)(void *, void *));

void heap_sort_asc(void **base, size_t n)
{
    return heap_sort(base, n, (int (*)(void *, void *))cmp_asc);
}

void heap_sort_desc(void **base, size_t n)
{
    return heap_sort(base, n, (int (*)(void *, void *))cmp_desc);
}

void heap_sort(void **base, size_t n, int (*comp)(void *, void *))
{
    size_t i;
    for (i = n / 2; i >= 1; i--) {
        hs_sink(base, n, i, comp);
    }
    while (n > 1) {
        swap(base, 1, n--);
        hs_sink(base, n, 1, comp);
    }
}

static void hs_sink(void **data, size_t n, size_t k, int (*comp)(void *, void *))
{
    if (k < 1 || k > n)
        return;
    
    size_t j = k*2;
    while (j <= n)
    {
        if (j < n && comp(data[j], data[j+1]) < 0)
            j++;
        if (comp(data[k], data[j]) > 0)
            break;
        swap(data, k, j);
        k = j;
        j *= 2;
    }
}
