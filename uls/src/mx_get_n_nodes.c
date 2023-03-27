#include "../inc/uls.h"

int mx_get_n_nodes(t_list *filelist) {
    int n = 0;
    for (t_list *temp = filelist; temp != NULL; temp = temp->next) n++;
    return n;
}
