#include <stdio.h>
#include <stdlib.h>
#include "../sort_utils.h"
#include "../sort_quick3w.h"
#include "../shuffle.h"

/*
gcc -c lib/src/sort_utils.c lib/src/sort_quick3w.c
*/

static void _sort(void **a, size_t lo, size_t hi, int (*comp)(void *, void *));

void quick_sort3w_asc(void **a, size_t n)
{
    return quick_sort3w(a, n, (int (*)(void *, void *))cmp_asc);
}

void quick_sort3w_desc(void **a, size_t n)
{
    return quick_sort3w(a, n, (int (*)(void *, void *))cmp_desc);
}

void quick_sort3w(void **a, size_t n, int (*comp)(void *, void *))
{
    shuffle(a, n);
    _sort(a, 0, n-1, comp);
}

static void _sort(void **a, size_t lo, size_t hi, int (*comp)(void *, void *))
{
    //printf("_sort: lo=%lu, hi=%lu\n", lo, hi);
    
    if (lo >= hi) return;
    
    void *v = a[lo];
    size_t l = lo;
    size_t h = hi;
    size_t i = lo + 1;
    int cmpres;

    while (i <= h)
    {
        cmpres = (*comp)(v, a[i]);
        if (cmpres < 0) {
            swap(a, i, l);
            i++;
            l++;
        }
        else if (cmpres > 0) {
            swap(a, i, h);
            h--;
        }
        else {
            i++;
        }
    }

    //printf("       l=%lu, h=%lu\n", l, h);

    if (l > 0 && lo < l-1) _sort(a, lo, l-1, comp);
    if (h+1 < hi) _sort(a, h+1, hi, comp);
}
