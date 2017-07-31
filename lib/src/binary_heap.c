#include <stdio.h>
#include <stdlib.h>
#include "../binary_heap.h"
#include "../sort_utils.h"
#define BH_INIT_CAPACITY 8

bheap * bheap_init(size_t data_size, int (*comp)(void *, void *))
{
    return bheap_init2(data_size, BH_INIT_CAPACITY, comp);
}

bheap * bheap_init2(size_t data_size, size_t init_capa, int (*comp)(void *, void *))
{
    bheap *bh;
    
    if (init_capa <= 0)
        init_capa = BH_INIT_CAPACITY;
    
    bh = (bheap *) malloc(sizeof(bheap));
    if (bh == NULL)
        return NULL;
    
    bh->data = malloc(data_size * (init_capa+1));
    if (bh->data == NULL) {
        free(bh);
        return NULL;
    }
    
    bh->data_size = data_size;
    bh->n          = 0;
    bh->capa       = init_capa;
    bh->cmp        = comp;
    
    return bh;
}

status_code bh_is_empty(bheap *bh)
{
    return bh->n > 0 ? FALSE : TRUE;
}

size_t bh_size(bheap *bh)
{
    return bh->n;
}

size_t bh_capacity(bheap *bh)
{
    return bh->capa;
}

status_code bh_insert(bheap *bh, void *new_item)
{
    if (bh->n >= bh->capa) {
        status_code res = bh_grow(bh);
        if (res != TRUE)
            return CANNOT_INSERT;
    }
        
    bh->n++;
    bh->data[ bh->n ] = new_item;
    bh_swim(bh, bh->n);
    return OK;
}

void * bh_get_root(bheap *bh)
{
    if (bh->n < 1) return NULL;
    return bh->data[ bh->n ];
}

void * bh_delete_root(bheap *bh)
{
    void *item;
    
    if (bh->n < 1)
        return NULL;

    if (bh->n <= bh->capa / 4) {
        bh_shring(bh);
        // Do not check status code here. In case of trouble we cannot free
        // memory, but programm should not stop
    }

    swap(bh->data, 1, bh->n);
    item = bh->data[ bh->n ];
    bh->data[ bh->n ] = NULL;
    bh->n--;
    bh_sink(bh, 1);

    return item;
}

static status_code bh_grow(bheap *bh)
{
    return bh_resize(bh, bh->capa * 2);
}

static status_code bh_shring(bheap *bh)
{
    return bh_resize(bh, bh->capa / 2);
}

static status_code bh_resize(bheap *bh, size_t new_size)
{
    bh->data = realloc(bh->data, bh->data_size * (new_size + 1));
    if (bh->data == NULL) {
        free(bh);
        return OUT_OF_MEMORY;
    }
    bh->capa = new_size;
    return TRUE;
}

static status_code bh_swim(bheap *bh, size_t k)
{
    if (k < 1 || k > bh->n)
        return OUT_OF_RANGE;
    while (k > 1) {
        size_t pk = k/2;    // Parent id
        if (bh->cmp(bh->data[pk], bh->data[k]) > 0) {
            swap(bh->data, k, pk);
            k = pk;
        }
        else
            break;
    }
    return OK;
}

static status_code bh_sink(bheap *bh, size_t k)
{
    if (k < 1 || k > bh->n)
        return OUT_OF_RANGE;
    
    size_t j = k*2;
    while (j <= bh->n)
    {
        if (j < bh->n && bh->cmp(bh->data[j], bh->data[j+1]) > 0)
            j++;
        if (bh->cmp(bh->data[k], bh->data[j]) < 0)
            break;
        swap(bh->data, k, j);
        k = j;
        j *= 2;
    }
    
    return OK;
}



