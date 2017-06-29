#include "status_codes.h"

typedef struct deq_str_node deq_str_node;

struct deq_str_node {
    deq_str_node *next;
    deq_str_node *prev;
    char * item;
};

typedef struct {
    deq_str_node *first;
    deq_str_node *last;
    size_t size;
} deq_str;

deq_str * deq_str_init();
status_code deq_str_add_first(deq_str *, char *value);      // add the item to the front
status_code deq_str_add_last(deq_str *, char *value);       // add the item to the end
char * deq_str_remove_first(deq_str *);                     // remove and return the item from the front
char * deq_str_remove_last(deq_str *);                      // remove and return the item from the end
status_code deq_str_is_empty(deq_str *);
size_t deq_str_size(deq_str *);

deq_str_node * deq_str_node_init(char *value);

/* TODO: implement iterator
deq_str_iter * deq_str_iterator(deq_str *);             // return an iterator over items in order from front to end
status_code deq_str_iter_has_next(deq_str_iter *);      // returns true if the iteration has more elements.
char * deq_str_iter_next(deq_str_iter *);               // returns the next element in the iteration.
*/
