#include "../inc/uls.h"

int mx_file_exists(char *filename) {
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
}
