#include "../inc/uls.h"

item_t **mx_filter(item_t **items, int len, bool (*show)(item_t *), int *new_size) {
    *new_size = 0;
    item_t **arr = (item_t **) malloc(sizeof(item_t) * len);
    int i = 0;
    while ( i < len ) {
        if (show(items[i])) {
            arr[(*new_size)++] = items[i];
        }
        i++;
    }
    return arr;
}
