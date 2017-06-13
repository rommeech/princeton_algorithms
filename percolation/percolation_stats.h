#include <stdio.h>

// Public functions
status_code run(size_t, size_t);        // perform trials independent experiments on an n-by-n grid
double mean();                          // sample mean of percolation threshold
double stddev();                        // sample standard deviation of percolation threshold
double confidence_lo();                 // low  endpoint of 95% confidence interval
double confidence_hi();                 // high endpoint of 95% confidence interval
