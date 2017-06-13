#include <stdio.h>
#include "../lib/quick_union.h"

/* Compile:
gcc lib/src/quick_union.c examples/quick_union_demo01.c -o examples/quick_union_demo01
*/ 

void qu_dump(quick_union *);

int main(int argc, char * argv[])
{
    size_t n, a, b;
    
    n = 10;
    quick_union * qu = init_quick_union(n);
    printf("Quick find inited with %lu elements\n", n);
    qu_dump(qu);

    a = 4; b = 3;
    qu_union(qu, a, b);
    printf("Union %lu and %lu\n", a, b);
    qu_dump(qu);

    qu_union(qu, 3, 8);
    qu_union(qu, 6, 5);
    qu_union(qu, 9, 4);
    qu_union(qu, 2, 1);
    qu_union(qu, 8, 9);
    qu_union(qu, 5, 0);
    qu_union(qu, 7, 2);
    qu_union(qu, 6, 1);

    printf("Quick find data after few unions:\n");
    qu_dump(qu);

    a = 1; b = 0;
    printf("Connected %lu and %lu? %s.\n", a, b, qu_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 2; b = 3;
    printf("Connected %lu and %lu? %s.\n", a, b, qu_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 6; b = 7;
    printf("Connected %lu and %lu? %s.\n", a, b, qu_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 1; b = 9;
    printf("Connected %lu and %lu? %s.\n", a, b, qu_connected(qu, a, b) == TRUE ? "Yes" : "No");

    a = 1; b = n + 2;
    printf("\n[Test out_of_range exception]\n");
    printf("Result of qu_union(%lu, %lu) is %d\n", a, b, qu_union(qu, a, b));
    printf("Result of qu_connected(%lu, %lu) is %d\n", a, b, qu_connected(qu, a, b));

    return 0;
}

void qu_dump(quick_union * qu)
{
    for (size_t i = 0; i < qu->length; i++)
        printf("%lu ", *(qu->data+i));
    printf("\n");
}