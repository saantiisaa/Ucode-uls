#include "../inc/uls.h"

t_list *mx_create_filelist(t_main *main, char *path);
t_list *get_all_files(char *path);
t_list *get_all_hidden(char *path);
t_list *get_only_visible(char *path);

int to_lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c +'a'-'A';
    else
        return c;
}

// possible leaks
char* to_lowercase(const char* str) {
    char* new_str = malloc(mx_strlen(str) + 1);
    if (new_str == NULL) {
        return NULL;
    }
    for (int i = 0; i < mx_strlen(str); i++) {
        new_str[i] = to_lower(str[i]);
    }
    new_str[mx_strlen(str)] = '\0';
    return new_str;
}

bool mx_compare_alphabetic(void *arg1, void *arg2) {
    if (arg1 == NULL || arg2 == NULL) {
        // handle null pointer case
        return false;
    }

    #ifdef __linux__
        char* first = to_lowercase(((const char *)(arg1)));
        char* second = to_lowercase(((const char *)(arg2)));
        bool result = mx_strcmp(first, second) > 0;
        free(first);
        free(second);
        return result;
    #endif

    #ifdef __APPLE__
        return (
            mx_strcmp(
                ((const char *)(arg1)),
                ((const char *)(arg2))
            ) > 0
        );
    #endif
}

bool mx_compare_reverse(void *arg1, void *arg2) {
    if (arg1 == NULL || arg2 == NULL) {
        // handle null pointer case
        return false;
    }

    #ifdef __linux__
        char* first = to_lowercase(((const char *)(arg1)));
        char* second = to_lowercase(((const char *)(arg2)));
        bool result = mx_strcmp(first, second) < 0;
        free(first);
        free(second);
        return result;
    #endif

    #ifdef __APPLE__
        return (
            mx_strcmp(
                ((const char *)(arg1)),
                ((const char *)(arg2))
            ) < 0
        );
    #endif
}

void mx_process_filelist(t_main *main, char *path) {
    t_list *filelist = NULL;
    filelist = mx_create_filelist(main, path); //leak
    mx_format_output(main, filelist, path);
    mx_delete_filelist(filelist);
}

t_list *mx_create_filelist(t_main *main, char *path) {
    t_list *filelist = NULL;
    if (mx_get_char_index(main->flags, 'A') > 0) 
        filelist = get_all_hidden(path);
    else if (mx_get_char_index(main->flags, 'a') > 0) 
        filelist = get_all_files(path);
    else 
        filelist = get_only_visible(path);
    if (mx_get_char_index(main->flags, 'r') > 0) {
        return mx_sort_list(filelist, mx_compare_reverse);
    }
    return mx_sort_list(filelist, mx_compare_alphabetic); // leak
}

t_list *get_all_files(char *path) {
    DIR *ddd;
    struct dirent *dirrr;
    t_list *filelist = NULL;
    ddd = opendir(path);
    while ((dirrr = readdir(ddd)) != NULL) {
        if (filelist == NULL) 
            filelist = mx_fl_create_node(mx_strdup(dirrr->d_name));
        else 
            mx_fl_push_back(&filelist, mx_strdup(dirrr->d_name));
    }
    closedir(ddd);
    return filelist;
}

t_list *get_all_hidden(char *path) {
    DIR *ddd;
    struct dirent *dirrr;
    t_list *filelist = NULL;
    ddd = opendir(path);
    while ((dirrr = readdir(ddd)) != NULL) {
        if (mx_strcmp(dirrr->d_name, ".") != 0 && mx_strcmp(dirrr->d_name, "..") != 0) {
            if (filelist == NULL) 
                filelist = mx_fl_create_node(mx_strdup(dirrr->d_name));
            else 
                mx_fl_push_back(&filelist, mx_strdup(dirrr->d_name));
        }
    }
    closedir(ddd);
    return filelist;
}

t_list *get_only_visible(char *path) {
    DIR *ddd;
    struct dirent *dirrr;
    t_list *filelist = NULL;
    ddd = opendir(path);
    while ((dirrr = readdir(ddd)) != NULL) {
        if (dirrr->d_name[0] != '.')  {
            if (filelist == NULL) 
                filelist = mx_fl_create_node(mx_strdup(dirrr->d_name));
            else 
                mx_fl_push_back(&filelist, mx_strdup(dirrr->d_name));
        }
    }
    closedir(ddd);
    return filelist;
}
