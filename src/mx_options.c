#include "../inc/uls.h"

char *mx_options(int argc, string_t *argv) {
    char *opts = (char *) malloc(sizeof(char));
    int size = 1;
    opts[0] = '\0';
    int i = 1;
    while (i < argc){
        string_t opt = argv[i];
        if (*opt != '-'){
            i++;
            continue;
        }
        opt++;
        while (*opt) {
            if (mx_get_char_index(FLAGS, *opt) == -1) {
                free(opts);
                mx_option_err(*opt);
                return NULL;
            }
            opts = mx_realloc(opts, size + 1);
            opts[size - 1] = *opt;
            opts[size++] = '\0';
            opt++;
        }
        i++;
    }
    return opts;
}
