#include "../inc/uls.h"

t_list *mx_fl_create_node(char *filename) {
    t_list *lst = malloc(sizeof(t_list));
    if (!lst) return NULL;
    lst->data = filename;
    lst->next = NULL;
    return lst;
}
