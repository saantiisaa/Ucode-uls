#include "../inc/uls.h"

void mx_fl_push_back(t_list **list, char *filename) {
    t_list *node = *list;
    if (node == NULL) {
        *list = mx_fl_create_node(filename);
        return;
    }
    while (node->next != NULL) 
        node = node->next;
    node->next = mx_fl_create_node(filename);
}
