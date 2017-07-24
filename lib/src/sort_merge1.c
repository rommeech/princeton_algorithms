#include <stdio.h>
#include <stdlib.h>
#include "../sort_utils.h"
#include "../sort_merge1.h"

/*
gcc -c lib/src/sort_utils.c lib/src/sort_merge1.c
*/

/*
s  0 1 2 3 4 5 6 7 8 9
s  0 1 2 3 4
s  0 1 2
s  0 1
s  0
s    1
m  0 1
s      2
m  0 1 2
s        3
s          4
m        3 4
m  0 1 2 3 4

*/

static void _sort(
    void **a,
    void **aux,
    size_t start,
    size_t end,
    int (*comp)(void *, void *)
);
static void _merge(
    void **a,
    void **aux,
    size_t start,
    size_t mid,
    size_t end,
    int (*comp)(void *, void *)
);

void merge_sort1_asc(void **a, size_t n)
{
    return merge_sort1(a, n, (int (*)(void *, void *))cmp_asc);
}

void merge_sort1_desc(void **a, size_t n)
{
    return merge_sort1(a, n, (int (*)(void *, void *))cmp_desc);
}

void merge_sort1(void **a, size_t n, int (*comp)(void *, void *))
{
    size_t i;
    //printf("a: lenght=%d, sizeof=%lu, *a=%lu, **a=%lu\n", lenght(a), sizeof(a), sizeof(*a), sizeof(**a));
    //for (i = 0; i < n; i++)
    //    aux[i] = a[i];
    void **aux;
    aux = malloc(n * sizeof(a));
    _sort(a, aux, 0, n-1, comp);
}

static void _sort(
    void **a, void **aux, size_t start, size_t end, int (*comp)(void *, void *)
) {
    /* printf("[S] ");
    for (int i = 0; i <= end; i++)
        if (i >= start) printf("%d ", i);
        else printf("  ");
    printf("\n"); */

    // Only one element in sub-array
    if (start >= end)
        return;

    size_t mid = start + (end - start) / 2;

    _sort(a, aux, start, mid, comp);
    _sort(a, aux, mid+1, end, comp);
    _merge(a, aux, start, mid, end, comp);
}

static void _merge(
    void **a,
    void **aux,
    size_t start,
    size_t mid,
    size_t end,
    int (*comp)(void *, void *)
) {
    /* printf("[M] ");
    for (int i = 0; i <= end; i++)
        if (i >= start) printf("%d ", i);
        else printf("  ");
    printf("\n"); */

    size_t s = start;
    size_t e = mid + 1;
    size_t i;

    for (i = start; i <= end; i++)
        aux[i] = a[i];

    for (i = start; i <= end; i++)
    {
        //printf("    s=%lu, m=%lu, e=%lu\n", s, mid, e);
        if      (s > mid)                       a[i] = aux[e++];
        else if (e > end)                       a[i] = aux[s++];
        else if ((*comp)(aux[s], aux[e]) > 0)   a[i] = aux[e++];
        else                                    a[i] = aux[s++];
    }
}
