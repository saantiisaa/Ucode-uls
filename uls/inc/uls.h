#ifndef ULS_ULS_H
#define ULS_ULS_H


#define _GNU_SOURCE

#include "../libmx/inc/libmx.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/xattr.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Macros
#define ARGUMENTS "lar1"  // List of supported flags

#ifdef __APPLE__
#ifndef st_mtime
#define st_mtime st_mtimespec.tv_sec
#endif
#endif

typedef struct s_main {
    char **dirs;                  // The list of directories where we run ls
    char *flags;
    bool hasCat;
}           t_main;


char *mx_getdir(char *argv);

// Errors
void mx_error_illegal_option(const char *ch);
void mx_error_no_such_file(char *filename);

// Memory
void mx_alloc_clean_up(t_main *main);

// Parse
void mx_parse_flags(t_main *main, char **argv);
void mx_parse_file_paths(t_main *main, int argc, char **argv);
int mx_get_terminal_width();

// Output
void mx_list_files(t_main *main, char *basePath);
void mx_print_filelist(t_list* filelist);
void mx_process_filelist(t_main *main, char *path);
t_list *mx_fl_create_node(char *filename);
void mx_fl_push_back(t_list **list, char *filename);
void mx_delete_filelist(t_list *filelist);
void mx_print_format(t_list *filelist);
void mx_print_format_column(t_list *filelist);
void mx_print_format_details(t_main *main, t_list *filelist, char *path);
void mx_format_output(t_main *main, t_list *filelist, char *path);
void mx_filter_filelist(t_list *filelist);
void mx_print_file_size(char *name, int size_len);
void mx_print_m_time(struct stat *file_stat);

// Utils
int mx_file_exists(char *filename);
int mx_is_regular_file(const char *filename);
int mx_is_dir(const char *filename);
off_t mx_fsize(const char *filename);
int mx_get_sf_max_len(t_list *filelist, char *path);

// Linked list
int mx_get_n_nodes(t_list *filelist);

//test
void mx_get_attributes(t_list *filelist, char *path);

int to_lower(int c);
char* to_lowercase(const char* str);
bool mx_compare_alphabetic(void *arg1, void *arg2);
bool mx_compare_reverse(void *arg1, void *arg2);
void mx_sort_dirs(t_main *main, bool (*cmp)(void *a, void *b));
void mx_printerr(const char *s);
void mx_print_rwx(char *name);
void mx_print_nlink(struct stat *sb, char *name, int size_len);
void mx_print_nlink_linux(struct stat *sb, char *name);

#endif
