#include "../inc/uls.h"

void mx_format_output(t_main *main, t_list *filelist, char *path) {
    if (mx_get_char_index(main->flags, 'l') > 0)
        mx_print_format_details(main, filelist, path);
    else if (mx_get_char_index(main->flags, '1') > 0 || main->hasCat == true)
        mx_print_format_column(filelist);
    else
        mx_print_format(filelist);
}
