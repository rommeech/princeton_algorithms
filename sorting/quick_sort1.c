#include <stdio.h>
#include <stdlib.h>
#include "../lib/rp_io.h"
#include "../lib/sort_quick1.h"

/*
gcc lib/src/rp_io.c lib/src/rp_libstr.c lib/src/sort_utils.c \
    lib/src/sort_quick1.c sorting/quick_sort1.c lib/src/shuffle.c \
    -o bin/test/quick_sort
./bin/test/quick_sort < bin/test/pokemons10.txt
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

    //quick_sort1_asc((void **)data, n);
    quick_sort1_desc((void **)data, n);

    printf("[After sorting]\n");
    print_str_array(data, n, col_width, col_num);
}
