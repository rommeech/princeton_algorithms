#include <stdio.h>
#include "status_codes.h"

void heap_sort(void **base, size_t n, int (*comp)(void *, void *));
void heap_sort_asc(void **base, size_t n);
void heap_sort_desc(void **base, size_t n);
