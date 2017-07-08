#include <stdio.h>

#ifndef LIB_SORT_UTILS
#define LIB_SORT_UTILS

char lc(char);
char uc(char);
int is_digit(char);
int is_num(char *);
int is_int(char *);
int str_to_int(char *);
double str_to_num(char *);
int cmp_str(char *, char *);
int cmp_str_cs(char *, char *);         // Case sensetive
int cmp_num(char *, char *);
int cmp_int(char *, char *);
void swap(void **, size_t, size_t);
int cmp_asc(char *a, char *b);
int cmp_desc(char *a, char *b);

#endif