#include "../inc/uls.h"

void mx_norm_items(item_t **items, int *count) {
    int new_count = 0;
    int i = 0;
    while ( i < *count ) {
        if (items[i]) {
            items[new_count++] = items[i];
        }
        i++;
    }
    i = new_count;
    while ( i < *count ) {
        items[i] = NULL;
        i++;
    }
    *count = new_count;
}
