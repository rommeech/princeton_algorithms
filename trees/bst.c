#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../lib/binary_search_tree.h"
#include "../lib/rp_io.h"
#include "../lib/shuffle.h"
#include "../lib/rp_libstr.h"

/*
gcc lib/src/sort_utils.c lib/src/rp_libstr.c lib/src/rp_io.c \
    lib/src/shuffle.c lib/src/binary_search_tree.c trees/bst.c \
    -o bin/test/bst
./bin/test/bst < data/abc.txt

*/

int main()
{
    size_t i, n, cw;
    
    char **data = read_str_array(&n, &cw);
    shuffle((void **)data, n);

    bst *b = bst_init();
    for (i = 0; i < n; i++) {
        bst_put(b, data[i], data[i]);
    }

    for (i = 0; i < 10; i++)
        printf("%s => %s\n", data[i], bst_get(b, data[i]));
    
    printf("min=%s\n", bst_min(b));
    printf("max=%s\n", bst_max(b));

    printf("floor of M is %s\n", bst_floor(b, "M"));
    printf("ceiling of M is %s\n", bst_ceiling(b, "M"));

    printf("deleting %s...\n", bst_floor(b, "M"));
    bst_delete(b, bst_floor(b, "M"));

    printf("deleting %s...\n", bst_ceiling(b, "M"));
    bst_delete(b, bst_ceiling(b, "M"));

    printf("new floor of M is %s\n", bst_floor(b, "M"));
    printf("new ceiling of M is %s\n", bst_ceiling(b, "M"));

    printf("done\n");

    return 0;
}