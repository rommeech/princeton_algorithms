#include <stdio.h>
#include "../rp_libstr.h"

/*
gcc -c lib/src/rp_libstr.c -o lib/rp_libstr.o
*/

void str_copy(char * to, char * from)
{
    while ((*to++ = *from++) != 0);
}

size_t str_len(char * s)
{
    size_t l;
    for (l = 0; *s++ != '\0'; l++);
    return l;
}