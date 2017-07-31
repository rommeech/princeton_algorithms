#ifndef STCDS
#define STCDS

typedef enum {
    OUT_OF_RANGE   = -1,
    OUT_OF_MEMORY  = -2,
    ARRAY_IS_EMPTY = -3,
    CANNOT_INSERT  = -4,
    CANNOT_DELETE  = -5,
    NOT_INITED     = -6,
    FALSE          =  0,
    TRUE           =  1,
    OK             =  2,
} status_code;

#endif