#include "../inc/uls.h"

void mx_print_m_time(struct stat *file_stat) {
    char *str = NULL;

    time_t current = time(NULL);
    time_t modtime_sec = file_stat->st_mtime;
    double diff = (double)(current - modtime_sec);

    if (diff > (15768000)) { // more than 6 months
        str = mx_strndup(ctime(&modtime_sec) + 4, 7);
        char *year_str = mx_strndup(ctime(&modtime_sec) + 20, 4);
        mx_printstr(str);
        mx_printstr(" ");
        mx_printstr(year_str);
        free(year_str);
    } else {
        str = mx_strndup(ctime(&modtime_sec) + 4, 12);
        mx_printstr(str);
    }

    free(str);
}
