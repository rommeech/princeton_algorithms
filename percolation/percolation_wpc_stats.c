#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "percolation.h"
#include "percolation_stats.h"

struct _stat {
    size_t grid_size;
    size_t trials_plan;
    size_t trials_run;
    double * fractions;
};
typedef struct _stat stat;

stat pstat;
size_t _str2num(char[]);
void _shuffle(size_t *, size_t);
void _dump_list(size_t *, size_t);

/*
Compilation:
gcc lib/quick_union_wpc.o \
    percolation/percolation_wpc.c \
    percolation/percolation_wpc_stats.c \
    -o percolation/percolation_wpc_stats
*/

int main(int argc, char * argv[])
{
    size_t n, t;

    // Check input parameters
    if (argc != 3) {
        printf("Call syntax: %s <N_SIZE> <TRIALS>\n", argv[0]);
        return 1;
    }
    
    n = _str2num(argv[1]);
    t = _str2num(argv[2]);

    if (!n || !t) {
        printf("Call syntax: %s <N_SIZE> <TRIALS>\n", argv[0]);
        return 2;
    }
    
    // Build stat object
    pstat.grid_size   = n;
    pstat.trials_plan = t;
    pstat.trials_run  = 0;
    pstat.fractions   = (double *) malloc(sizeof(double) * t);

    //printf("Starting with n=%lu, t=%lu\n", n, t);

    run(n, t);

    return 0;
}

/* ======================================================================
   PUBLIC function
  ==================================================================== */ 

// perform trials independent experiments on an n-by-n grid
status_code run(size_t n, size_t trials)
{
    size_t i;               // trials iterator
    size_t j;               // experiment iterator
    size_t nc = n * n;      // number of all cells
    size_t queue[nc];       // queue of cells to open

    // Initialize random number generator
    srand(time(NULL));

    // Run trials experiments
    for (i = 0; i < trials; i++)
    {
        // Build queue of cells to open
        for (j = 0; j < nc; j++)
            queue[j] = j;
        _shuffle(queue, nc);
        //_dump_list(queue, nc);

        // Start experiment
        j = 0;
        init(n);
        do
        {
            open(1 + queue[j] / n, 1 + queue[j] % n);
            j++;
        } while (!percolates());
        //printf("Percolated after %lu iterations\n", j);

        pstat.trials_run++;
        pstat.fractions[i] = (double) j / nc;
    }

    // Output results
    printf("mean                    = %f\n", mean());
    printf("stddev                  = %f\n", stddev());
    printf("95%% confidence interval = [%f, %f]\n",  confidence_lo(), confidence_hi());
    
    return OK;
}

// sample mean of percolation threshold
double mean()
{
    size_t i;
    double mn = 0;
    for (i = 0; i < pstat.trials_run; i++) {
        mn += pstat.fractions[i];
    }
    return mn / pstat.trials_run;
}

// sample standard deviation of percolation threshold
double stddev()
{
    size_t i;
    double mn = mean();
    double stddev = 0;
    double dev;
    for (i = 0; i < pstat.trials_run; i++) {
        dev = pstat.fractions[i] - mn;
        stddev += dev * dev;
    }
    return sqrt(stddev / (pstat.trials_run - 1));
}

// low  endpoint of 95% confidence interval
double confidence_lo()
{
    return mean() - 1.96 * stddev() / sqrt(pstat.trials_run);
}

// high endpoint of 95% confidence interval
double confidence_hi()
{
    return mean() + 1.96 * stddev() / sqrt(pstat.trials_run);
}

/* ======================================================================
   Private function
  ==================================================================== */
size_t _str2num(char str[])
{
    int i;
    size_t n = 0;
    for (i = 0; str[i] != '\0'; i++)
        if (str[i] >= '0' && str[i] <= '9')
            n = n * 10 + (str[i] - '0');
        else
            return 0; 
    return n;
}

void _shuffle(size_t * list, size_t nc)
{
    size_t i, j, a;
    for (i = 0; i < nc - 1; i++) {
        j = i + (rand() % (nc - i));
        if (i != j) {
            a = *(list + i);
            *(list + i) = *(list + j);
            *(list + j) = a;
        }
    }
}

void _dump_list(size_t * list, size_t nc)
{
    size_t i;
    for (i = 0; i < nc; i++)
        printf("%lu ", list[i]);
    printf("\n");
}
