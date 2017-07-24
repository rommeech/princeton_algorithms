#include <stdio.h>
#include "../sort_utils.h"
#include "../sort_shell.h"
#include "../rp_libstr.h"

void shell_sort_asc(void **base, size_t n)
{
    return shell_sort(base, n, (int (*)(void *, void *))cmp_asc);
}

void shell_sort_desc(void **base, size_t n)
{
    return shell_sort(base, n, (int (*)(void *, void *))cmp_desc);
}

void shell_sort(void **base, size_t n, int (*comp)(void *, void *))
{
    size_t i, j, k = 1;
    while (k < n / 3) k = k * 3 + 1;
    //printf("k=%lu, n=%lu\n", k, n);
    do {
        for(i = k; i < n; i++) {
            for (j = i; j >= k && (*comp)(base[j-k], base[j]) > 0; j -= k) {
                swap(base, j-k, j);
            }
        }
        k /= 3;
    } while (k >= 1);
}
