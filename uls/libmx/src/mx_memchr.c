#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *pointer = (unsigned char *)s;

    for (; n > 0; n--) {
        if (*pointer == (unsigned char)c) 
            return pointer;
        pointer++;
    }
    return NULL;
}
