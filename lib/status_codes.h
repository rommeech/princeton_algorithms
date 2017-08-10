#ifndef STCDS
#define STCDS

typedef enum {
    NOT_INITED     = -6,
    CANNOT_DELETE  = -5,
    CANNOT_INSERT  = -4,
    ARRAY_IS_EMPTY = -3,
    OUT_OF_MEMORY  = -2,
    OUT_OF_RANGE   = -1,
    NOK            =  0,
    OK             =  1,
} status_code;

typedef enum {
    FALSE =  0,
    TRUE  =  1,
} boolean;

#endif