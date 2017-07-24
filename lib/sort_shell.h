#include <stdio.h>
#include "status_codes.h"

void shell_sort(void **base, size_t n, int (*comp)(void *, void *));
void shell_sort_asc(void **base, size_t n);
void shell_sort_desc(void **base, size_t n);
