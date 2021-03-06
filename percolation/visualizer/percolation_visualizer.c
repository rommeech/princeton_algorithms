#include <stdio.h>
#include <stdlib.h>
#include "../percolation.h"

#define FULL   "\x1B[44m"
#define OPEN   "\x1B[47m"
#define RESET  "\x1B[0m"

/*
Compile:
gcc lib/quick_union_wpc.o \
    percolation/percolation_wpc.o \
    percolation/visualizer/percolation_visualizer.c \
    -o percolation/visualizer/percolation_visualizer

Run example:
./percolation/visualizer/percolation_visualizer < percolation/visualizer/input20.txt

gcc ../../lib/src/quick_union_wpc.c percolation_visualizer.c -o percolation_visualizer
./percolation_visualizer < input20.txt
*/

struct _percolation {
    quick_union_wpc * uf;   // union fild object
    char * cells;           // Open / block cells data
    size_t size;            // size of grid
    size_t open;            // number of open items
};
typedef struct _percolation percolation;

// Private variables
static percolation * prc;

// Declaration of private functions.
// Please note: if you want to implement percolation programm
// using another one Union Find alghorithm you need change
// only these functions
static size_t _get_uf_id(size_t, size_t);
static void _union(size_t, size_t, size_t, size_t);
static void _union_uf(size_t, size_t);
static status_code _is_connected(size_t, size_t, size_t, size_t);

int main(int argc, char * argv[])
{
    size_t size_n, row, col;
    
    scanf("%lu", &size_n);
    if (init(size_n) != OK) {
        printf("Cannot initialize percolation object with size %lu\n", size_n);
        return 1;
    }
    printf("Initialized with size %lu\n", size_n);

    while(scanf("%lu %lu", &row, &col) == 2) {
        if (open(row, col) != OK) {
            printf("Cannot open cell(%lu, %lu)\n", row, col);
        }
        printf("Open cell(%lu, %lu)\n", row, col);
    }

    for (row = 1; row <= size_n; row++) {
        for (col = 1; col <= size_n; col++) {
            if (is_full(row, col) == TRUE)
                printf(FULL " " RESET);
            else if (is_open(row, col) == TRUE)
                printf(OPEN " " RESET);
            else
                printf(" ");
        }
        printf("\n");
    }
    
    size_t n_open = number_of_open_sites();
    printf("%lu open size%s\n", n_open, n_open > 0 ? "s" : "");
    printf("%s\n", percolates() == TRUE ? "Percolates" : "Does not percolate");

    return 0;
}

// Convert ROW and COL values to union fild array ID
static size_t _get_uf_id(size_t row, size_t col)
{
    return prc->size * (row - 1) + col;
}

// Union two cells
static void _union(size_t row1, size_t col1, size_t row2, size_t col2)
{
    _union_uf(_get_uf_id(row1, col1), _get_uf_id(row2, col2));
}

static void _union_uf(size_t uf_id1, size_t uf_id2)
{
    quwpc_union(prc->uf, uf_id1, uf_id2);
}

// Check
static status_code _is_connected(size_t r1, size_t c1, size_t r2, size_t c2)
{
    return quwpc_connected(
        prc->uf,
        _get_uf_id(r1, c1),
        _get_uf_id(r2, c2)
    ) == TRUE ? TRUE : FALSE;
}

/* ======================================================================
   PUBLIC function
  ==================================================================== */ 

// create n-by-n grid, with all items blocked
status_code init(size_t size)
{
    size_t i, wpc_size;
    
    // Check input parameters

    // Init
    wpc_size = 1 + size * size;

    // initialize percolation object
    prc = (percolation *) malloc(sizeof(percolation));
    
    // union fild object as array of all cells
    prc->uf = init_quick_union_wpc(wpc_size);
    if (prc->uf == NULL) {
        free(prc);
        printf("init: cannot alloc memory for union fild object\n");
        return OUT_OF_MEMORY;
    }

    // All cells, all closed
    prc->cells = (char *) malloc(wpc_size * sizeof(char));
    if (prc->cells == NULL) {
        free(prc);
        printf("init: cannot alloc memory for cells\n");
        return OUT_OF_MEMORY;
    }
    for(i = 1; i < wpc_size - 1; i++)
        *(prc->cells + i) = 0;

    prc->size = size;
    prc->open = 0;

    // All right
    return OK;
}

// open site (row, col) if it is not open already
// open means we should mark current cell as open
status_code open(size_t row, size_t col)
{
    // Check input parameters
    if (row == 0 || col == 0 || row > prc->size || col > prc->size) {
        printf(
            "open: item(%lu, %lu) is out of range (%lu, %lu)\n",
            row,
            col,
            prc->size,
            prc->size
        );
        return OUT_OF_RANGE;
    }

    // Get ID of cell
    size_t uf_id = _get_uf_id(row, col);

    // Check whether current cell is open
    if (*(prc->cells + uf_id) > 0)
        return OK;
    
    // Mark cell as open and update open cells number
    *(prc->cells + uf_id) = 1;
    prc->open++;

    // Connect with neighbours open cells
    if (col < prc->size && is_open(row, col + 1))   // Right neighbour
        _union(row, col, row, col + 1);     
    if (col > 1 && is_open(row, col - 1))           // Left neighbour
        _union(row, col, row, col - 1); 
    if (row < prc->size && is_open(row + 1, col))   // Below cell
        _union(row, col, row + 1, col); 
    if (row > 1 && is_open(row - 1, col))           // Above cell
        _union(row, col, row - 1, col); 

    return OK;
}

// is site (row, col) open?
status_code is_open(size_t row, size_t col)
{
    // Check input parameters
    if (row == 0 || col == 0 || row > prc->size || col > prc->size) {
        printf(
            "is_open: item(%lu, %lu) is out of range (%lu, %lu)\n",
            row,
            col,
            prc->size,
            prc->size
        );
        return OUT_OF_RANGE;
    }
    return *(prc->cells + _get_uf_id(row, col)) > 0 ? TRUE : FALSE;
}
    
// is site (row, col) full?
status_code is_full(size_t row, size_t col)
{
    size_t i;
    
    // Check input parameters
    if (row == 0 || col == 0 || row > prc->size || col > prc->size) {
        printf(
            "is_open: item(%lu, %lu) is out of range (%lu, %lu)\n",
            row,
            col,
            prc->size,
            prc->size
        );
        return OUT_OF_RANGE;
    }
    
    // Closed cell cannot be full
    if (is_open(row, col) == FALSE) {
        return FALSE;
    }

    // First row open cells are always full
    if (row == 1)
        return TRUE;
    
    for (i = 1; i <= prc->size; i++)
        if (is_open(1, i) && _is_connected(1, i, row, col))
            return TRUE;

    return FALSE;
}

// number of open sites
size_t number_of_open_sites()
{
    return prc->open;
}

// does the system percolate?
status_code percolates()
{
    size_t i, j;
    for (i = 1; i <= prc->size; i++)
        if (is_open(1, i))
            for(j = 1; j <= prc->size; j++)
                if (is_open(prc->size, j)
                 && _is_connected(1, i, prc->size, j))
                    return TRUE;
    return FALSE;
}
