#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../lib/red_black_tree.h"
#include "../lib/rp_io.h"
#include "../lib/shuffle.h"
#include "../lib/rp_libstr.h"

/*
gcc lib/src/sort_utils.c lib/src/rp_libstr.c lib/src/rp_io.c \
    lib/src/shuffle.c lib/src/red_black_tree.c trees/rbt.c \
    -o bin/test/rbt
./bin/test/rbt < data/abc.txt
./bin/test/rbt < data/abc.txt
./bin/test/rbt < data/pokemons153dbl.txt
./bin/test/rbt < data/pokemons200dbl.txt

*/

int main()
{
    size_t i, n, cw;
    
    char **data = read_str_array(&n, &cw);
    shuffle((void **)data, n);

    rbt *b = rbt_init();
    for (i = 0; i < n; i++) {
        rbt_put(b, data[i], data[i]);
    }

    for (i = 0; i < 10; i++)
        printf("%s => %s\n", data[i], rbt_get(b, data[i]));
    
    printf("min=%s\n", rbt_min(b));
    printf("max=%s\n", rbt_max(b));

    printf("floor of M is %s\n", rbt_floor(b, "M"));
    printf("ceiling of M is %s\n", rbt_ceiling(b, "M"));

    printf("deleting %s...\n", rbt_floor(b, "M"));
    rbt_delete(b, rbt_floor(b, "M"));

    printf("deleting %s...\n", rbt_ceiling(b, "M"));
    rbt_delete(b, rbt_ceiling(b, "M"));

    printf("new floor of M is %s\n", rbt_floor(b, "M"));
    printf("new ceiling of M is %s\n", rbt_ceiling(b, "M"));

    printf("done\n");

    return 0;
}