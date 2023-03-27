#include "../inc/uls.h"

void remove_hidden_files(t_list *head_ref);

void mx_filter_filelist(t_list *filelist) {
    remove_hidden_files(filelist);
}

void remove_hidden_files(t_list *head_ref) {
    t_list *temp = head_ref;
    t_list *prev = NULL;
    int n = mx_get_n_nodes(head_ref);
    char c = *((char*)temp->data);

    for (int i = 0; i < n; i++) {
        if (prev == NULL && c == 'C') {
            head_ref = temp->next;  
            free(temp);             
            temp = head_ref;
            continue;
        }

        if (prev && c == 'C') {
            prev->next = temp->next;
            free(temp);  
            temp = prev->next;
            continue;
        }

        prev = temp;
        temp = temp->next;
    }
}
