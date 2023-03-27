#include "../inc/libmx.h"

int mx_strlen(const char *s) {
    int len = 0;

    for (const char* i = s;; i++) {
        if (*i != '\0') len++;
        else break;
    }
    return len;
}
