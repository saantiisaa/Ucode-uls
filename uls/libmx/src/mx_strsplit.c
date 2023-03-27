#include "../inc/libmx.h"

char **mx_strsplit(const char *s, char c) {
    if (!s) return NULL;
    int len = 0;
    int i = 0;
    char **arr = NULL;

    arr = (char**)malloc((mx_count_words(s, c) + 1) * sizeof(char*));
    while ((*s) && (*s != '\0')) {
        if (*s != c) {

            len = 0;
            while (s[len] && s[len] != c) 
                len++;

            arr[i] = mx_strndup(s, len);
            s += len;
            i++;
            
            continue;
        }
        s++;
    }
    arr[i] = NULL;
    return arr;
}
