#include "../inc/uls.h"

void mx_print_rwx(char *name) {
    struct stat sb;
    stat(name, &sb);
    char modestr[11];

    modestr[0] = (S_IFDIR & sb.st_mode) ? 'd' : '-';
    modestr[1] = (S_IRUSR & sb.st_mode) ? 'r' : '-';
    modestr[2] = (S_IWUSR & sb.st_mode) ? 'w' : '-';
    modestr[3] = (S_IXUSR & sb.st_mode) ? 'x' : '-';
    modestr[4] = (S_IRGRP & sb.st_mode) ? 'r' : '-';
    modestr[5] = (S_IWGRP & sb.st_mode) ? 'w' : '-';
    modestr[6] = (S_IXGRP & sb.st_mode) ? 'x' : '-';
    modestr[7] = (S_IROTH & sb.st_mode) ? 'r' : '-';
    modestr[8] = (S_IWOTH & sb.st_mode) ? 'w' : '-';
    modestr[9] = (S_IXOTH & sb.st_mode) ? 'x' : '-';
    modestr[10] = '\0';

    mx_printstr(modestr);
}

void mx_print_nlink(struct stat *sb, char *name, int size_len) {
    if (lstat(name, sb) != -1) {
        char *str = mx_strnew(size_len);
        for (int j = 0; j < size_len; j++) 
            str[j] = ' ';
        char *temp = mx_itoa(sb->st_nlink);
        int temp_len = mx_strlen(temp);
        int str_len = size_len;
        while (temp_len >= 0) {
            str[str_len] = temp[temp_len];
            temp_len--;
            str_len--;
        }
        mx_printstr(str);
        free(temp);
        if (str) free(str);
    }
}

void mx_print_nlink_linux(struct stat *sb, char *name) {
    int result = lstat(name, sb);
    if (result != -1) {
        mx_printint(sb->st_nlink);
    }
}

static void print_stats(struct stat *sb, char *name, int size_len) {
    struct passwd   *psswd;
    struct group    *grp;

    psswd = getpwuid(sb->st_uid);
    grp = getgrgid(sb->st_gid);

    #ifdef __linux__
    mx_print_rwx(name);
    mx_print_nlink(sb, name, size_len - 2);
    mx_printstr(" ");
    mx_printstr(psswd->pw_name);
    mx_printstr(" ");
    mx_printstr(grp->gr_name);
    mx_printstr(" ");
    mx_print_file_size(name, size_len);
    mx_printstr(" ");
    mx_print_m_time(sb);
    mx_printstr(" ");
    #endif

    #ifdef __APPLE__
    mx_print_rwx(name);
    mx_print_nlink(sb, name, size_len - 1);
    mx_printstr(" ");
    mx_printstr(psswd->pw_name);
    mx_printstr("  ");
    mx_printstr(grp->gr_name);
    mx_printstr("  ");
    mx_print_file_size(name, size_len);
    mx_printstr(" ");
    mx_print_m_time(sb);
    mx_printstr(" ");
    #endif
}

static void process_file_stats(const char *parent, char *name, int size_len) {
    struct stat st_buf;
    char *path = NULL;
    char *temp = NULL;
    path = mx_strnew(mx_strlen(name) + mx_strlen(parent) + 2);
    temp = mx_strjoin(parent, "/");
    free(path);
    path = mx_strjoin(temp, name);
    free(temp);
    if (lstat(parent, &st_buf) == -1) perror("");
    else print_stats(&st_buf, path, size_len);
    free(path);
}

void mx_print_format_details(t_main *main, t_list *filelist, char *path) {
    bool isDir = true; 
    DIR *dir; 
    struct dirent *entry; 
    dir = opendir(path); 
    if (dir == NULL) { 
        isDir = false;
    } 
    if (isDir)
    {
        int count = 0;
        while ((entry = readdir(dir)) != NULL) { 
            count++;
        } 
        closedir(dir);
        dir = opendir(path);
        char *files[count];
        int total = 0;
        for(int i = 0; i < count; i++){
            struct stat file_stat;
            entry = readdir(dir);
            files[i] = mx_strdup(entry->d_name);
            char *files_temp = mx_strjoin("/", files[i]);
            char *temp = mx_strjoin(path, files_temp);
            if (stat(temp, &file_stat) < 0) { 
                perror("stat1"); 
                exit(EXIT_FAILURE); 
            }
            if(mx_get_char_index(main->flags, 'a') > 0) {
                total += file_stat.st_blocks;
            }
            else {
                if (mx_strncmp(files[i], ".", 1) != 0) {
                    total += file_stat.st_blocks;
                }
            }
            free(files_temp);
            free(temp);
        }
        closedir(dir);
        // free the memory allocated by mx_strdup
        for (int i = 0; i < count; i++) {
            free(files[i]);
        }
        #ifdef __linux__
            total /= 2;
        #endif
        mx_printstr("total ");
        mx_printint(total);
        mx_printchar('\n');
    }
    int size_len = mx_get_sf_max_len(filelist, path);
    for (t_list *cur = filelist; cur != NULL; cur = cur->next) {
        process_file_stats(path, cur->data, size_len);
        mx_printstr(cur->data);
        mx_printchar('\n');
    }
}
