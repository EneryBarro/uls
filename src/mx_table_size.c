#include "../inc/uls.h"

int mx_table_size(item_t **items, int file_count, flags_t flags, int *collum, int *row) {
    if (file_count == 0) {
        *collum = 0;
        *row = 0;
    } else {
        int width = flags.width_console;
        int max_length = 0;
        int i = 0;
        while (i < file_count) {
            int len = mx_strlen(items[i]->name);
            if (max_length < len) {
                max_length = len;
            }
            i++;
        }
        while (++max_length % 8) {
            *collum = width / max_length;
        }
        if (*collum == 0) {
            *collum = 1;
        }
        *row = (int) ((float) file_count / (float) (*collum)) + (file_count % *collum != 0);
        return max_length;
    }
    return 0;
}
