#include <stdio.h>
#include "../lib/quick_union_wpc.h"

/* Compile:
gcc lib/src/quick_union_wpc.c examples/quick_union_wpc_demo01.c -o examples/quick_union_wpc_demo01
*/ 

void quwpc_dump(quick_union_wpc *);
void quwpc_dump_size(quick_union_wpc *);

int main(int argc, char * argv[])
{
    size_t n, a, b;
    
    n = 10;
    quick_union_wpc * qu = init_quick_union_wpc(n);
    printf("Quick find inited with %lu elements\n", n);
    quwpc_dump(qu);

    a = 4; b = 3;
    quwpc_union(qu, a, b);
    printf("Union %lu and %lu\n", a, b);
    quwpc_dump(qu);

    quwpc_union(qu, 3, 8);
    quwpc_union(qu, 6, 5);
    quwpc_union(qu, 9, 4);
    quwpc_union(qu, 2, 1);
    quwpc_union(qu, 8, 9);
    quwpc_union(qu, 5, 0);
    quwpc_union(qu, 7, 2);
    quwpc_union(qu, 6, 1);

    printf("Quick find data after few unions:\n");
    quwpc_dump(qu);

    printf("Size values after few unions:\n");
    quwpc_dump_size(qu);

    a = 1; b = 0;
    printf("Connected %lu and %lu? %s.\n", a, b, quwpc_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 2; b = 3;
    printf("Connected %lu and %lu? %s.\n", a, b, quwpc_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 6; b = 7;
    printf("Connected %lu and %lu? %s.\n", a, b, quwpc_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 1; b = 9;
    printf("Connected %lu and %lu? %s.\n", a, b, quwpc_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 1; b = n + 2;
    printf("\n[Test out_of_range exception]\n");
    printf("Result of quwpc_union(%lu, %lu) is %d\n", a, b, quwpc_union(qu, a, b));
    printf("Result of quwpc_connected(%lu, %lu) is %d\n", a, b, quwpc_connected(qu, a, b));

    return 0;
}

void quwpc_dump(quick_union_wpc * qu)
{
    for (size_t i = 0; i < qu->length; i++)
        printf("%lu ", *(qu->data+i));
    printf("\n");
}

void quwpc_dump_size(quick_union_wpc * qu)
{
    for (size_t i = 0; i < qu->length; i++)
        printf("%lu ", *(qu->size+i));
    printf("\n");
}