#include "../inc/uls.h"

void mx_print_m_time(struct stat *file_stat) {
    char *str = NULL;

    #ifdef __linux__
        struct timespec modtime = file_stat->st_mtim;
        char *modtime_str = ctime(&modtime.tv_sec);
        str = mx_strndup(modtime_str + 4, 12);
    #endif
    
    #ifdef __APPLE__
    time_t modtime_sec = file_stat->st_mtime;
    str = mx_strndup(ctime(&modtime_sec) + 4, 12);
    #endif

    mx_printstr(str);
    free(str);
}
