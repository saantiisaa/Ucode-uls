#include "../inc/uls.h"

void mx_print_filelist(t_list* filelist) {
    for (t_list *cur = filelist; cur != NULL; cur = cur->next) {
        mx_printstr((cur->data));
        mx_printstr("  ->  ");
    }
    mx_printstr("NULL\n");
}
