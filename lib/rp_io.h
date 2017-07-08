#include <stdio.h>
#include <stdlib.h>

#ifndef RP_IO
#define RP_IO

void print_str_array(char **s, size_t n, size_t col_width, size_t col_num);
char ** read_str_array(size_t *n, size_t *max_str_len);

#endif