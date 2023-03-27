#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
    int f = open(file, O_RDONLY);
    if (f < 0) {
        close(f);
        return NULL;
    }
    int l = 0;
    char c;
    int info = read(f, &c, 1);
    while (info > 0) {
        info = read(f, &c, 1);
        l++;
    }
    close(f);
    if (l == 0) {
        return "\0";
    }
    f = open(file, O_RDONLY);
    char *result = mx_strnew(l);
    read(f, result, l);
    close(f);
    return result;
}
