#include <stdio.h>
#include "status_codes.h"

// Data structure
// Interpretation: id[i] is parent of i.
// Root of i is id[id[id[...id[i]...]]].
struct _quick_union_wpc {
    size_t * data;
    size_t * size;
    size_t length;
};

typedef struct _quick_union_wpc quick_union_wpc;

// Init
quick_union_wpc * init_quick_union_wpc(size_t);

// Get root ID of element
size_t quwpc_root(quick_union_wpc *, size_t);

// Union two entities
status_code quwpc_union(quick_union_wpc *, size_t, size_t);

// Check whether two entities connected
status_code quwpc_connected(quick_union_wpc *, size_t, size_t);
