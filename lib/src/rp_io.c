#include <stdio.h>
#include "../rp_io.h"
#include "../rp_libstr.h"

void print_str_array(char **s, size_t n, size_t col_width, size_t col_num)
{
    size_t i, j, k, col_height;
    col_height = (n + col_num - 1) / col_num;
    for (i = 0; i < col_height; i++) {
        for (j = 0; j < col_num; j++) {
            k = i + j * col_height;
            if (k < n) {
                printf("%3lu. ", k);
                printf("%-*s", (int)col_width, s[k]);
            }
        }
        printf("\n");
    }
}

char ** read_str_array(size_t *n, size_t *max_str_len)
{
    size_t l;
    char **data;
    char *s = (char *) malloc(sizeof(char) * 256);
    *n = 0;
    while (scanf("%s", s) == 1) {
        l = str_len(s);
        if (*max_str_len < l) *max_str_len = l;
        data[*n] = (char *) malloc(sizeof(char) * l);
        str_copy(data[*n], s);
        (*n)++;
    }
    return data;
}