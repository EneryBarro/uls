#include "../inc/uls.h"

string_t *mx_filenames(int argc, string_t *argv, int *files_count) {
    string_t *files = (string_t *) malloc((int) sizeof(string_t) * argc);
    *files_count = 0;
    int i = 1;
    while ( i < argc ) {
        if (argv[i][0] == '-') {
            i++;
            continue;
        }
        files[(*files_count)++] = argv[i];
        i++;
    }
    string_t *files_ = (string_t *) malloc((int) sizeof(string_t) * *files_count);
    i = 0;
    while ( i < *files_count ) {
            files_[i] = files[i];
            i++;
    }
    free(files);
    return files_;
}
