#include <stdio.h>
#include "status_codes.h"

void insertion_sort(void **base, size_t n, int (*comp)(void *, void *));
void insertion_sort_asc(void **base, size_t n);
void insertion_sort_desc(void **base, size_t n);
