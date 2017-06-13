#include <stdio.h>

// Return codes
typedef enum _return_codes {
    OUT_OF_RANGE = -1,
    FALSE        =  0,
    TRUE         =  1, 
} rt_code;

// Data structure
struct _quick_find {
    size_t * data;
    size_t length;
};

typedef struct _quick_find quick_find;

// Init
quick_find * init_quick_find(size_t);

// Union two entities
rt_code qf_union(quick_find *, size_t, size_t);

// Check whether two entities connected
rt_code qf_connected(quick_find *, size_t, size_t);
