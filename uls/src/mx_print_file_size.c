#include "../inc/uls.h"

void mx_print_file_size(char *name, int size_len) {
    char *str = NULL;
    char *temp = NULL;
    int str_len = size_len;
    int temp_len;
    str = mx_strnew(size_len);
    for (int j = 0; j < size_len; j++) str[j] = ' ';
    temp = mx_itoa((int)mx_fsize(name));
    temp_len = mx_strlen(temp);
    while (temp_len >= 0) {
        str[str_len] = temp[temp_len];
        temp_len--;
        str_len--;
    }
    mx_printstr(str);
    free(temp);
    if (str) free(str);
}
