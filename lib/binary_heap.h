#include <stdio.h>
#include "status_codes.h"

typedef struct {
    size_t n;
    size_t capa;
    size_t data_size;
    int (*cmp)(void *, void *);
    void **data;
} bheap;

bheap * bheap_init(size_t data_size, int (*comp)(void *, void *));
bheap * bheap_init2(size_t data_size, size_t init_capa, int (*comp)(void *, void *));
status_code bh_is_empty(bheap *bh);
size_t bh_size(bheap *bh);
size_t bh_capacity(bheap *bh);
status_code bh_insert(bheap *bh, void *new_item);
void * bh_delete_root(bheap *bh);
void * bh_get_root(bheap *bh);

static status_code bh_grow(bheap *bh);
static status_code bh_shring(bheap *bh);
static status_code bh_resize(bheap *bh, size_t new_size);
static status_code bh_swim(bheap *bh, size_t k);
static status_code bh_sink(bheap *bh, size_t k);


/*
Private

bh_less - should be passed as comparator function
bh_exch - inherited from sort_utils
*/