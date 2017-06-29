#include <stdio.h>
#include "../rp_libstr.h"

/*
gcc -c lib/src/rp_libstr.c -o lib/rp_libstr.o
*/

void str_copy(char * to, char * from)
{
    while ((*to++ = *from++) != 0);
}