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
            mx_printerr("uls: ");
            mx_printerr(main.dirs[j]);
            mx_printerr(": No such file or directory\n");
            error = true;
        }
    }

    t_list *filelist = NULL;
    for (int j = 0; main.dirs[j] != NULL; j++) {
        if (mx_is_dir(main.dirs[j]) == 1 && mx_file_exists(main.dirs[j])) {
            if (filelist == NULL) 
                filelist = mx_fl_create_node(mx_strdup(main.dirs[j]));
            else 
                mx_fl_push_back(&filelist, mx_strdup(main.dirs[j]));
            files_count++;
        }
        if (mx_is_dir(main.dirs[j]) == 0 && mx_file_exists(main.dirs[j])) {
            dirs_count++;
        }
    }

    if (filelist != NULL) {
        mx_format_output(&main, filelist, ".", true);
    }
    mx_delete_filelist(filelist);

    if (files_count > 0 && dirs_count > 0) {
        mx_printstr("\n");
    }

    for (int i = 0; main.dirs[i] != NULL; i++) {
        if (!mx_file_exists(main.dirs[i])) {
            error = true;
            continue;
        }
        if (mx_is_dir(main.dirs[i]) == 0) {
            if (mx_file_exists(main.dirs[i]) && (dirs_count > 1 || files_count > 0 || error)) {
                mx_printstr(main.dirs[i]);
                mx_printstr(":\n");
            }
            mx_list_files(&main, main.dirs[i]);
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
