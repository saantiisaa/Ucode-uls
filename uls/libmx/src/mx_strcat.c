#include "../inc/libmx.h"

char *mx_strcat(char *s1, const char *s2) {
    int len_s1 = mx_strlen(s1);
    int len_s2 = mx_strlen(s2);
    
    for (int i = 0; i < len_s2; i++) {
        s1[len_s1 + i] = s2[i];
    }
    s1[len_s1 + len_s2] = '\0';
    return s1;
}
