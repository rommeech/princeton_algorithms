#include <stdio.h>
#include "resizing_array_str.h"

typedef struct {
    rs_array_str * data;
} rand_array_str;

typedef struct {
    rand_array_str * iterator;
    size_t * order;
} rand_array_str_iterator;

rand_array_str * rqs_init();                                    // construct an empty randomized queue
status_code rqs_is_empty(rand_array_str *);                     // is the queue empty?
size_t rqs_size(rand_array_str *);                              // return the number of items on the queue
status_code enqueue(rand_array_str *, char *);                  // add the item
char * dequeue(rand_array_str *);                               // remove and return a random item
char * sample(rand_array_str *);                                // return (but do not remove) a random item

/* TODO: implement iterator
rand_array_str_iterator * rqs_iterator(rand_array_str *);       // return an independent iterator over items in random order
status_code rqsi_has_next(rand_array_str_iterator *);           // returns true if the iteration has more elements.
char * rqsi_next(rand_array_str_iterator *);                    // returns the next element in the iteration.
*/