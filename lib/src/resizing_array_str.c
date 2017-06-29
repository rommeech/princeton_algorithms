#include <stdio.h>
#include <stdlib.h>
#include "../resizing_array_str.h"

/*
gcc lib/src/resizing_array_str.c
gcc -c lib/src/resizing_array_str.c -o lib/src/resizing_array_str.o
*/

void str_copy(char * str_to, char * str_from);

/*
int main()
{
    int i;
    char *s1, *s2;

    rs_array_str * a = ra_str_init();
    printf("Inited, size=%lu, capa=%lu\n", ra_str_size(a), ra_str_capacity(a));
    
    for (i = 0; i < 10; i++) {
        sprintf(s1, "str%d", i);
        ra_str_push(a, s1);
        printf(" ... push %d, size=%lu, capa=%lu\n", i, ra_str_size(a), ra_str_capacity(a));
    }

    printf(" ... now try to pop values\n");

    s2 = (char *) malloc(sizeof(char) * 80);
    for (i = 0; i < 10; i++) {
        s2 = ra_str_pop(a);
        printf(" ... pop %d = %s, size=%lu, capa=%lu\n", i, s2, ra_str_size(a), ra_str_capacity(a));
    }
}
*/

rs_array_str * ra_str_init()
{
    return ra_str_init_n(INIT_CAPACITY);
}

rs_array_str * ra_str_init_n(size_t init_capacity)
{
    rs_array_str * arr = (rs_array_str *) malloc(sizeof(rs_array_str));
    if (arr == NULL)
        return NULL;
    arr->data = (char **) malloc(sizeof(char *) * init_capacity);
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = init_capacity;
    return arr;
}

status_code ra_str_push(rs_array_str * arr, char * value)
{
    if (arr->size >= arr->capacity) {
        status_code res = ra_str_grow(arr);
        if (res != OK)
            return res;
    }

    arr->data[arr->size] = (char *) malloc(sizeof(char) * strlen(value));
    str_copy(arr->data[arr->size], value);

    arr->size++;
    return OK;
}

char * ra_str_pop(rs_array_str * arr)
{
    if (arr->size == 0)
        return NULL;

    char * value = (char *) malloc(sizeof(char) * strlen(arr->data[arr->size - 1]));
    str_copy(value, arr->data[arr->size - 1]);
    //printf("    ... pop = %s / %s\n", value, arr->data[arr->size - 1]);

    arr->size--;
    if (arr->size <= arr->capacity / 4) {
        ra_str_shrink(arr);
    }

    return value;
}

status_code ra_str_is_empty(rs_array_str * arr)
{
    return arr->size == 0 ? TRUE : FALSE;
}

size_t ra_str_size(rs_array_str * arr)
{
    return arr->size;
}

size_t ra_str_capacity(rs_array_str * arr)
{
    return arr->capacity;
}

status_code ra_str_grow(rs_array_str * arr)
{
    return ra_str_resize(arr, arr->capacity * 2);
}

status_code ra_str_shrink(rs_array_str * arr)
{
    return ra_str_resize(arr, arr->capacity / 2);
}

status_code ra_str_resize(rs_array_str * arr, size_t new_size)
{
    arr->data = (char **) realloc(arr->data, sizeof(char *) * new_size);
    if (arr->data == NULL) {
        free(arr);
        return OUT_OF_MEMORY;
    }
    arr->capacity = new_size;
    return OK;
}

void str_copy(char * str_to, char * str_from)
{
    //char *s = (char *) malloc(sizeof(char) * strlen(str_from));
    //str_to = (char *) malloc(sizeof(char) * strlen(str_from));
    while ((*str_to++ = *str_from++) != 0);
}


