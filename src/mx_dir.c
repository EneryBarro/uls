#include "../inc/uls.h"

string_t *mx_dir(string_t dir_name, int *count_of_items) {
    DIR *directory;
    struct dirent *ent;
    *count_of_items = mx_count_items(dir_name);
    directory = opendir(dir_name);
    string_t *items = (string_t *) malloc(sizeof(string_t) * *count_of_items);
    int i = 0;
    while ((ent = readdir(directory)) != NULL) {
        items[i] = mx_strdup(ent->d_name);
        i++;
    }
    closedir(directory);
    return items;
}
