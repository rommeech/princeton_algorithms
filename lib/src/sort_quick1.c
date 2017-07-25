#include <stdio.h>
#include <stdlib.h>
#include "../sort_utils.h"
#include "../sort_quick1.h"
#include "../shuffle.h"

/*
gcc -c lib/src/sort_utils.c lib/src/sort_quick1.c
*/

static void _sort(
    void **a, size_t start, size_t end, int (*comp)(void *, void *)
);

static size_t _partition(
    void **a, size_t start, size_t end, int (*comp)(void *, void *)
);

void quick_sort1_asc(void **a, size_t n)
{
    return quick_sort1(a, n, (int (*)(void *, void *))cmp_asc);
}

void quick_sort1_desc(void **a, size_t n)
{
    return quick_sort1(a, n, (int (*)(void *, void *))cmp_desc);
}

void quick_sort1(void **a, size_t n, int (*comp)(void *, void *))
{
    shuffle(a, n);
    _sort(a, 0, n-1, comp);
}

static void _sort(
    void **a, size_t start, size_t end, int (*comp)(void *, void *)
) {
    if (start >= end) return;
    size_t p = _partition(a, start, end, comp);
    if (p > 0)
        _sort(a, start, p-1, comp);
    _sort(a, p+1, end, comp);
}

static size_t _partition(
    void **a, size_t start, size_t end, int (*comp)(void *, void *)
) {
    size_t s = start;
    size_t e = end + 1;

    while(1) {
        while ((*comp)(a[++s], a[start]) < 0) {
            if (s == end)
                break;
        }
        while ((*comp)(a[start], a[--e]) < 0) {
            if (e == start)
                break;
        }
        if (s >= e)
            break;
        swap(a, s, e);
    };

    if (e != start)
        swap(a, e, start);

    return e;
}


