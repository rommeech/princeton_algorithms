#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/binary_heap.h"
#include "../lib/rp_io.h"
#include "../lib/sort_utils.h"
#include "../lib/shuffle.h"
#include "../lib/rp_libstr.h"

/*
gcc lib/src/sort_utils.c lib/src/rp_libstr.c lib/src/rp_io.c \
    lib/src/shuffle.c lib/src/binary_heap.c trees/binaryheap.c \
    -o bin/test/binaryheap
./bin/test/binaryheap < data/abc.txt

*/

int main()
{
    int mg;
    char *s;
    size_t i = 0, k = 0, cw, p, level;
    
    char **d = read_str_array(&k, &cw);
    shuffle((void **)d, k);
    
    printf("got %lu strings (cw=%lu):\n", k, cw);
    for (i = 0; i < k; i++)
        printf("%s ", d[i]);
    printf("\n");

    bheap *bh = bheap_init2(sizeof(char *), 1, (int (*)(void *, void *))cmp_desc);
    printf("bh: inited, %lu/%lu/%lu\n", k, bh->n, bh->capa);

    for (i = 0; i < k; i++) {
        bh_insert(bh, d[i]);
    }
    printf("bh: data added %lu/%lu\n", bh->n, bh->capa);

    printf("[Binary heap tree]\n"); 
    mg = 32;
    level = 1;
    for (i = 1; i <= bh->n; i++) {
        p = pow(2, level);
        if (p < i+1) {
            printf("\n");
            level++;
            mg = mg / 2;
        }
        printf("%-*s", mg, bh->data[i]);
    }
    printf("\n");

/*
    printf("[Roots]\n");
    while (bh->n > 0) {
        s = bh_delete_root(bh);
        printf("%s ", s);
    }
    printf("\n");
*/

    return 0;
}