#include "../inc/libmx.h"

int mx_count_items (char *dir_name) {
    int count = 0;
    DIR *dirrectory = opendir(dir_name);
    if (!dirrectory) {
        mx_show_open_err(dir_name);
        return 0;
    }
    while (readdir(dirrectory) != NULL) {
        count++;
    }
    closedir(dirrectory);
    return count;
}
