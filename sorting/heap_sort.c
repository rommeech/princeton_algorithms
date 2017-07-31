#include <stdio.h>
#include <stdlib.h>
#include "../lib/rp_io.h"
#include "../lib/shuffle.h"
#include "../lib/sort_heap.h"

/*
gcc lib/src/rp_io.c lib/src/shuffle.c lib/src/rp_libstr.c lib/src/sort_utils.c \
    lib/src/sort_heap.c sorting/heap_sort.c -o bin/test/heap_sort
./bin/test/heap_sort < bin/test/pokemons10.txt
*/

int main()
{
    // Init
    size_t i = 0, n = 0, col_width = 0, col_num = 0, l = 0;
    char **d = read_str_array(&n, &col_width);
    char **data = (char **) malloc(sizeof(char *) * (n+1));
    shuffle((void **)d, n);
    data[0] = "---";
    for (i = 0; i < n; i++)
        data[i+1] = d[i];
    col_width += 2;
    col_num = 80 / col_width;

    printf("[Before sorting]\n");
    print_str_array(data, n+1, col_width, col_num);

    //heap_sort_asc((void **)data, n);
    heap_sort_desc((void **)data, n);

    printf("[After sorting]\n");
    print_str_array(data, n+1, col_width, col_num);
}
