#include <stdio.h>
#include "../lib/quick_union_w.h"

/* Compile:
gcc lib/src/quick_union_w.c examples/quick_union_w_demo01.c -o examples/quick_union_w_demo01
*/ 

void quw_dump(quick_union_w *);
void quw_dump_size(quick_union_w *);

int main(int argc, char * argv[])
{
    size_t n, a, b;
    
    n = 10;
    quick_union_w * qu = init_quick_union_w(n);
    printf("Quick find inited with %lu elements\n", n);
    quw_dump(qu);

    a = 4; b = 3;
    quw_union(qu, a, b);
    printf("Union %lu and %lu\n", a, b);
    quw_dump(qu);

    quw_union(qu, 3, 8);
    quw_union(qu, 6, 5);
    quw_union(qu, 9, 4);
    quw_union(qu, 2, 1);
    quw_union(qu, 8, 9);
    quw_union(qu, 5, 0);
    quw_union(qu, 7, 2);
    quw_union(qu, 6, 1);

    printf("Quick find data after few unions:\n");
    quw_dump(qu);

    printf("Size values after few unions:\n");
    quw_dump_size(qu);

    a = 1; b = 0;
    printf("Connected %lu and %lu? %s.\n", a, b, quw_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 2; b = 3;
    printf("Connected %lu and %lu? %s.\n", a, b, quw_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 6; b = 7;
    printf("Connected %lu and %lu? %s.\n", a, b, quw_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 1; b = 9;
    printf("Connected %lu and %lu? %s.\n", a, b, quw_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 1; b = n + 2;
    printf("\n[Test out_of_range exception]\n");
    printf("Result of quw_union(%lu, %lu) is %d\n", a, b, quw_union(qu, a, b));
    printf("Result of quw_connected(%lu, %lu) is %d\n", a, b, quw_connected(qu, a, b));

    return 0;
}

void quw_dump(quick_union_w * qu)
{
    for (size_t i = 0; i < qu->length; i++)
        printf("%lu ", *(qu->data+i));
    printf("\n");
}

void quw_dump_size(quick_union_w * qu)
{
    for (size_t i = 0; i < qu->length; i++)
        printf("%lu ", *(qu->size+i));
    printf("\n");
}