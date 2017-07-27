#include <stdio.h>
#include "status_codes.h"

/* Dijkstra 3-way partitioning quick sort */

void quick_sort3w(void **base, size_t n, int (*comp)(void *, void *));
void quick_sort3w_asc(void **base, size_t n);
void quick_sort3w_desc(void **base, size_t n);
