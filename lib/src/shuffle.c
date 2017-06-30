#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../shuffle.h"

/*
gcc lib/src/shuffle.c -o bin/test/shuffle.o
*/

int main()
{
    int i;
    int n = 10;
    char **s, *s1;
    s = (char **) malloc(sizeof(char *) * n);

    for (i = 0; i < n; i++) {
        s1 = (char *) malloc(sizeof(char) * 80);
        sprintf(s1, "str_%d", i);
        *(s+i) = s1;
    }
    shuffle((void **)s, n);
    for (i = 0; i < n; i++)
        printf("%d => %s\n", i, *(s+i));

    return 0;
}

void shuffle(void **base, size_t n_items)
{
    srand(time(NULL));
    size_t i, j;
    void *tmp;
    for (i = 0; i < n_items - 1; i++) {
        j = i + rand() % (n_items - i);
        tmp = base[j];
        base[j] = base[i];
        base[i] = tmp;
    }
}

