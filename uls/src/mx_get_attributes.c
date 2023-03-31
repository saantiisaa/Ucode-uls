#include "../inc/uls.h"

off_t fsize(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0)
        return st.st_size;
    mx_printerr("Cannot determine size of ");
    mx_printerr(filename);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printerr("\n");
    return -1;
}

void get_file_attr(struct stat sb, t_list *file) {
    struct group    *grp;
    grp = getgrgid(sb.st_gid);
    mx_printstr("  ");
    mx_printstr(grp->gr_name);
    mx_printstr("  ");
    mx_printint((int)fsize(file->data));
    mx_printstr("  ");
    mx_printstr(file->data);
    mx_printstr("\n");
}

void get_file(const char *parent, t_list *file) {
    struct stat st_buf;
    char *path = NULL;
    char *temp = NULL;
    path = mx_strnew(mx_strlen(file->data) + mx_strlen(parent) + 2);
    temp = mx_strjoin(parent, "/");
    free(path);
    path = mx_strjoin(temp, file->data);
    free(temp);
    if (lstat(parent, &st_buf) == -1) {
    	perror("");
    }
    else get_file_attr(st_buf, file);
    free(path);
}

void mx_get_attributes(t_list *filelist, char *path) {
    for (t_list *cur = filelist; cur != NULL; cur = cur->next) {
        if (cur == NULL) break;
        get_file(path, cur);
    }
}
