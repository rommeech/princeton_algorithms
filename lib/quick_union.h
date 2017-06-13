#include <stdio.h>

// Return codes
typedef enum _return_codes {
    OUT_OF_RANGE = -1,
    FALSE        =  0,
    TRUE         =  1, 
} rt_code;

// Data structure
// Interpretation: id[i] is parent of i.
// Root of i is id[id[id[...id[i]...]]].
struct _quick_union {
    size_t * data;
    size_t length;
};

typedef struct _quick_union quick_union;

// Init
quick_union * init_quick_union(size_t);

// Get root ID of element
size_t qu_root(quick_union *, size_t);

// Union two entities
rt_code qu_union(quick_union *, size_t, size_t);

// Check whether two entities connected
rt_code qu_connected(quick_union *, size_t, size_t);
