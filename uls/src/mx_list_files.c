#include "../inc/uls.h"

void mx_list_files(t_main *main, char *basePath) {
    DIR *dir;
    if (!(dir = opendir(basePath))) return;
    mx_process_filelist(main, basePath);
    closedir(dir);
}
