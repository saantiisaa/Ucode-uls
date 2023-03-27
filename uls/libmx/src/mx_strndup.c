#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t len = mx_strlen(s1);
    if (len > n)
        len = n;
    char *new = (char *)malloc(len + 1);
    if (new == NULL)
        return NULL;
    new[len] = '\0';
    return (char *)mx_memcpy(new, s1, len);
}
