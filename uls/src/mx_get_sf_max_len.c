#include "../inc/uls.h"

static int nbr_len(int nbr);

int mx_get_sf_max_len(t_list *filelist, char *path) {
    int max_len = 0;
    int temp;
    char *str1 = NULL;
    char *str2 = NULL;

    for (t_list *cur = filelist; cur != NULL; cur = cur->next) {
        str1 = mx_strjoin(path, "/");
        str2 = mx_strjoin(str1, cur->data);
        temp = nbr_len((int)mx_fsize(str2));
        if (temp > max_len) max_len = temp;
        free(str1);
        free(str2);
    }
    return max_len;
}

int mx_flink(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0)
        return st.st_nlink;
    return -1;
}

int mx_get_lf_max_len(t_list *filelist, char *path) {
    int max_len = 0;
    int temp;
    char *str1 = NULL;
    char *str2 = NULL;

    for (t_list *cur = filelist; cur != NULL; cur = cur->next) {
        str1 = mx_strjoin(path, "/");
        str2 = mx_strjoin(str1, cur->data);
        temp = nbr_len(mx_flink(str2));
        if (temp > max_len) max_len = temp;
        free(str1);
        free(str2);
    }
    return max_len;
}

static int nbr_len(int nbr) {
    int len = 0;
    if (nbr == 0) return (1);
    if (nbr < len) len += 1;
    while (nbr != 0) {
        nbr = nbr / 10;
        len++;
    }
    return len;
}
