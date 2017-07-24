#include <stdio.h>
#include "status_codes.h"

void merge_sort1(void **base, size_t n, int (*comp)(void *, void *));
void merge_sort1_asc(void **base, size_t n);
void merge_sort1_desc(void **base, size_t n);
