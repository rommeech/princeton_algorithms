#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../randomized_queue_str.h"
#include "../resizing_array_str.h"

/*
gcc lib/src/resizing_array_str.c lib/src/randomized_queue_str.c -o bin/test/randomized_queue_str
./bin/test/randomized_queue_str
*/

// Test client
int main()
{
    int i;
    char *s1, *s2;

    rand_array_str * arr = rqs_init();

    for (i = 0; i < 10; i++) {
        sprintf(s1, "str%d", i);
        enqueue(arr, s1);
        printf("added %d str: %s\n", i, s1);
    }

    for (i = 0; i < 10; i++) {
        s2 = dequeue(arr);
        printf("got %d str: %s\n", i, s2);
    }

    return 0;
}

// construct an empty randomized queue
rand_array_str * rqs_init()
{
    rand_array_str * arr;
    arr = (rand_array_str *) malloc(sizeof(rand_array_str));
    if (arr == NULL) return NULL;
    arr->data = ra_str_init();
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    srand(time(NULL));
    return arr;
}

// is the queue empty?
status_code rqs_is_empty(rand_array_str * arr)
{
    return ra_str_is_empty(arr->data);
}

// return the number of items on the queue
size_t rqs_size(rand_array_str * arr)
{
    return ra_str_size(arr->data);
}

// add the item
status_code enqueue(rand_array_str * arr, char * item)
{
    return ra_str_push(arr->data, item);
}

// remove and return a random item
char * dequeue(rand_array_str * arr)
{
    size_t n = rand() % ra_str_size(arr->data);
    char * item = arr->data->data[n];
    arr->data->data[n] = ra_str_pop(arr->data);
    return item;
}

// return (but do not remove) a random item
char * sample(rand_array_str * arr)
{
    size_t n = rand() % ra_str_size(arr->data);
    return arr->data->data[n];
}

/*
rand_array_str_iterator * rqs_iterator(rand_array_str *);       // return an independent iterator over items in random order
status_code rqsi_has_next(rand_array_str_iterator *);           // returns true if the iteration has more elements.
char * rqsi_next(rand_array_str_iterator *);                    // returns the next element in the iteration.
*/