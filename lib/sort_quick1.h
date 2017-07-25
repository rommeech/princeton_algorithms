#include <stdio.h>
#include "status_codes.h"

void quick_sort1(void **base, size_t n, int (*comp)(void *, void *));
void quick_sort1_asc(void **base, size_t n);
void quick_sort1_desc(void **base, size_t n);
