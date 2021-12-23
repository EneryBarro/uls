#include "../inc/uls.h"

char *mx_options(int argc, string_t *argv, flags_t *flags) {
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
    i = 0;
    while (opts[i]) {
        switch (opts[i]) {
            case '1':
                flags->single = 1;
                flags->longf = 0;
                break;
            case 'C':
                flags->longf = 0;
                flags->single = 0;
                break;
            case 'l':
                flags->longf = 1;
                flags->single = 0;
                break;
            case 'c':
                flags->stattime = 1;
                flags->actime = 0;
                break;
            case 'u':
                flags->actime = 1;
                flags->stattime = 0;
                break;
            case 'R':
                flags->recurs = 1;
                break;
            case 'a':
                flags->pathd = 1;
                break;
            case 'A':
                flags->pathd = 0;
                flags->listd = 1;
                break;
            case 'h':
                flags->hval = 1;
                break;
            case 'r':
                flags->revers = 1;
                break;
            case 'S':
                flags->sizesort = 1;
                break;
            case 'T':
                flags->sectime = 1;
                break;
            case 't':
                flags->timesort = 1;
                break;
            case 'G':
                flags->color = 1;
                break;
            case '@':
                flags->xattr = 1;
                break;
            case 'e':
                flags->acl = 1;
        }
        i++;
    }
    return opts;
}
