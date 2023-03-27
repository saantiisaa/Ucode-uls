#include "../inc/libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (fd < 0 || buf_size < 0 || !delim || !lineptr) {
        return -2;
    }
    static char *remainder = NULL;
    char *str = NULL;
    int total = 0;
    char *buf = malloc(buf_size + 1);
    ssize_t result = -1;

    if (remainder != NULL) {
        str = remainder;
        remainder = NULL;
        total = mx_strlen(str);
    }

    while (fd >= 0 && (result = read(fd, buf, buf_size)) > 0) {
        char *ptr = mx_memchr(buf, delim, result);
        ssize_t count = result;

        if (ptr != NULL) {
            count = ptr - buf;
        }

        buf[count] = '\0';
        str = mx_realloc(str, total + count + 1);
        mx_strcat(str, buf);
        total += count;

        if (ptr != NULL) {
            ssize_t remaining = result - count;

            if (remaining > 0) {
                remainder = mx_strndup(buf + count + 1, remaining);
            }
            break;
        }
    }

    free(buf);

    if (result == -1) {
        mx_strdel(&str);
        mx_strdel(&remainder);
        return -2;
    }

    if (str == NULL) {
        return -1;
    }

    *lineptr = str;
    return total;
}
