#include "../inc/uls.h"

void mx_delete_filelist(t_list *filelist) {
    t_list *cur = NULL;
    while (filelist) {
        cur = filelist->next;
        mx_strdel((char**) &filelist->data);
        if (filelist != NULL)
            free(filelist);
        filelist = cur;
    }
}
