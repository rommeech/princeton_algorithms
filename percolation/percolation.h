#include <stdio.h>
#include "../lib/status_codes.h"
#include "../lib/quick_union_wpc.h"

// Public functions
status_code init(size_t);               // create n-by-n grid, with all sites blocked
status_code open(size_t, size_t);       // open site (row, col) if it is not open already
status_code is_open(size_t, size_t);    // is site (row, col) open?
status_code is_full(size_t, size_t);    // is site (row, col) full?
size_t number_of_open_sites();          // number of open sites
status_code percolates();               // does the system percolate?
