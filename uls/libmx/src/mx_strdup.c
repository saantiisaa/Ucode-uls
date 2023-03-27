#include "../inc/libmx.h"

char *mx_strdup(const char *str){
    int size = mx_strlen(str);
    char *new = mx_strnew(size);
    return mx_strcpy(new, str);;
}
