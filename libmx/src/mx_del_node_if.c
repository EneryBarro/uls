#include "../inc/libmx.h"

void mx_del_node_if(t_list **list, void *del_data, bool (*cmp)(void *a, void *b)) {
    if (cmp == NULL 
            || *list == NULL 
                || list == NULL 
                    || del_data == NULL) {
                         return;
                    }
    t_list *temp = *list, *h = *list;
    while (temp) {
        if (cmp(temp -> data, del_data)) {
            if (*list == temp) {
                *list = temp -> next;
                free(temp);
                temp = *list;
                continue;
            }
            h -> next = temp -> next;
            free(temp);
            temp = h -> next;
            return;
        }
        h = temp;
        temp = temp -> next;
    }
}
