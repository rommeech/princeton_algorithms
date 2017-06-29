#include "status_codes.h"

#define INIT_CAPACITY 1

typedef struct {
    int * data;
    size_t size;
    size_t capacity;
} rs_array_int;

rs_array_int * ra_int_init();
rs_array_int * ra_int_init_n(size_t init_capacity);
status_code ra_int_push(rs_array_int *, int value);
status_code ra_int_pop(rs_array_int *, int * value);
status_code ra_int_is_empty(rs_array_int *);
size_t ra_int_size(rs_array_int *);
size_t ra_int_capacity(rs_array_int *);
status_code ra_int_resize(rs_array_int *, size_t new_size);
status_code ra_int_grow(rs_array_int *);
status_code ra_int_shrink(rs_array_int *);