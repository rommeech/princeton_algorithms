#include <stdio.h>
#include <stdlib.h>
#include "../lib/rp_libstr.h"
#include "../lib/sort_selection.h"

/*
gcc lib/src/rp_libstr.c lib/src/sort_utils.c lib/src/sort_selection.c sorting/selection_sort.c -o bin/test/selection_sort
./bin/test/selection_sort < bin/test/pokemons70.txt
*/

void print_array(char **s, int n, int col_width, int col_num);

int main()
{
    // Init
    char **data;
    char *s = (char *) malloc(sizeof(char) * 256);
    int i = 0, n = 0, col_width = 0, col_num = 0, l = 0;
    
    // Read strings from input
    while (scanf("%s", s) == 1) {
        l = str_len(s);
        if (col_width < l) col_width = l;
        data[i] = (char *) malloc(sizeof(char) * l);
        str_copy(data[i], s);
        i++;
    }
    n = i;
    col_width += 2;
    col_num = 80 / col_width;

    printf("[Before sorting]\n");
    print_array(data, n, col_width, col_num);

    //selection_sort((void **)data, n, (int (*)(void *, void *))cmp_str);
    selection_sort_asc((void **)data, n);
    //selection_sort_desc((void **)data, n);

    printf("[After sorting]\n");
    print_array(data, n, col_width, col_num);
}

void print_array(char **s, int n, int col_width, int col_num)
{
    int i, j, k, col_height;
    col_height = (n + col_num - 1) / col_num;
    for (i = 0; i < col_height; i++) {
        for (j = 0; j < col_num; j++) {
            k = i + j * col_height;
            if (k < n) {
                printf("%-*s", col_width, s[k]);
            }
        }
        printf("\n");
    }
}