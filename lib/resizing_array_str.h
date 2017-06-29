#include "status_codes.h"

#ifndef RESIZING_ARRAY_STR
#define RESIZING_ARRAY_STR

#define INIT_CAPACITY 1

typedef struct {
    char ** data;
    size_t size;
    size_t capacity;
} rs_array_str;

rs_array_str * ra_str_init();
rs_array_str * ra_str_init_n(size_t init_capacity);
status_code ra_str_push(rs_array_str *, char * value);
char * ra_str_pop(rs_array_str *);
status_code ra_str_is_empty(rs_array_str *);
size_t ra_str_size(rs_array_str *);
size_t ra_str_capacity(rs_array_str *);
status_code ra_str_resize(rs_array_str *, size_t new_size);
status_code ra_str_grow(rs_array_str *);
status_code ra_str_shrink(rs_array_str *);

#endif