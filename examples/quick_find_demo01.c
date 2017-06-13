#include <stdio.h>
#include "../lib/quick_find.h"

/* Compile:
gcc lib/src/quick_find.c examples/quick_find_demo01.c -o examples/quick_find_demo01
*/ 

void qf_dump(quick_find *);

int main(int argc, char * argv[])
{
    size_t n, a, b;
    
    n = 10;
    quick_find * qf = init_quick_find(n);
    printf("Quick find inited with %lu elements\n", n);
    qf_dump(qf);

    a = 4; b = 3;
    qf_union(qf, a, b);
    printf("Union %lu and %lu\n", a, b);
    qf_dump(qf);

    qf_union(qf, 3, 8);
    qf_union(qf, 6, 5);
    qf_union(qf, 9, 4);
    qf_union(qf, 2, 1);
    qf_union(qf, 8, 9);
    qf_union(qf, 5, 0);
    qf_union(qf, 7, 2);
    qf_union(qf, 6, 1);

    printf("Quick find data after few unions:\n");
    qf_dump(qf);

    a = 1; b = 0;
    printf("Connected %lu and %lu? %s.\n", a, b, qf_connected(qf, a, b) == TRUE ? "Yes" : "No");

    a = 2; b = 3;
    printf("Connected %lu and %lu? %s.\n", a, b, qf_connected(qf, a, b) == TRUE ? "Yes" : "No");

    a = 6; b = 7;
    printf("Connected %lu and %lu? %s.\n", a, b, qf_connected(qf, a, b) == TRUE ? "Yes" : "No");

    a = 1; b = 9;
    printf("Connected %lu and %lu? %s.\n", a, b, qf_connected(qf, a, b) == TRUE ? "Yes" : "No");

    a = 1; b = n + 2;
    printf("\n[Test out_of_range exception]\n");
    printf("Result of qf_union(%lu, %lu) is %d\n", a, b, qf_union(qf, a, b));
    printf("Result of qf_connected(%lu, %lu) is %d\n", a, b, qf_connected(qf, a, b));

    return 0;
}

void qf_dump(quick_find * qf)
{
    for (size_t i = 0; i < qf->length; i++)
        printf("%lu ", *(qf->data+i));
    printf("\n");
}