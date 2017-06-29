#include <stdio.h>
#include <stdlib.h>
#include "../resizing_array_int.h"

/*
gcc lib/src/resizing_array_int.c
*/

int main()
{
    int i, j;

    rs_array_int * a = ra_int_init();
    printf("Inited, size=%lu, capa=%lu\n", ra_int_size(a), ra_int_capacity(a));
    
    for (i = 0; i < 10; i++) {
        ra_int_push(a, i);
        printf(" ... push %d, size=%lu, capa=%lu\n", i, ra_int_size(a), ra_int_capacity(a));
    }

    for (i = 0; i < 11; i++) {
        ra_int_pop(a, &j);
        printf(" ... pop %d = %d, size=%lu, capa=%lu\n", i, j, ra_int_size(a), ra_int_capacity(a));
    }
}

rs_array_int * ra_int_init()
{
    return ra_int_init_n(INIT_CAPACITY);
}

rs_array_int * ra_int_init_n(size_t init_capacity)
{
    rs_array_int * arr = (rs_array_int *) malloc(sizeof(rs_array_int));
    if (arr == NULL)
        return NULL;
    arr->data = (int *) malloc(sizeof(int) * init_capacity);
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = init_capacity;
    return arr;
}

status_code ra_int_push(rs_array_int * arr, int value)
{
    if (arr->size >= arr->capacity) {
        status_code res = ra_int_grow(arr);
        if (res != OK)
            return res;
    }
    arr->data[ arr->size++ ] = value;
    return OK;
}

status_code ra_int_pop(rs_array_int * arr, int * value)
{
    if (arr->size == 0)
        return ARRAY_IS_EMPTY;
    *value = arr->data[ arr->size ];
    arr->data[ arr->size-- ] = 0;
    if (arr->size <= arr->capacity / 4) {
        status_code res = ra_int_shrink(arr);
        if (res != OK)
            return res;
    }
    return OK;
}

status_code ra_int_is_empty(rs_array_int * arr)
{
    return arr->size == 0 ? TRUE : FALSE;
}

size_t ra_int_size(rs_array_int * arr)
{
    return arr->size;
}

size_t ra_int_capacity(rs_array_int * arr)
{
    return arr->capacity;
}

status_code ra_int_grow(rs_array_int * arr)
{
    return ra_int_resize(arr, arr->capacity * 2);
}

status_code ra_int_shrink(rs_array_int * arr)
{
    return ra_int_resize(arr, arr->capacity / 2);
}

status_code ra_int_resize(rs_array_int * arr, size_t new_size)
{
    arr->data = (int *) realloc(arr->data, sizeof(int *) * new_size);
    if (arr->data == NULL) {
        free(arr);
        return OUT_OF_MEMORY;
    }
    arr->capacity = new_size;
    return OK;
}

