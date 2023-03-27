#include "../inc/uls.h"

void mx_printerr(const char *s) {
    if (!s) return;
    write(2, s, mx_strlen(s));
}

void mx_error_illegal_option(const char *ch) {
    mx_printerr("uls: illegal option -- ");
    mx_printerr(ch);
    mx_printerr("\nusage: uls [-");
    mx_printerr(ARGUMENTS);
    mx_printerr("] [file ...]\n");
    exit(1);
}

void mx_error_no_such_file(char *filename) {
    mx_printerr("uls: ");
    mx_printerr(filename);
    mx_printerr(": No such file or directory\n");
    exit(1);
}
