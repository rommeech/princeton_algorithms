#include <stdio.h>
#include <stdlib.h>
#include "../lib/rp_io.h"
#include "../lib/sort_quick3w.h"

/*
gcc lib/src/rp_io.c lib/src/rp_libstr.c lib/src/sort_utils.c \
    lib/src/sort_quick3w.c sorting/quick_sort3w.c lib/src/shuffle.c \
    -o bin/test/quick_sort
./bin/test/quick_sort < data/pokemons15dbl.txt
*/

int main()
{
    // Init
    size_t i = 0, n = 0, col_width = 0, col_num = 0, l = 0;
    char **data = read_str_array(&n, &col_width);
    col_width += 2;
    col_num = 80 / col_width;

    printf("[Before sorting]\n");
    print_str_array(data, n, col_width, col_num);

    //quick_sort3w_asc((void **)data, n);
    quick_sort3w_desc((void **)data, n);

    printf("[After sorting]\n");
    print_str_array(data, n, col_width, col_num);
}
