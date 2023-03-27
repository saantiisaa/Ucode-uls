#include "../inc/uls.h"

void mx_sort_dirs(t_main *main, bool (*cmp)(void *a, void *b)) {
	int i, j;
    char* temp;
    for (i = 0; main->dirs[i] != NULL; i++) {
        for (j = 0; main->dirs[j] != NULL; j++) {
            if (cmp(main->dirs[j], main->dirs[j+1])) {
                temp = main->dirs[j];
                main->dirs[j] = main->dirs[j+1];
                main->dirs[j+1] = temp;
            }
        }
    }
}

int main(int argc, char **argv) {
    t_main main;
    int dirs_count = 0;
    int files_count = 0;
    bool error = false;
    mx_parse_flags(&main, argv);
    mx_parse_file_paths(&main, argc, argv);
    if (mx_get_char_index(main.flags, 'r') > 0) {
        mx_sort_dirs(&main, mx_compare_reverse);
    }
    else {
        mx_sort_dirs(&main, mx_compare_alphabetic);
    }
    for (int j = 0; main.dirs[j] != NULL; j++) {
        if (!mx_file_exists(main.dirs[j])) {
            mx_printstr("uls: ");
            mx_printstr(main.dirs[j]);
            mx_printstr(": No such file or directory\n");
            error = true;
        }
    }
    for (int j = 0; main.dirs[j] != NULL; j++) {
        if (mx_is_dir(main.dirs[j]) == 1 && mx_file_exists(main.dirs[j])) {
            if (mx_get_char_index(main.flags, 'l') > 0) {
                struct stat file_stat;

                if (lstat(main.dirs[j], &file_stat) == -1) {
                    mx_error_no_such_file(main.dirs[j]);
                    error = true;
                    continue;
                }

                struct passwd *pwd = getpwuid(file_stat.st_uid);
                struct group *grp = getgrgid(file_stat.st_gid);

                mx_print_rwx(main.dirs[j]);
                #ifdef __linux__
                mx_printstr(" ");
                mx_print_nlink_linux(&file_stat, main.dirs[j]);
                #endif
                #ifdef __APPLE__
                mx_print_nlink(&file_stat, main.dirs[j], (int)file_stat.st_size - 1);
                #endif
                mx_printstr(" ");
                mx_printstr(pwd->pw_name);
                mx_printstr(" ");
                mx_printstr(grp->gr_name);
                mx_printstr(" ");
                mx_printint((int)file_stat.st_size);
                mx_printstr(" ");
                mx_print_m_time(&file_stat);
                mx_printstr(" ");
            }
            mx_printstr(main.dirs[j]);
            mx_printstr("\n");
            files_count++;
        }
        if (mx_is_dir(main.dirs[j]) == 0 && mx_file_exists(main.dirs[j])) {
            dirs_count++;
        }
    }
    if (files_count > 0 && dirs_count > 0) {
        mx_printstr("\n");
    }
    for (int i = 0; main.dirs[i] != NULL; i++) {
        if (!mx_file_exists(main.dirs[i])) {
            error = true;
            continue;
        }
        if (mx_is_dir(main.dirs[i]) == 0) {
            if (mx_strcmp(main.dirs[i], ".") != 0 && mx_file_exists(main.dirs[i]) && (dirs_count > 1 || files_count > 0 || error)) {
                mx_printstr(main.dirs[i]);
                mx_printstr(":\n");
            }
            mx_list_files(&main, main.dirs[i]); //leak here
            for (int k = i; main.dirs[k] != NULL; k++) {
                if (mx_is_dir(main.dirs[k + 1]) == 0 && main.dirs[k + 1] != NULL && mx_file_exists(main.dirs[k + 1])) {
                    mx_printstr("\n");
                    break;
                }
            }
        }
        
    }
    mx_alloc_clean_up(&main);
    if (error) {
        exit(1);
    }
    exit(0);
}
