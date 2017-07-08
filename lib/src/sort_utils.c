#include <stdio.h>
#include "../sort_utils.h"

/*
gcc -c lib/src/sort_utils.h -o lib/sort_utils.o
*/

//int main()
//{
//    return 0;
//}

int is_digit(char c)
{
    if ((c >= '0' && c <= '9') || c == '.' || c == '+' || c == '-')
        return 1;
    return 0;
}

int is_num(char *s)
{
    for (; is_digit(*s); s++);
    return *s == '\0' ? 1 : 0;
}

int is_int(char *s)
{
    for (; (*s >= '0' && *s <= '9') || *s == '+' || *s == '-'; s++);
    return *s == '\0' ? 1 : 0;
}

int str_to_int(char *s)
{
    int res = 0;
    signed char sign = 1;

    if (*s == '-') {
        sign = -1;
        s++;
    }
    else if (*s == '+')
        s++;
    for (; *s >= '0' && *s <= '9'; s++)
        res = res * 10 + (*s - '0');
    if (*s != '\0')
        return 0;
    res *= sign;
    return res;
}

double str_to_num(char *s)
{
    double res;
    signed char sign = 1;
    unsigned long int_part = 0;
    unsigned long frc_part = 0;
    unsigned long frc_exp  = 0;

    if (*s == '-') {
        sign = -1;
        s++;
    }
    else if (*s == '+')
        s++;
    for (; *s >= '0' && *s <= '9'; s++)
        int_part = int_part * 10 + (*s - '0');
    if (*s == '.') {
        s++;
        frc_exp = 10;
        for (; *s >= '0' && *s <= '9'; s++) {
            frc_exp *= 10;
            frc_part = frc_part * 10 + (*s - '0');
        }
    }
    if (*s != '\0')
        return 0;
    res = int_part;
    if (frc_exp > 0)
        res += frc_part / frc_exp;
    res *= sign;
    return res;
}

char lc(char c)
{
    if (c >= 'a' && c <= 'z')
        c += 'A' - 'a';
    return c;
}

char uc(char c)
{
    if (c >= 'A' && c <= 'Z')
        c += 'a' - 'A';
    return c;
}

int cmp_str(char *a, char *b)
{
    char aa, bb;
    do {
        aa = lc(*(a++));
        bb = lc(*(b++));
    } while (aa == bb);
    if (aa == '\0')
        return 0;
    return aa - bb;
}

// Case sensetive
int cmp_str_cs(char *a, char *b)
{
    for (; *a == *b; a++, b++)
        if (*a == '\0')
            return 0;
    return *a - *b;
}

int cmp_num(char *a, char *b)
{
    double an = str_to_num(a);
    double bn = str_to_num(b);
    return an - bn;
}

int cmp_int(char *a, char *b)
{
    int an = str_to_int(a);
    int bn = str_to_int(b);
    return an - bn;
}

void swap(void *v[], size_t a, size_t b)
{
    void *tmp;
    tmp = v[a];
    v[a] = v[b];
    v[b] = tmp;
}

int cmp_asc(char *a, char *b)
{
    return is_num(a) ? cmp_num(a, b) : cmp_str(a, b);
}

int cmp_desc(char *a, char *b)
{
    return is_num(a) ? cmp_num(b, a) : cmp_str(b, a);
}