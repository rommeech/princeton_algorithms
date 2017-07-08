#include <stdio.h>
#include "status_codes.h"

void selection_sort(void **base, size_t n, int (*comp)(void *, void *));
void selection_sort_asc(void **base, size_t n);
void selection_sort_desc(void **base, size_t n);
